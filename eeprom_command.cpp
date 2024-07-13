#include "eeprom_command.hpp"
#include "eeprom.hpp"
#include "uart.hpp"
#include "core.hpp"

constexpr uint16_t EEPROM_CMD_RD_BUFF_SIZE = 64;
constexpr uint16_t EEPROM_CMD_WR_BUFF_SIZE = 32;

extern "C"
{
    #include <stdio.h>
}

uint16_t PrintData(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
        CMD_DELIMITER_LNG*3 + CMD_ARG5_LNG*2+
        CMD_EOL_LNG) != lng) {

        return CMD_RET_ERR;
    }

    uint16_t address = (pStrCmd[CMD_ARG_OFFSET + 0] - '0')*10000;

    address += (pStrCmd[CMD_ARG_OFFSET + 1] - '0')*1000;
    address += (pStrCmd[CMD_ARG_OFFSET + 2] - '0')*100;
    address += (pStrCmd[CMD_ARG_OFFSET + 3] - '0')*10;
    address += (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;

    uint16_t length = (pStrCmd[CMD_ARG_OFFSET + 6] - '0')*10000;

    length += (pStrCmd[CMD_ARG_OFFSET + 7] - '0')*1000;
    length += (pStrCmd[CMD_ARG_OFFSET + 8] - '0')*100;
    length += (pStrCmd[CMD_ARG_OFFSET + 9] - '0')*10;
    length += (pStrCmd[CMD_ARG_OFFSET + 10] - '0')*1;

    Eeprom* eeprom = Eeprom::getInstance();
    Uart* uart = Uart::getInstance();

    if(address + length > EEPROM_MAX_SIZE)
    {
        return 0xFFFF;
    }

    uint8_t buffer[EEPROM_CMD_RD_BUFF_SIZE];
    uint16_t subLength = length;

    Core::disableInterruts();

    while(length != 0)
    {
        subLength = (length > EEPROM_CMD_RD_BUFF_SIZE) ? EEPROM_CMD_RD_BUFF_SIZE : length;
        eeprom->read(address, buffer, subLength);

        for(uint16_t i = 0; i < subLength; i++)
        {
            uart->write(reinterpret_cast<uint8_t*>(&buffer[i]), sizeof(uint8_t));
        }
        address += subLength;
        length -= subLength;

    }

    Core::enableInterrupts();


    return 0;

}

uint16_t WriteData(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if (((CMD_METHOD_LNG + CMD_NAME_LNG +
        CMD_DELIMITER_LNG*4 + CMD_ARG5_LNG*2+
        CMD_EOL_LNG) > lng) || (lng > UART_RX_BUFF_SIZE)) {

        return CMD_RET_ERR;
    }

    uint16_t address = (pStrCmd[CMD_ARG_OFFSET + 0] - '0')*10000;

    address += (pStrCmd[CMD_ARG_OFFSET + 1] - '0')*1000;
    address += (pStrCmd[CMD_ARG_OFFSET + 2] - '0')*100;
    address += (pStrCmd[CMD_ARG_OFFSET + 3] - '0')*10;
    address += (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;

    uint16_t length = (pStrCmd[CMD_ARG_OFFSET + 6] - '0')*10000;

    length += (pStrCmd[CMD_ARG_OFFSET + 7] - '0')*1000;
    length += (pStrCmd[CMD_ARG_OFFSET + 8] - '0')*100;
    length += (pStrCmd[CMD_ARG_OFFSET + 9] - '0')*10;
    length += (pStrCmd[CMD_ARG_OFFSET + 10] - '0')*1;

    Eeprom* eeprom = Eeprom::getInstance();

    if(address + length > EEPROM_MAX_SIZE && length > EEPROM_CMD_WR_BUFF_SIZE)
    {
        return 0xFFFF;
    }

    Core::disableInterruts();

    eeprom->write(address, const_cast<uint8_t*>(&(pStrCmd[CMD_ARG_OFFSET + 12])), length);

    Core::enableInterrupts();

    return 0;

}