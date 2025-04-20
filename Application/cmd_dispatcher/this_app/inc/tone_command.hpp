#ifndef TONE_COMMAND_HPP
#define TONE_COMMAND_HPP

#include "cmd_defs.hpp"

uint32_t TonePlay(const uint8_t* const pStrCmd, const uint8_t lng);
uint32_t PlaySedmikrasky(const uint8_t* const pStrCmd, const uint8_t lng);
void FnPlaySedmiKrasky();

#endif