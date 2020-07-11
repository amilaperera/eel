//
// Created by amila.perera on 10/07/2020.
//
#include "utils/os_wrapper/timer.hpp"
#if (configUSE_TIMERS == 1)
namespace eel::utils::os_wrapper::detail {

timer_create_helper<timer_type::one_shot>::Callback timer_create_helper<timer_type::one_shot>::callback = one_shot_timer_callback;
timer_create_helper<timer_type::periodic>::Callback timer_create_helper<timer_type::periodic>::callback = periodic_timer_callback;

void one_shot_timer_callback(TimerHandle_t handle) {
  auto self = reinterpret_cast<one_shot_timer*>(pvTimerGetTimerID(handle));
  self->callback_();
}
void periodic_timer_callback(TimerHandle_t handle) {
  auto self = reinterpret_cast<periodic_timer*>(pvTimerGetTimerID(handle));
  self->callback_();
}
}
#endif
