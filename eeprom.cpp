#include "eeprom.hpp"

/* // Find out how to implement eeprom_busy_wait, eeprom_write_byte
void EEPROM::write(uint16_t address, uint8_t* data, uint16_t length)
{
    eeprom_busy_wait();
    eeprom_write_byte(reinterpret_cast<uint8_t*>(0), 0xAA);
}
*/
EEPROM* EEPROM::instance = nullptr;

EEPROM* EEPROM::getInstance()
{
    if(instance == nullptr)
    {
        static EEPROM singletonEEPROM;
        singletonEEPROM.configureEEPROM();
        instance = &singletonEEPROM;
    }
    return instance;
}

void EEPROM::write(uint16_t address, uint8_t* data, uint16_t length)
{
    uint16_t lng = length;

    if ((data == NULL) || (length > EEPROM_MAX_SIZE) || (address + length > EEPROM_MAX_SIZE))
    {
        return ;
    }

    while(lng)
    {
        eeprom_busy_wait();
        eeprom_write_byte(reinterpret_cast<uint8_t*>(address), *data);

        data++;
        address++;
        lng--;

    }
}

// Find out how to implement eeprom_busy_wait, eeprom_write_byte
void EEPROM::read(uint16_t address, uint8_t* data, uint16_t length)
{
    uint16_t lng = length;
    uint16_t idx = 0;

    if ((data == NULL) || (length > EEPROM_MAX_SIZE) || (address + length > EEPROM_MAX_SIZE))
    {
        return ;
    }

    while(lng)
    {
        eeprom_busy_wait();
        data[idx]  = eeprom_read_byte(const_cast<const uint8_t*>(reinterpret_cast<uint8_t*>(address)));
        lng--;
        address++;
        idx++;
    }
}

void EEPROM::configureEEPROM()
{
    /* Erase and write wihin a single cycle (3.4ms) */
    EECR &= ~((1 << EEPM0) | (1 << EEPM0));
}