#include "spi_command.hpp"
#include "spi.hpp"

extern "C"
{
    #include <stdio.h>
}

uint16_t SpiWriteRead(const uint8_t* const pStrCmd, const uint8_t lng)
{

    (void)pStrCmd;
    (void)lng;
    
    Spi* spi = Spi::getInstance();
    uint8_t wdata = 0xAA;
    uint8_t rdata = 0;
    spi->writeAndRead(&wdata, &rdata, 1);
    printf("W0x%02x R0x%02x\n", wdata, rdata);

    return 0;
}