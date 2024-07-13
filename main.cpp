#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"
#include "tone.hpp"
#include "core.hpp"
#include "eeprom.hpp"


extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

#include "cmd_dispatcher.hpp"

template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

int main(void)
{
    uint8_t buffer[64];
    uint16_t length;

    /* Initialize 57600baud Uart */
    Uart* uart = Uart::getInstance();
    uart->enableRxISR(true);
    /* All Simple-MCU-might-use C++ casts showed */
    uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));
    UartPrintf stdPrintf = UartPrintf(uart);

    /* After this you might call printf() as you are used to */
    printf("myMax %d\n", myMax<int>(3,7));

    /* 1kHz timer used for msDelay*/
    Tim *tim = Tim::getInstance();
    Tone* tone = Tone::getInstance(tim);

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

    /* Show up, the printf-UART redirection works */
    //uint8_t array[64] = "Juch Hody v Zelesicich!\n";
    uint8_t readback[51] = {0};
    //uint16_t length = static_cast<uint16_t>(strlen(reinterpret_cast<char*>(array)));

    //eeprom.write(0, array, length);
    Eeprom* eeprom = Eeprom::getInstance();
    eeprom->read(0u, readback, 50);

    //printf("Readback: %s", const_cast<const char*>(reinterpret_cast<char*>(readback)));

    /* Hvezdy jsou jak sedmikrasky */
    tone->playTone(Note::F_6, Duration::Quarter);
    tone->playTone(Note::AesBb_6, Duration::Quarter);

    CommandDispatcher dispatcher = CommandDispatcher();

    while(1)
    {
        if((length = uart->readLine(buffer, 1)))
        {
            buffer[length] = 0u;
            uart->write(buffer, length);
            dispatcher.Dispatch(buffer, length);

        }
    }
    return 0;
}