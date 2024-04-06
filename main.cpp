#include "uart.hpp"
#include "uartprintf.hpp"
#include "tim.hpp"
#include "gpio.hpp"

extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

extern void tim_beep_D6D4_initialize(void);
extern void tim_beep_D6D4_freq(uint16_t freq);
extern void tim_beep_D6D4_sound(bool state);

void getAndPrintIoState(Gpio & io)
{
    bool state = io.get();

    if(true == state)
    {
        printf("GPIO is 1\n");
    
    }
    else
    {
        printf("GPIO is 0\n");
    }
}

#include <stdint.h>

// Define note frequencies for multiple octaves
#define TONE_REST 0
#define TONE_C3 130
#define TONE_C3_SHARP 138
#define TONE_D3 146
#define TONE_D3_SHARP 155
#define TONE_E3 164
#define TONE_F3 174
#define TONE_F3_SHARP 184
#define TONE_G3 195
#define TONE_G3_SHARP 207
#define TONE_A3 220
#define TONE_A3_SHARP 233
#define TONE_B3 246
#define TONE_C4 261
#define TONE_C4_SHARP 277
#define TONE_D4 293
#define TONE_D4_SHARP 311
#define TONE_E4 329
#define TONE_F4 349
#define TONE_F4_SHARP 369
#define TONE_G4 391
#define TONE_G4_SHARP 415
#define TONE_A4 440
#define TONE_A4_SHARP 466
#define TONE_B4 493

// Define note durations
#define NOTE_WHOLE 2000
#define NOTE_HALF 1000
#define NOTE_QUARTER 500
#define NOTE_EIGHTH 250
#define NOTE_SIXTEENTH 125

// Define structure to hold tone and note duration
typedef struct {
    uint16_t tone;
    uint16_t duration;
} tone_note;

// Define the melody using the defined notes and durations
const tone_note melody[] = {
    {TONE_E4, NOTE_QUARTER}, {TONE_E4, NOTE_QUARTER}, {TONE_E4, NOTE_QUARTER}, {TONE_C4, NOTE_QUARTER}, {TONE_E4, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER},
    {TONE_C4, NOTE_HALF}, {TONE_G4, NOTE_HALF}, {TONE_E4, NOTE_HALF}, {TONE_A4, NOTE_HALF}, {TONE_B4, NOTE_HALF}, {TONE_B4, NOTE_HALF},
    {TONE_A4_SHARP, NOTE_QUARTER}, {TONE_A4, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER}, {TONE_E4, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER}, {TONE_A4, NOTE_QUARTER},
    {TONE_F4, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER}, {TONE_A4_SHARP, NOTE_QUARTER}, {TONE_G4, NOTE_QUARTER}, {TONE_C4, NOTE_HALF},
    {TONE_E4, NOTE_HALF}, {TONE_D4, NOTE_HALF}, {TONE_C4, NOTE_HALF}, {TONE_G4, NOTE_HALF}, {TONE_A4, NOTE_HALF}, {TONE_F4, NOTE_HALF},
    {TONE_G4, NOTE_HALF}, {TONE_E4, NOTE_HALF}, {TONE_C4, NOTE_HALF}, {TONE_D4, NOTE_HALF}, {TONE_B4, NOTE_HALF}, {TONE_C4, NOTE_HALF},
};

int main(void)
{
    uint32_t demoNumber = 0;

    /* Initialize 57600baud Uart */
    Uart uart = Uart(false);
    /* After this you might call printf() as you are used to */
    UartPrintf stdPrintf = UartPrintf(uart);

    /* 1kHz timer used for msDelay*/
    Tim tim = Tim();

    Gpio gpioPB5 = Gpio(GPIO::GpioPort::IO_PORTB, GPIO::GpioPin::Pin5, GPIO::GpioDirection::Output);
    Gpio gpioPC4 = Gpio(GPIO::GpioPort::IO_PORTC, GPIO::GpioPin::Pin4, GPIO::GpioDirection::Output);
    gpioPC4.set(true);

    /* All Simple-MCU-might-use C++ casts showed */
    uart.write(reinterpret_cast<uint8_t*>(const_cast<char*>("HelloWorld!\n")), static_cast<uint16_t>(strlen("HelloWorld!\n")));

    tim_beep_D6D4_initialize();

    /* Enable all interrupts within Atmega328p*/
    sei();

    /* Show up, the printf-UART redirection works */
    printf("The number of the beast is %ld\n", demoNumber++);


    for(int tone = 0; tone < 36; tone++)
    {
        tim_beep_D6D4_freq(melody[tone].tone);
        tim.msDelay(melody[tone].duration);
    }

    tim_beep_D6D4_sound(false);

    while(1)
    {   
    }

    return 0;
}