#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"
#include "hal/usart.hh"
#include <cstring>

using eel::hal::Pin;
using eel::hal::PinMode;
using eel::hal::PullUpDown;
using eel::hal::OutputType;
using eel::hal::OutputSpeed;
using eel::hal::UsartPeripheral;
using eel::hal::WordLength;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // debug usart configuration
  eel::hal::Usart serial{UsartPeripheral::kUsart3, Pin::D8, Pin::D9};
  serial.ConfigureTxRx(PullUpDown::Up,
                       OutputType::PushPull,
                       OutputSpeed::Medium);
  serial.Configure(115200, WordLength::k8DataBits);

  const char *str{"\r\n" "Simple echo server" "\r\n"};
  serial.Write(reinterpret_cast<const eel::util::U8 *>(str), std::strlen(str));

  for (;;) {
    eel::util::U8 ch{};
    serial.Read(&ch, 1);
    serial.Write(&ch, 1);
  }
}

