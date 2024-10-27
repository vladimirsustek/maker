#ifndef EEPROM_COMMAND_HPP
#define EEPROM_COMMAND_HPP

#include "cmd_defs.hpp"

uint32_t PrintData(const uint8_t* const pStrCmd, const uint8_t lng);
uint32_t WriteData(const uint8_t* const pStrCmd, const uint8_t lng);

#endif