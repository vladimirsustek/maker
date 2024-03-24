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
};