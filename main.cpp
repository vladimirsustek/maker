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

volatile uint16_t ch6Volt = 0;

ISR(ADC_vect) 
{
    volatile uint8_t adcl = ADCL;
    volatile uint8_t adch = ADCH;
    ch6Volt = (0x300 & static_cast<uint16_t>(adch) << 8) | static_cast<uint16_t>(adcl);
}

int main(void)
{
    uint8_t buffer[64];
    uint16_t length;

    /* Timer used for ms_delay, tone and PWM */
    Tim *tim = Tim::getInstance();
    Tone* tone = Tone::getInstance(tim);

    /* Initialize 57600baud Uart */
    Uart* uart = Uart::getInstance();
    uart->enableRxISR(true);

    PRR &= ~(1 << PRADC);
    
    ADCSRA |= (1 << ADEN);
    ADMUX  |= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
    ADCSRA |= (1 << ADATE) | (1 << ADIE);
    ADMUX  |= ((1<<REFS1) | (1<<REFS0)); 
    ADCSRB &=~( (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0) ); 
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
    ADCSRA &=~(1<<ADPS2);
    DIDR0  = 0b00111111;
    ADCSRA |=(1 << ADSC);


    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

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
            //dispatcher.Dispatch(buffer, length);

        }

        if(tim->getTick() > prevTick + 100)
        {
            prevTick = tim->getTick();
            static uint16_t cnt = 0;
            if(!cnt)
            {
                gpioPB5.set(true);
                printf("ADC: %u\n", ch6Volt);
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