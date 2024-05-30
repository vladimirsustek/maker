/*
 * Created by Vladimir Sustek, 23.6.2019
 *
 * Feel free to use/modify/whatever
 *
**/
/***********************************************************************/
/*****************    Includes   ***************************************/
/***********************************************************************/
#include "uart.hpp"

/***********************************************************************/
/*****************    Private macro *  *********************************/
/***********************************************************************/

/* Defined speed of UART stage in Baud, note that 57600 is maximal */
#define USART_BAUDRATE      (uint16_t)(57600)
/* Calculating prescaler to set an appropriate baud speed */
#define BAUD_PRESCALE       (uint16_t)(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Macro to substitute set bit of the UART busy line */
#define UART_BUFF_BUSY      (!(UCSR0A & (1 << UDRE0)))


#define DEBUG_PRINT        0

/***********************************************************************/
/*****************    Private data     *********************************/
/***********************************************************************/

/* @brief Disable UART interrupt (so its ISR)
 *
 *
 */
static void uart_enter_critical(void) {
    UCSR0B &=~(1 << RXCIE0);
}
/* @brief Enable UART interrupt (so its ISR)
 *
 *
 */
static void uart_exit_critical(void) {
    UCSR0B |=(1 << RXCIE0);
}

/* @brief USART RX ISR handler
 *
 * Functions stores received characters into the
 * static buffer (owned by this module) to the array
 * inner_buffer. In case of received <LF> character
 * or if more than UART_RX_BUFF_SIZE is received
 * without any reading the uart_lf_flag is set and
 * user may handle this event as the further receive
 * is disabled (RX interrupt disabled).
 *
 * @sa uart_received_LF
 * @sa uart_copy_buffer
 *
 */
ISR(USART_RX_vect)
{
    uart_enter_critical();
    volatile uint8_t iUDR0 = UDR0;
    (void)iUDR0;
    uart_exit_critical();
}

Uart::Uart(bool isr_enable_flag)
{
    /* Use 8 - bit size of transaction symbol */
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    /* Upper part of bitrate 57600*/
    UBRR0H |= (BAUD_PRESCALE >> 8);
    /* Lower part of bitrate 57600 */
    UBRR0L |= BAUD_PRESCALE;
    /* Enable Interrupt on receive */
    if(isr_enable_flag) {
            UCSR0B |= (1 << RXCIE0);
    }
    /* Force off the TX and RX for further enabling */
    UCSR0B &= ~(1 << RXEN0) | ~(1 << TXEN0);
}

Uart::~Uart()
{
    
}

uint16_t Uart::write(uint8_t* pData, uint16_t size)
{

    uint16_t idx;

    /* Enable TX line */
    UCSR0B|= (1 << TXEN0);

    for (idx = 0; idx < size; idx++)
    {
        /* Start UART transmission - fill buffer*/
        UDR0 = pData[idx];

        while (UART_BUFF_BUSY){
            /* Do nothing - stuck here*/
        }
    }

    /* Disable TX line */
    UCSR0B&=~(1 << TXEN0);

    return idx;
}

uint16_t Uart::read(uint8_t* pData, uint16_t size)
{
    uint16_t idx = 0;

    return idx;
}

uint16_t Uart::isRxISR(void)
{
    return 0;
}

uint16_t Uart::isTxISR(void)
{
    return 0;
}

uint16_t Uart::isTXBusy(void)
{
    if(!(UCSR0A & (1 << UDRE0)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/* Needed when pure virtual function is used. Normally comes with libstd++, but
 * for avr-g++ must be this declared explicitely. */
extern "C" void __cxa_pure_virtual(void) 
{
    while(1);
}


