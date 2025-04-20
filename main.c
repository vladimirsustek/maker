#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

#define USART_BAUDRATE      (uint16_t)(57600)
#define BAUD_PRESCALE (uint16_t)(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define UART_BUFF_BUSY      (!(UCSR0A & (1 << UDRE0)))

static volatile uint32_t sys_tick = 0;

ISR(TIMER0_COMPA_vect) {
    sys_tick++;
}

void enable8BitCTCTim0(void)
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

uint32_t getTick(void) {
    uint32_t tick = 0;
    /* Disable interrupt for correct
    reading of the sys_tick 32-bit value*/
    TIMSK0 &=~(1 << OCIE0A);
    tick = sys_tick;
    /* Enable-back timer interrupt */
    TIMSK0|= (1 << OCIE0A);
    return tick;
}

void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}

uint16_t ADC_readChannel(uint8_t channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADCSRA |= (1 << ADSC); /* Start conversion write '1' to ADSC */
	while(false == (ADCSRA & (1 << ADIF))); /* Wait for conversion to complete, ADIF becomes '1' */
    ADCSRA |= (1 << ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}

uint16_t write(char* pData, uint16_t size)
{
    uint16_t idx;
    /* Enable TX line */
    UCSR0B|= (1 << TXEN0);

    for (idx = 0; idx < size; idx++)
    {
        /* Start UART transmission - fill buffer*/
        UDR0 = (uint8_t)pData[idx];

        while (UART_BUFF_BUSY){
            /* Do nothing - stuck here*/
        }
    }

    /* Disable TX line */
    UCSR0B&=~(1 << TXEN0);

    return idx;
}

void UartInit()
{
        /* Use 8 - bit size of transaction symbol */
        UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
        /* Upper part of bitrate 57600*/
        UBRR0H |= (BAUD_PRESCALE >> 8);
        /* Lower part of bitrate 57600 */
        UBRR0L |= BAUD_PRESCALE;
}
int main(void)
{
    char helloWorld[32] = {0};
    uint32_t prevTick = 0;

    DDRC &= ~(1 << DDC0);

    // Set voltage reference to AVcc with external capacitor at AREF pin
    ADMUX = (1 << REFS1) | (1 << REFS0); // REFS1=0, REFS0=1 -> AVcc reference
                          // MUX[3:0]=0000 -> ADC0

    // Enable ADC, enable auto trigger, enable ADC interrupt (optional), set prescaler to 128
    ADCSRA = (1 << ADEN)  | // ADC Enable
             (1 << ADATE) | // ADC Auto Trigger Enable
             (1 << ADSC)  | // ADC Start Conversion
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler of 128 (16 MHz / 128 = 125 KHz)

    // Set Auto Trigger Source to Free Running Mode
    ADCSRB = 0; // ADTS[2:0] = 000 for Free Running Mode

    UartInit();
    enable8BitCTCTim0();
    sei();


    while(1)
    {
        if(getTick() > prevTick + 100)
        {
            prevTick = getTick();
            static uint16_t cnt = 0;
            if(!cnt)
            {
                while (!(ADCSRA & (1 << ADIF)));
                // Read ADC value
                uint16_t adc_value = ADC;
                uint32_t voltage = (((uint32_t)adc_value)*1100)/1023;
                // Clear ADIF by writing 1 to it (yes, that's how you clear it)
                ADCSRA |= (1 << ADIF);                
                uint16_t txLng = snprintf(helloWorld, 32, "ADC: %ld\n", voltage);
                write(helloWorld, txLng);
            }
            else
            {

            }
            cnt = (cnt + 1) & 7;
        }
    }

    return 0;
}