#ifndef UARTPRINTF_HPP
#define UARTPRINTF_HPP

#include "Uart.hpp"

class UartPrintf 
{
public:
    UartPrintf(Uart& uartInstance);
    ~UartPrintf() = default;
private:
    Uart uart;
};

#endif
