#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"

extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

int main(void)
{
    uint32_t demoNumber = 0;

    /* Initialize 57600baud Uart */
    Uart uart = Uart(false);
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);

    /* 1kHz timer used for msDelay*/
    Tim tim = Tim();

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));

    tim.configureBeepPins();
    tim.enableBeep(true);

    /* Enable all interrupts within Atmega328p*/
    sei();

    /* Show up, the printf-UART redirection works */
    printf("The number of the beast is %ld\n", demoNumber++);

    tim.setBeepFrequency(Tone::C_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::D_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::E_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::F_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::G_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::A_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::B_4);
    tim.msDelay(450);
    tim.setBeepFrequency(Tone::C_5);
    tim.msDelay(450);
    
    tim.enableBeep(false);

    while(1)
    {   
    }

    return 0;
}