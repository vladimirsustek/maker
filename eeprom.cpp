#include "eeprom.hpp"

EEPROM::EEPROM()
{
    /* Erase and write wihin a single cycle (3.4ms) */
    EECR &= ~((1 << EEPM0) | (1 << EEPM0));
}

EEPROM::~EEPROM()
{

}

void EEPROM::write(uint16_t address, uint8_t* data, uint16_t length)
{
    uint16_t lng = length;
    while(lng)
    {
        /* Wait for completion of previous write */
        while(EECR & (1<<EEPE))
        ;
        /* Set up address and Data Registers */
        EEAR = address;
        EEDR = *data;
        /* Write logical one to EEMPE */
        EECR |= (1<<EEMPE);
        /* Start eeprom write by setting EEPE */
        EECR |= (1<<EEPE);

        data++;
        lng--;
    }

}

void EEPROM::read(uint16_t address, uint8_t* data, uint16_t length)
{
    uint16_t lng = length;
    uint16_t idx = 0;

    while(lng)
    {
        /* Wait for completion of previous write */
        while(EECR & (1<<EEPE))
        ;
        /* Set up address register */
        EEAR = address;
        /* Start eeprom read by writing EERE */
        EECR |= (1<<EERE);
        /* Return data from Data Register */
        data[idx] = EEDR;
        lng--;
        address++;

    }
}