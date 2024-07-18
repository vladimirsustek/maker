#ifndef UART_HPP
#define UART_HPP

/***********************************************************************/
/*****************    Includes   ***************************************/
/***********************************************************************/

extern "C"
{
    #include <string.h>
    #include <stdio.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
}

#include "IPeripheral.hpp"

/***********************************************************************/
/*****************    Private macro *  *********************************/
/***********************************************************************/

/* Defined speed of UART stage in Baud, note that 57600 is maximal */
#define USART_BAUDRATE      (uint16_t)(57600)
/* Calculating prescaler to set an appropriate baud speed */
#define BAUD_PRESCALE       (uint16_t)(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Macro to substitute set bit of the UART busy line */
#define UART_BUFF_BUSY      (!(UCSR0A & (1 << UDRE0)))
/***********************************************************************/
/*****************    Public macro *************************************/
/***********************************************************************/

#define RX_ISR_ENAB             (uint8_t)(1u)
#define RX_ISR_DISAB            (uint8_t)(0u)
#define UART_RX_BUFF_SIZE       (uint8_t)(64u)

#define UART_ISR_MODE           (uint8_t)(1u)
/***********************************************************************/
/*****************    Public functions    ******************************/
/***********************************************************************/

class Uart : IPeripheral
{
public:
    Uart& operator=(const Uart& other) = delete;
    Uart(Uart & t) = delete;
    static Uart* getInstance();
    void enableRxISR(bool en);
    uint16_t write(uint8_t* pData, uint16_t size);
    uint16_t readLine(uint8_t* pData, uint16_t size);
    uint16_t read(uint8_t*, uint16_t) {return 0;};
    uint16_t isRxISR(void);
    uint16_t isTxISR(void);
    uint16_t isTXBusy(void);
private:
    Uart() = default;
    ~Uart() = default;
    void enable8BitUart();
    static Uart* instance;
};

#endif // UART_HPP
