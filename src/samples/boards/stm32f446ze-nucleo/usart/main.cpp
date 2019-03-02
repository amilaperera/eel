#include "hal/cortex/sys_tick_timer.hh"
#include "hal/cortex/lock.hh"
#include "hal/gpio.hh"
#include "hal/usart.hh"

using eel::hal::gpio::Pin;
using eel::hal::gpio::Mode;
using eel::hal::gpio::PullUpDown;
using eel::hal::gpio::OutputType;
using eel::hal::gpio::OutputSpeed;

int main() {
  // tick per 1ms
  eel::hal::SysTickTimer::Enable<eel::hal::SysTickTimer::Frequency::k1kHz, 0xf>();

  // output pin
  eel::hal::Usart serial{eel::hal::usart::Peripheral::kUsart3, eel::hal::gpio::Pin::D8, eel::hal::gpio::Pin::D9};
  serial.ConfigureTx(eel::hal::gpio::Af::k7,
          eel::hal::gpio::PullUpDown::Up,
          eel::hal::gpio::OutputType::PushPull,
          eel::hal::gpio::OutputSpeed::Medium);
  serial.ConfigureRx(eel::hal::gpio::Af::k7,
                     eel::hal::gpio::PullUpDown::Up,
                     eel::hal::gpio::OutputType::PushPull,
                     eel::hal::gpio::OutputSpeed::Medium);
  serial.Configure(115200, eel::hal::usart::WordLength::k8DataBits);
  for (;;) {
    serial.Send('S');
    eel::hal::Tick::Delay(500);
    serial.Send('T');
    eel::hal::Tick::Delay(500);
    serial.Send('M');
    eel::hal::Tick::Delay(500);
    serial.Send('3');
    eel::hal::Tick::Delay(500);
    serial.Send('2');
    eel::hal::Tick::Delay(500);
  }
}

