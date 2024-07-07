#ifndef TONE_COMMAND_HPP
#define TONE_COMMAND_HPP

#include "cmd_defs.hpp"

uint16_t PlayTone(const uint8_t* const pStrCmd, const uint8_t lng, Peripherals* hardware);

#endif