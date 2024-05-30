#ifndef GPIO_HPP
#define GPIO_HPP

extern "C"
{
    #include <avr/io.h>
}

namespace GPIO
{
    /* Addresss obtained from io328p.h */
    constexpr uint16_t DDRB_ADR = 0x04;
    constexpr uint16_t PORTB_ADR = 0x05;

    constexpr uint16_t DDRC_ADR = 0x07;
    constexpr uint16_t PORTC_ADR = 0x08;

    constexpr uint16_t DDRD_ADR = 0x0A;
    constexpr uint16_t PORTD_ADR = 0x0B;

    /* To fit both DDR and PORT into a single number*/
    constexpr uint16_t DDRx_PORTx(uint16_t ddr, uint16_t port)
    {
        return (ddr << 8) | port;
    }

    /* To get DDR back*/
    constexpr uint8_t DDRx(uint16_t ddr_port)
    {
        return static_cast<uint8_t>((ddr_port & 0xFF00) >> 8);
    }

    /* To get PORT back*/
    constexpr uint8_t PORTx(uint16_t ddr_port)
    {
        return static_cast<uint8_t>(ddr_port & 0x00FF);
    }

    enum GpioPort
    {
        IO_PORTB = DDRx_PORTx(DDRB_ADR, PORTB_ADR), 
        IO_PORTC = DDRx_PORTx(DDRC_ADR, PORTC_ADR), 
        IO_PORTD = DDRx_PORTx(DDRD_ADR, PORTD_ADR)
    };

    enum GpioPin
    {
        Pin0 = 0u, Pin1 = 1u, Pin2 = 2u, Pin3 = 3u, Pin4 = 4u, Pin5 = 5u, Pin6 = 6u, Pin7 = 7u
    };

    enum GpioDirection
    {
        Input, Output
    };
}

class Gpio
{
public:
    Gpio(GPIO::GpioPort ioPort, GPIO::GpioPin ioPin, GPIO::GpioDirection ioDirection);
    ~Gpio() = default;
    void set(bool state);
    bool get(void);
private:
    GPIO::GpioPort port;
    GPIO::GpioPin pin;
    GPIO::GpioDirection direction;
};

#endif