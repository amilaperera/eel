#pragma once
#include "util/types.hh"
namespace eel {
namespace hal {

class SysTickTimer {
 private:
  static constexpr eel::util::U32 kBaseAddr{0xE000E010U};
  struct RCB {
    eel::util::IO_U32 STK_CTRL;
    eel::util::IO_U32 STK_LOAD;
    eel::util::IO_U32 STK_VAL;
    eel::util::IO_U32 STK_CALIB;
  };

  static auto SysTickRegisterBlock() {
    return reinterpret_cast<RCB *>(SysTickTimer::kBaseAddr);
  }

 public:
  static void SetReloadValue(eel::util::U32 val) {
    SysTickRegisterBlock()->STK_LOAD = (val & 0x00FFFFFFU);
  }
  static eel::util::U32 GetReloadValue() {
    return SysTickRegisterBlock()->STK_LOAD & 0x00FFFFFFU;
  }
  static void Enable(eel::util::U32 frequency) {

  }
};

}
}
