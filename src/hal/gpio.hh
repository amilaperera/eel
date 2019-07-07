#pragma once
#include "platform/hal_ll.hh"

namespace eel::hal {

class Gpio {
 public:
  static bool IsInterruptSet(Pin pin);
  static void ClearInterrupt(Pin pin);

  explicit Gpio(Pin pin);
  void ConfigureOutput(PullUpDown pud, OutputType type, OutputSpeed speed);
  void ConfigureInput(PullUpDown pud);
  void ConfigureInterrupt(PinInterrupt interrupt);
  bool Read() const;
  explicit operator bool() const;
  void Write(bool status);
  Gpio & operator=(bool status);
  Gpio & operator=(int status);
  void Toggle();
  void EnableInterrupt(eel::util::U32 priority);
  void DisableInterrupt();

 private:
  ll::Gpio gpio_ll_;
};

}
