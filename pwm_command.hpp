#ifndef PWM_COMMAND_HPP
#define PWM_COMMAND_HPP

#include "cmd_defs.hpp"

uint16_t EnablePWM_OC2B(const uint8_t* const pStrCmd, const uint8_t lng);
uint16_t SetPWM_OC2B(const uint8_t* const pStrCmd, const uint8_t lng);

#endif