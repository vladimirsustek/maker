#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"
#include "tone.hpp"
#include "core.hpp"
#include "eeprom.hpp"
#include "spi.hpp"
#include "adc.hpp"

#include "cmd_dispatcher.hpp"

extern "C"
{
    #include <avr/io.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>
}

#if TEMPLATE_DEMO

template <typename T> T myMax(T x, T y)
{
    return (x > y) ? x : y;
}

#endif

int main(void)
{
    uint8_t uartRxBuffer[UART_RX_BUFF_SIZE];
    uint16_t uartRxLength;

    /* Timer used for ms_delay, tone and PWM */
    Tim *tim = Tim::getInstance();
    Tone* tone = Tone::getInstance(tim);

    /* Initialize 57600baud Uart */
    Uart* uart = Uart::getInstance();
    uart->enableRxISR(true);

    Adc* adc = Adc::getInstance();

    /* Enable all interrupts within Atmega328p*/
    Core::enableInterrupts();

    /* All Simple-MCU-might-use C++ casts showed - not needed to write() when printf existing */
    //uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);
    printf("HelloWorld\n");


#if TEMPLATE_DEMO
    printf("myMax %d\n", myMax<int>(3,7));
#endif

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
        if((uartRxLength = uart->readLine(uartRxBuffer, UART_RX_BUFF_SIZE)))
        {
            uartRxBuffer[uartRxLength] = 0u;
            uart->write(uartRxBuffer, uartRxLength);
            dispatcher.Dispatch(uartRxBuffer, uartRxLength);
        }

        if(tim->getTick() > prevTick + 100)
        {
            prevTick = tim->getTick();
            static uint16_t cnt = 0;
            if(!cnt)
            {
                gpioPB5.set(true);
                uint16_t txLng = snprintf(reinterpret_cast<char*>(uartRxBuffer), 32, "ADC: %d\n", adc->getVoltage());
                uart->write(uartRxBuffer, txLng);
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