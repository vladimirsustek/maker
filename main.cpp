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

int main(void)
{
    uint32_t demoNumber = 0;

    /* Initialize 57600baud Uart */
    Uart uart = Uart(true);
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);

    /* 1kHz timer used for msDelay*/
    Tim tim = Tim();
    Tone tone = Tone(tim);

    EEPROM eeprom = EEPROM();

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));
    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

    /* Show up, the printf-UART redirection works */
    printf("The number of the beast is %ld\n", demoNumber++);

    //uint8_t array[64] = "Juch Hody v Zelesicich!\n";
    uint8_t readback[51] = {0};
    //uint16_t length = static_cast<uint16_t>(strlen(reinterpret_cast<char*>(array)));

    //eeprom.write(0, array, length);
    eeprom.read(0u, readback, 50);

    //printf("Readback: %s", const_cast<const char*>(reinterpret_cast<char*>(readback)));

    /* Hvezdy jsou jak sedmikrasky */
    tone.playTone(Note::F_6, Duration::Quarter);
    tone.playTone(Note::AesBb_6, Duration::Quarter);
#if 0
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
#endif
    tim.enableBeep(false);


    uint8_t buffer[64];
    uint16_t length;
    
    //printf("Delay 15000 ms start\n");
    //tim.msDelay(15000);
    //printf("Delay 15000 ms stop\n");

    ;

    while(1)
    {
        if((length = uart.readLine(buffer, 1)))
        {
            buffer[length] = 0u;
            //uart.write(buffer, length);
            //CmdDispatch(const_cast<const uint8_t*>(buffer), length);
            CmdDispatch(buffer, length);
        }
        
    }

    return 0;
}