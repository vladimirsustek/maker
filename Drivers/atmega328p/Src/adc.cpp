#include "adc.hpp"
#include "assert.h"

volatile uint32_t adcRaw = 0;
volatile uint32_t adcAvg = 0;

Adc* Adc::instance = nullptr;

ISR(ADC_vect)
{
    static volatile uint16_t idx = 0;
    adcRaw  += ADC;
    idx = (idx + 1) & 1023;
    if(0 == idx)
    {
        adcAvg = adcRaw >> 10;
        adcRaw = 0;
    }
}

Adc* Adc::getInstance()
{
    if(instance == nullptr)
    {
        static Adc singletonAdc;
        singletonAdc.AdcSingleChannel(Adc::Channel::CHANNEL6);
        instance = reinterpret_cast<Adc*>(&singletonAdc);
    }
    return instance;
}

void Adc::AdcSingleChannel(Adc::Channel channel)
{
    // Set voltage reference to internal 1V1 reference, enable channel 6 (MUX2, MUX1).
    ADMUX = (1 << REFS1) | (1 << REFS0) | static_cast<uint8_t>(channel);
    // Enable ADC, enable auto trigger, enable ADC interrupt (optional), set prescaler to 128
    ADCSRA = (1 << ADEN)  | // ADC Enable
    (1 << ADATE) | // ADC Auto Trigger Enable
    (1 << ADIE) | 
    (1 << ADSC)  | // ADC Start Conversion
    (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler of 128 (16 MHz / 128 = 125 KHz)

    // Set Auto Trigger Source to OC0A (Must be enabled and running before)
    ADCSRB = (1 << ADTS1) | (1 << ADTS0);
}

uint16_t Adc::getVoltage()
{
    return static_cast<uint16_t>(((adcAvg)*1100)/1023); 
}