#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"
#include "tone.hpp"
#include "core.hpp"

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
    Tone tone = Tone(tim);

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));


    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

    /* Show up, the printf-UART redirection works */
    printf("The number of the beast is %ld\n", demoNumber++);

    /* Hvezdy jsou jak sedmikrasky */
    tone.playTone(Note::F_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    tone.playTone(Note::E_7, Duration::Quarter);
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);

    /* nad Brnem */
    tone.playTone(Note::GisAb_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
    tone.playTone(Note::F_6, Duration::Half);
    tone.playTone(Note::F_6, Duration::Half);
    tone.playTone(Note::None, Duration::Half);

    /* noc, muj mily */
    tone.playTone(Note::E_6, Duration::Quarter);
    tone.playTone(Note::FisGb_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);

    /* dobrou */
    tone.playTone(Note::CisDb_7, Duration::Half);
    tone.playTone(Note::DisEb_7, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);

    /* noc */
    tone.playTone(Note::CisDb_7, Duration::Full);
    tone.playTone(Note::CisDb_7, Duration::Half);

    /* -pomlka- */
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    tone.playTone(Note::CisDb_7, Duration::Quarter);
    
    tim.enableBeep(false);
    
    while(1)
    {   
    }

    return 0;
}