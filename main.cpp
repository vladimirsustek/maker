#include "function.hpp"
#include "uart_interface.hpp"

extern "C"
{
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

#define ONBOARD_LED     (uint8_t)(PIN5)

void gpio_initialize(void){

    DDRB|=(1 << ONBOARD_LED);
    PORTB&=~(1 << ONBOARD_LED);
}

void gpio_LED_toggle(void){

    if(PORTB & (1 << ONBOARD_LED)){
        PORTB&=~(1 << ONBOARD_LED);
    }
    else {
        PORTB|= (1 << ONBOARD_LED);
    }
}

void gpio_LED_set(bool state){

    if(state == true){
        PORTB|= (1 << PIN5);
    }
    if(state == false) {
        PORTB&=~(1 << PIN5);
    }
}

int main(void)
{
    gpio_initialize();
    UARTinitiliaze(false);

    static uint32_t number = 0;

    while(1)
    {   _delay_ms(950);
        gpio_LED_set(true);
        _delay_ms(50);
        gpio_LED_set(false);
        printf("The number of the beast is %ld\n", number++);
    }

    return 0;
}