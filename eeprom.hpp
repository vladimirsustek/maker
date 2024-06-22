#ifndef EEPROM_HPP
#define EEPROm_HPP

extern "C"
{
#include <avr/io.h>
//#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
}

class EEPROM
{
public:
    EEPROM();
    ~EEPROM();
    void write(uint16_t address, uint8_t* data, uint16_t length);
    void read(uint16_t address, uint8_t* data, uint16_t length);
};

#endif