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
    static Tim* getInstance();
    uint32_t getTick();
    void msDelay(uint32_t delay); 
    void configureBeepPins(void);
    void setBeepFrequency(uint16_t frequency);
    void enableBeep(bool enable);
    void enableFastPWM_OC2B(bool en);
    void setPWM_OC2B(uint8_t period);
private:
    ~Tim() = default;
    Tim() = default;
    void enable8BitCTCTim0();
    void disableTim0();
    static Tim *instance;
};

#endif