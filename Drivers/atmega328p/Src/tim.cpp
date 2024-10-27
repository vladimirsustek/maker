#include "tim.hpp"

/* Clock frequency of timer F_CPU/PRESCALER = 16MHz/64
   in case of any change, recalculate this constant !!! */
constexpr uint32_t BEEP_CLOCK = 250000u;

/* Incremented variable by TIMER0_COMPA_vect - system tick*/
static volatile uint32_t sys_tick = 0;

Tim* Tim::instance = nullptr;

ISR(TIMER0_COMPA_vect) {
    sys_tick++;
}

Tim* Tim::getInstance()
{

    if(instance == nullptr)
    {
        static Tim singletonTim;
        singletonTim.enable8BitCTCTim0();
        instance = &singletonTim;
    }

    return instance;
}

uint32_t Tim::getTick(void) {
    uint32_t tick = 0;
    /* Disable interrupt for correct
    reading of the sys_tick 32-bit value*/
    TIMSK0 &=~(1 << OCIE0A);
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

/* Configure TIM1 to toggle D1 (PORT.PIN1) when
   CTC reaches compared value OCR1A. For buzzer 
   GND use PORTB.PIN5 */
void Tim::configureBeepPins(void) {

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

void Tim::setBeepFrequency(uint16_t frequency) {

    uint16_t aux_OCR1A = 0u;
    /* Calculate OCR1A compare register value for
    TCNT1A counter (TCNT1A increments up to OCR1A) */
    aux_OCR1A = (uint16_t)((BEEP_CLOCK)/(uint32_t)frequency);
    /* Reset counting register for fluent beep */
    TCNT1 = 0;
    /* Write register for frequency change */
    OCR1A = aux_OCR1A;

}

void Tim::enableBeep(bool state) {
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

void Tim::enable8BitCTCTim0()
{
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

void Tim::disableTim0()
{
    TCCR0A &=~(1 << WGM01);
    TIMSK0 &=~(1 << OCIE0A);
}

void Tim::enableFastPWM_OC2B(bool en)
{
    if(en)
    {
        /* Non inverting mode for OC2B (PORTD.3)*/
        TCCR2A |= (1 << COM2B1);
        /* Enable PORTD.3 as an output */
        DDRD |= (1 << PIN3);
        /* Enabling fast PWM */
        TCCR2A |= (1 << WGM21)|(1 << WGM20);
        /* Prescaler 1024 (16M/1024 = 250kHz)*/
        //TCCR2B |= (1 << CS22)| (1 << CS21)|(1 << CS20);
        TCCR2B |= (1 << CS20);

    }
    else
    {
        /* Prescaler 0 -> no clock source, WGM2 clear (WGM2 = 0 does not ensure no waveform)*/
        TCCR2B &= ~((1 << CS22)| (1 << CS21)|(1 << CS20) | (1 << WGM22));
        /* Clearing WGM1:0 forcing Timer to 'NORMAL MODE' */
        TCCR2A &= ~((1 << WGM21)|(1 << WGM20));
        /* Disconnecting Timer from OC2B */
        TCCR2A &= ~((1 << COM2B1)|(1 << WGM20));
        /* Set PORTD.3 as an input */
        DDRD &= ~(1 << PIN3);
    }
        /* Setting PWM to 0 */
        OCR2B = 0;
}

void Tim::setPWM_OC2B(uint8_t period)
{
    OCR2B = period;
}