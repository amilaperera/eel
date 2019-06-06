#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"
#include "hal/usart.hh"
#include "util/streams/io_device_wrapper.hh"
#include "util/streams/io_stream.hh"

using eel::hal::Pin;
using eel::hal::PinMode;
using eel::hal::PullUpDown;
using eel::hal::OutputType;
using eel::hal::OutputSpeed;
using eel::hal::UsartPeripheral;
using eel::hal::WordLength;

using eel::util::IOStream;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // debug usart configuration
  eel::hal::Usart serial{UsartPeripheral::kUsart3, Pin::D8, Pin::D9};
  serial.ConfigureTxRx(PullUpDown::Up,
                       OutputType::PushPull,
                       OutputSpeed::Medium);
  serial.Configure(115200, WordLength::k8DataBits);

  // IO device from debug usart
  auto io_device = eel::util::MakeIODevice(&serial);
  // Creating an IO stream from an IO device
  IOStream ios{&io_device};

  // some fun
  ios << IOStream::Endl << "Serial echo server with IOStream" << IOStream::Endl;
  ios << IOStream::Err << "This is an error....\r\n" << IOStream::NoErr;
  ios << IOStream::Warn << "This is a warning....\r\n" << IOStream::NoWarn;
  ios << IOStream::Info << "This is an info....\r\n" << IOStream::NoInfo;
  ios << IOStream::Err << "This " << IOStream::Warn << "is a " << IOStream::Info << "mix" << IOStream::Reset
      << IOStream::Endl;

  ios << "prompt > ";

  for (;;) {
    char ch;
    ios >> ch;
    ios << ch;
  }
}


