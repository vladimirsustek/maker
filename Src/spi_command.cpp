#include "spi_command.hpp"
#include "spi.hpp"
#include "uart.hpp"
#include "cmd_dispatcher_util.hpp"

extern "C"
{
#include "uartc_wrapper.h"
}

uint16_t SpiWriteRead(const uint8_t* const pStrCmd, const uint8_t lng)
{

    Spi* spi = Spi::getInstance();
    Uart* uart = Uart::getInstance();

    uint8_t spiTransactionLng = ((pStrCmd[CMD_ARG_OFFSET] - '0') *10) + (pStrCmd[CMD_ARG_OFFSET+1] - '0');

    if(spiTransactionLng > 52)
    {
        return CMD_RET_ERR;
    }

    constexpr uint8_t WR_BYTES_LNG = 2;

    if(asciiHex2Hex(const_cast<uint8_t*>(pStrCmd), 
        lng - CMD_ARG_OFFSET - CMD_DELIMITER_LNG - WR_BYTES_LNG - CMD_DELIMITER_LNG, 
        getWriteBuffer(), 
        spiTransactionLng) != 0)
    {
        return CMD_RET_ERR;
    }

    spi->writeAndRead(getWriteBuffer(), getReadBuffer(), spiTransactionLng);

    //hex2AsciiHex_andPrint(getReadBuffer(), spiTransactionLng, NULL);

    return 0;
}