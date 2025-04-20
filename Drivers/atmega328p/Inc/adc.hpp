#ifndef ADC_HPP
#define ADC_HPP

extern "C"
{
    #include <stdio.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
}

class Adc
{
public:
    enum Channel
    {
    CHANNEL8 = (1 << MUX3),
    CHANNEL7 = (1 << MUX2) | (1 << MUX1) | (1 << MUX0),
    CHANNEL6 = (1 << MUX2) | (1 << MUX1),
    CHANNEL5 = (1 << MUX2) | (1 << MUX0),
    CHANNEL4 = (1 << MUX2),
    CHANNEL3 = (1 << MUX1) | (1 << MUX0),
    CHANNEL2 = (1 << MUX1),
    CHANNEL1 = (1 << MUX0),
    CHANNEL0 = 0u,
    };

    static Adc* getInstance();
    uint16_t getVoltage();
private:
    Adc() = default;
    ~Adc() = default;
    static Adc* instance;
    void AdcSingleChannel(Adc::Channel  channel);
};

#endif 