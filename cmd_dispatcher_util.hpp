#ifndef CMD_DISPATCHER_UTIL_HPP
#define CMD_DISPATCHER_UTIL_HPP

#include "uart.hpp"
#include "cmd_defs.hpp"
extern "C"
{
    #include <stdint.h>
}

void hex2AsciiHex_andPrint(const uint8_t *pArr, uint8_t arrLng, Uart *uart);
uint8_t asciiHex2Hex(uint8_t *inArr, uint8_t inArrLng, uint8_t* outArr, uint8_t outArrLng);
uint8_t* getReadBuffer();
uint8_t* getWriteBuffer();

typedef uint16_t (*pfn_u8_cu8)(const uint8_t lng);

#endif
