#include "tim.hpp"

/* Clock frequency of timer F_CPU/PRESCALER = 16MHz/64
   in case of any change, recalculate this constant !!! */
#define BEEP_CLOCK          (uint32_t)(250000)

/* Incremented variable by TIMER0_COMPA_vect - system tick*/
static volatile uint32_t sys_tick = 0;

ISR(TIMER0_COMPA_vect) {
    sys_tick++;
}

Tim::Tim() {

    /* TIM0 - ATmega328p 8-bit timer *************/

    /* WGM01: CTC mode - clear timer of compare match.
    This means that timer is incremented to value OCR1A,
    when the value is reached, interrupt is called and
    timer is cleared
    */
    TCCR0A |= (1 << WGM01);
    /* TCCR0B: CS01, CS00 sets 64x prescaler */
    TCCR0B |= (1 << CS01)|(1 << CS00);
    /* Enable timer interrupt */
    TIMSK0|= (1 << OCIE0A);
    /* Set the compare value based on calculation:
       freq = CLOCK/(PRESCALER * OCR1A)
       in case of 16MHz Clock and 64x prescaler
       the frequency of counting is 250kHZ what
       means that if timer counts from 0 to 249,
       value 249 is reached with frequency 1kHZ*/
    OCR0A = 249;
}

Tim::~Tim() {

    TCCR0A &=~(1 << WGM01);
    TIMSK0 &=~(1 << OCIE0A);

}

uint32_t Tim::getTick(void) {
    uint32_t tick = 0;
    /* Disable interrupt for correct
    reading of the sys_tick 32-bit value*/
    TIMSK0&=~(1 << OCIE0A);
    tick = sys_tick;
    /* Enable-back timer interrupt */
    TIMSK0|= (1 << OCIE0A);
    return tick;
}

void Tim::msDelay(uint32_t delay) {

  uint32_t tickstart = 0;
  tickstart = this->getTick();

  while ((tickstart + delay > this->getTick())) {
  }
}

void tim_beep_D6D4_initialize(void) {

    /* TIM0 - ATmega328p 8-bit timer *************/

    /* Enable beep anode - timer controlled output 'D9'*/
    DDRB|= (1 << PIN1);
    /* Enable beep cathode - permanently grounded 'D7'*/
    DDRD|= (1 << PIN5);
    /* Set cathode as permanently grounded 'D7'*/
    PORTD|= (1 << PIN5);

    /* WGM12: CTC mode - clear timer of compare match.
    This means that timer is incremented to value OCR1A,
    when the value is reached, interrupt is called and
    timer is cleared
    CS11, CS10: Prescaler of the clock source 64x */
    TCCR1B |= (1 << WGM12)|(1 << CS11)|(1 << CS10);
    /* COM1A0: enable toggling PORTB.PIN1 when CTC
    reaches value OCR1A */
    TCCR1A = (1 << COM1A0);

}

extern void tim_beep_D6D4_sound(bool state) {
    if(state) {
        /* Enable toggling PORTB.PIN1 and
        enable timer device */
        TCCR1B |= (1 << WGM12);
        TCCR1A |= (1 << COM1A0);

    }
    else {
        /* Disable toggling PORTB.PIN1 and
        Disable timer device */
        TCCR1B &= ~(1 << WGM12);
        TCCR1A &= ~(1 << COM1A0);
    }
}

extern void tim_beep_D6D4_freq(uint16_t freq) {

    uint16_t aux_OCR1A = 0u;
    /* Calculate OCR1A compare register value for
    TCNT1A counter (TCNT1A increments up to OCR1A) */
    aux_OCR1A = (uint16_t)((BEEP_CLOCK)/(uint32_t)freq);
    /* Reset counting register for fluent beep */
    TCNT1 = 0;
    /* Write register for frequency change */
    OCR1A = aux_OCR1A;

}
