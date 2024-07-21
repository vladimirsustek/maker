#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"
#include "tone.hpp"
#include "core.hpp"
#include "eeprom.hpp"
#include "spi.hpp"

#include "cmd_dispatcher.hpp"

extern "C"
{
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

int main(void)
{
    uint8_t buffer[64];
    uint16_t length;

    /* Timer used for ms_delay, tone and PWM */
    Tim *tim = Tim::getInstance();
    Tone* tone = Tone::getInstance(tim);
    
    Core::enableInterrupts();
    tim->enableFastPWM_OC2B(TIMER1_CAPT_vect_num);
    tim->setPWM_OC2B(127);
    while(1);

    /* Enable all interrupts within Atmega328p*/

    /* Initialize 57600baud Uart */
    Uart* uart = Uart::getInstance();
    uart->enableRxISR(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));
    UartPrintf stdPrintf = UartPrintf(uart);

    /* After this you might call printf() as you are used to */
    printf("myMax %d\n", myMax<int>(3,7));
    printf("TBD:\n"
    "   -SPI\n"
    "   -I2C\n"
    "   -WDG\n"
    "   -FLASH\n");

    /* Led GPIO */
    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    gpioPB5.set(false);

    tone->playTone(Note::F_6, Duration::Quarter);
    tone->playTone(Note::AesBb_6, Duration::Quarter);

    CommandDispatcher dispatcher = CommandDispatcher();

    uint32_t prevTick = 0;
    while(1)
    {
        if((length = uart->readLine(buffer, 1)))
        {
            buffer[length] = 0u;
            uart->write(buffer, length);
            dispatcher.Dispatch(buffer, length);

        }

        if(tim->getTick() > prevTick + 100)
        {
            prevTick = tim->getTick();
            static uint16_t cnt = 0;
            if(!cnt)
            {
                gpioPB5.set(true);
            }
            else
            {
                gpioPB5.set(false);
            }
            cnt = (cnt + 1) & 7;
        }

    }
    return 0;
}