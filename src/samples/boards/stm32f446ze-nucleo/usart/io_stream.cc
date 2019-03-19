#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"
#include "hal/usart.hh"
#include <cstring>
#include "util/streams/io_device_wrapper.hh"
#include "util/streams/io_stream.hh"

using eel::hal::gpio::Pin;
using eel::hal::gpio::Mode;
using eel::hal::gpio::PullUpDown;
using eel::hal::gpio::OutputType;
using eel::hal::gpio::OutputSpeed;

using eel::util::IOStream;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::Enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // output pin
  eel::hal::Usart serial{eel::hal::usart::Peripheral::kUsart3, eel::hal::gpio::Pin::D8, eel::hal::gpio::Pin::D9};
  serial.ConfigureTxRx(eel::hal::gpio::Af::k7,
                       eel::hal::gpio::PullUpDown::Up,
                       eel::hal::gpio::OutputType::PushPull,
                       eel::hal::gpio::OutputSpeed::Medium);
  serial.Configure(115200, eel::hal::usart::WordLength::k8DataBits);

  auto io_device = eel::util::MakeIODeviceWrapper(&serial);
  IOStream io_stream{&io_device};

  io_stream << IOStream::Endl << "Serial echo server with IOStream" << IOStream::Endl;
  io_stream << "prompt > ";

  for (;;) {
    char ch;
    io_stream >> ch;
    io_stream << ch;
  }
}


