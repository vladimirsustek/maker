#include "gpio.hpp"

extern "C"
{
    #include <stdio.h>
}

Gpio::Gpio(GPIO::GpioPort ioPort, GPIO::GpioPin ioPin, GPIO::GpioDirection ioDirection):
    port(ioPort), pin(ioPin), direction(ioDirection)

{
    if(GPIO::GpioDirection::Output == direction)
    {
        _SFR_IO8(GPIO::DDRx(this->port)) |=  (1 << static_cast<uint8_t>(this->pin));
    }
    else
    {
        _SFR_IO8(GPIO::DDRx(this->port)) &= ~(1 << static_cast<uint8_t>(this->pin));
    }
}

void Gpio::set(bool state)
{
    if(true == state)
    {
        _SFR_IO8(GPIO::PORTx(this->port)) |= (1 << static_cast<uint8_t>(this->pin));
    }
    else
    {
        _SFR_IO8(GPIO::PORTx(this->port)) &= ~(1 << static_cast<uint8_t>(this->pin));
    }
}

bool Gpio::get(void)
{
    return (_SFR_IO8(GPIO::PORTx(this->port)) & static_cast<uint8_t>(this->pin));
}