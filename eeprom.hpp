#ifndef EEPROM_HPP
#define EEPROm_HPP

extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
}

constexpr uint16_t EEPROM_MAX_SIZE = 1024;

class EEPROM
{
public:
    static EEPROM* getInstance();
    void write(uint16_t address, uint8_t* data, uint16_t length);
    void read(uint16_t address, uint8_t* data, uint16_t length);
    void configureEEPROM();
private:
    static EEPROM* instance;
    EEPROM() = default;
    ~EEPROM() = default;
};

#endif