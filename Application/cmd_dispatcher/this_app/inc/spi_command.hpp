#ifndef SPI_COMMAND_HPP
#define SPI_COMMAND_HPP

#include "cmd_defs.hpp"

uint32_t SpiWriteRead(const uint8_t* const pStrCmd, const uint8_t lng);

#endif