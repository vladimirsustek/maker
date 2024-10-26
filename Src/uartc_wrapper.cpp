#include "uart.hpp"

extern "C"
{
    #include "uartc_wrapper.h"
}

void uart_write(char c)
{
    Uart* uartInstance = Uart::getInstance();
    uartInstance->write(reinterpret_cast<uint8_t*>(&c), sizeof(char));
}