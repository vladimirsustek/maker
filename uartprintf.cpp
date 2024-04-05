extern "C"
{
    #include <string.h>
    #include <stdio.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
}

#include "uartprintf.hpp"

extern "C"
{

/* Otherwise avr-g++ complains */
#undef FDEV_SETUP_STREAM
#define FDEV_SETUP_STREAM(p, g, f) \
    {                              \
        .buf = NULL,               \
        .unget = 0,                \
        .flags = f,                \
        .size = 0,                 \
        .len = 0,                  \
        .put = p,                  \
        .get = g,                  \
        .udata = 0                 \
    }

/* STDIO redirection of printf to appropriate UART.
 * Note that TX line is always enabled and disabled
   after each transmission (function call)*/
static int uart_putchar(char c, FILE *stream) {

    /* Enable TX line */
    UCSR0B|= (1 << TXEN0);

    /* Start UART transmission - fill buffer*/
    UDR0 = c;

    while (!(UCSR0A & (1 << UDRE0))){
        /* Do nothing - stuck here*/
    }

    /* Disable TX line */
    UCSR0B&=~(1 << TXEN0);

    return 0;
}

/* Output file declaration for UART output redirection */
static FILE customStdOut = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);

}

UartPrintf::UartPrintf(Uart &uartInstance):
    /* Reference is not used, however ensures UART exists 
    before redirection is created -> therefore UART was initialized*/
    uart(uartInstance)
{
    /**
   Stream that will be used as an output stream by the simplified
   functions that don't take a \c stream argument.

   The first stream opened with write intent using \c fdevopen()
   will be assigned to both, \c stdin, and \c stderr.
    */
    stdout = &customStdOut;
}