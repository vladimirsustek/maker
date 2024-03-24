#include "gpio.hpp"

Gpio::Gpio(GPIO::GpioPort ioPort, GPIO::GpioPin ioPin, GPIO::GpioDirection ioDirection):
    port(ioPort), pin(ioPin), direction(ioDirection)

{
    switch(ioPort)
    {
        case GPIO::GpioPort::IO_PORTB:
        {
            if(ioDirection == GPIO::GpioDirection::Ouput)
            {
                DDRB|=(1 << static_cast<uint8_t>(ioPin));
            }
            else
            {
                DDRB&=~(1 << static_cast<uint8_t>(ioPin));
            }
        }
        break;

        case GPIO::GpioPort::IO_PORTC:
        {
            if(ioDirection == GPIO::GpioDirection::Ouput)
            {
                DDRC|=(1 << static_cast<uint8_t>(ioPin));
            }
            else
            {
                DDRC&=~(1 << static_cast<uint8_t>(ioPin));
            }
        }
        break;

        case GPIO::GpioPort::IO_PORTD:
        {
            if(ioDirection == GPIO::GpioDirection::Ouput)
            {
                DDRD|=(1 << static_cast<uint8_t>(ioPin));
            }
            else
            {
                DDRD&=~(1 << static_cast<uint8_t>(ioPin));
            }
        }
        break;
    }
}

void Gpio::set(bool state)
{
    switch(this->port)
    {
        case GPIO::GpioPort::IO_PORTB:
        {
            if(state)
            {
                PORTB|= (1 << static_cast<uint8_t>(this->pin));
            }
            else
            {
                PORTB&=~(1 << static_cast<uint8_t>(this->pin));
            }
        }
        break;
        case GPIO::GpioPort::IO_PORTC:
        {
            if(state)
            {
                PORTC|= (1 << static_cast<uint8_t>(this->pin));
            }
            else
            {
                PORTC&=~(1 << static_cast<uint8_t>(this->pin));
            }
        }
        break;
        case GPIO::GpioPort::IO_PORTD:
        {
            if(state)
            {
                PORTD|= (1 << static_cast<uint8_t>(this->pin));
            }
            else
            {
                PORTD&=~(1 << static_cast<uint8_t>(this->pin));
            }
        }
        break;
    }
}

bool Gpio::get(void)
{
    return false;
}