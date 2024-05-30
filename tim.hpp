#ifndef TIM_HPP
#define TIM_HPP

extern "C"
{
    /* Standard libraries */
    #include <stdint.h>
    #include <stdbool.h>
    /* AVR libraries */
    #include <avr/io.h>
    #include <avr/interrupt.h>
}

class Tim
{
public:
    Tim();
    ~Tim();
    uint32_t getTick();
    void msDelay(uint32_t delay); 
    void configureBeepPins(void);
    void setBeepFrequency(uint16_t frequency);
    void enableBeep(bool enable);

};

#endif