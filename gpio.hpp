extern "C"
{
    #include <avr/io.h>
}

namespace GPIO
{
    enum GpioPort
    {
        IO_PORTB, IO_PORTC, IO_PORTD
    };

    enum GpioPin
    {
        Pin0 = 0, Pin1 = 1, Pin2 = 2, Pin3 = 3, Pin4 = 4, Pin5 = 5, Pin6 = 6, Pin7 = 7
    };

    enum GpioDirection
    {
        Input, Ouput
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