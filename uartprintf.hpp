#include "Uart.hpp"

class UartPrintf 
{
public:
    UartPrintf(Uart& uartInstance);
    ~UartPrintf() = default;
private:
    Uart uart;
};
