#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"

extern "C"
{
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

int main(void)
{
    uint32_t demoNumber = 0;

    Uart uart = Uart(false);
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);

    /* 1kHz timer used for msDelay*/
    Tim tim = Tim();

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));

    /* Enable all interrupts within Atmega328p*/
    sei();

    while(1)
    {   tim.msDelay(950);
        //gpio_LED_set(true);
        tim.msDelay(50);
        //gpio_LED_set(false);

        /* Show up, the printf-UART redirection works */
        printf("The number of the beast is %ld\n", demoNumber++);
    }

    return 0;
}