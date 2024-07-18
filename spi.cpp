#include "spi.hpp"

#include <stdio.h>

Spi* Spi::instance = nullptr;

/* PB5=CLOCK (17), PB4=MISO (16), PB3=MOSI (15), PB2=NSS (14)*/
constexpr uint8_t SPI_CLOCK_PIN = PORTB5;
constexpr uint8_t SPI_MISO_PIN = PORTB4;
constexpr uint8_t SPI_MOSI_PIN = PORTB3;
constexpr uint8_t SPI_NSS_PIN = PORTB2;

Spi* Spi::getInstance()
{
    if(instance == nullptr)
    {
        static Spi singletonSpi;
        singletonSpi.enableMasterSpi();
        instance = reinterpret_cast<Spi*>(&singletonSpi);
    }
    return instance;
}

uint16_t Spi::write(uint8_t *pData, uint16_t size)
{
    PORTB &= ~(1 << SPI_NSS_PIN);

    for(uint16_t i = 0; i < size; i++)
    {
        /* Start transmission */
        SPDR = pData[i];
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)))
        ;
    }

    PORTB |= (1 << SPI_NSS_PIN);

    return 0;

}

uint16_t Spi::read(uint8_t *pData, uint16_t size)
{
    PORTB &= ~(1 << SPI_NSS_PIN);

    for(uint16_t i = 0; i < size; i++)
    {
        /* Start transmission */
        SPDR = 0;
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)))
        ;
        pData[i] = SPDR;
    }

    PORTB |= (1 << SPI_NSS_PIN);

    return 0;

}

uint16_t Spi::writeAndRead(uint8_t *pWrData, uint8_t* pReadData, uint16_t size)
{
    PORTB &= ~(1 << SPI_NSS_PIN);

    for(uint16_t i = 0; i < size; i++)
    {
        /* Start transmission */
        SPDR = pWrData[i];
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)))
        ;

        pReadData[i] = SPDR;
    }
    PORTB |= (1 << SPI_NSS_PIN);

    return 0;

}

void Spi::enableMasterSpi()
{
    /* Set MOSI and SCK output, all others input */

    /* PB5=CLOCK (17), PB4=MISO (16), PB3=MOSI (15), PB2=NSS (14)*/
    DDRB |= (1 << SPI_CLOCK_PIN | 1 << SPI_MOSI_PIN | 1 << SPI_NSS_PIN); // output
    DDRB &= ~(1 << SPI_MISO_PIN); // input

    //NSS high
    PORTB |= (1 << SPI_NSS_PIN);

    /* Enable SPI, Master, CLK/16*/
    SPCR |= (1<<SPE)|(1<<MSTR)|(1 << SPR0);
    /* MS-bit first, CPHA and CPOL = 0 */
    SPCR &= ~((1<<DORD)|(1<<CPHA)|(1<<CPOL));
}
