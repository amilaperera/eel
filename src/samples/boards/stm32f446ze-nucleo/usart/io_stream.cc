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
  eel::hal::SysTickTimer::enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // debug usart configuration
  eel::hal::Usart serial{eel::hal::usart::Peripheral::kUsart3, eel::hal::gpio::Pin::D8, eel::hal::gpio::Pin::D9};
  serial.configure_tx_rx(eel::hal::gpio::PullUpDown::Up,
                         eel::hal::gpio::OutputType::PushPull,
                         eel::hal::gpio::OutputSpeed::Medium);
  serial.configure(115200, eel::hal::usart::WordLength::k8DataBits);

  // IO device from debug usart
  auto io_device = eel::util::make_io_device(&serial);
  // Creating an IO stream from an IO device
  IOStream ios{&io_device};

  // some fun
  ios << IOStream::endl << "Serial echo server with IOStream" << IOStream::endl;
  ios << IOStream::err << "This is an error....\r\n" << IOStream::noerr;
  ios << IOStream::warn << "This is a warning....\r\n" << IOStream::nowarn;
  ios << IOStream::info << "This is an info....\r\n" << IOStream::noinfo;
  ios << IOStream::err << "This " << IOStream::warn << "is a " << IOStream::info << "mix" << IOStream::reset << IOStream::endl;

  ios << "prompt > ";

  for (;;) {
    char ch;
    ios >> ch;
    ios << ch;
  }
}


