#include "hal/hal.hpp"
#include "hal/uart.hpp"
#include "hal/pin_in.hpp"
#include "utils/os_wrapper/task.hpp"
#include "utils/streams/io_device_wrapper.hpp"
#include "utils/streams/io_stream.hpp"
#include "samples/semaphore_from_isr_test.hpp"

using namespace eel::utils;
using namespace eel::utils::os_wrapper::literals;

eel::hal::pin_in* button_ptr{nullptr};
os_wrapper::binary_semaphore* sem{nullptr};

GPIO_IRQ_BEGIN(eel::hal::pin_name::C13)
    if (button_ptr->read() == eel::hal::pin_level::high) {
      sem->give_from_isr();
    }
GPIO_IRQ_END

struct init_task : os_wrapper::task {
  init_task() : os_wrapper::task{os_wrapper::priority(20)} {}

  void run() override {
    eel::hal::uart serial(eel::hal::pin_name::D8, eel::hal::pin_name::D9, 115200);
    auto io_device = make_io_device(&serial);
    io_stream io{&io_device};

    button_ptr = new eel::hal::pin_in(eel::hal::pin_name::C13, eel::hal::interrupt_mode::both);
    button_ptr->set_priority(configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

    sem = new os_wrapper::binary_semaphore();

    task_1 t1(io);
    task_2 t2(t1);
    task_3 t3(t1, *sem);

    suspend();
  }
};

int main() {
  eel::hal::init();
  [[maybe_unused]] auto init_routine = new init_task;
  os_wrapper::start_scheduler();
}
