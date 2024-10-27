#include "cmd_commands.hpp"
#include "cmd_defs.hpp"
#include "cmd_dispatcher.hpp"
#include "uart.hpp"

#include "tone_command.hpp"
#include "eeprom_command.hpp"
#include "pwm_command.hpp"
#include "spi_command.hpp"

constexpr uint CMD_TABLE_SIZE = 7u;

const CmdDisp_t cmdTable[CMD_TABLE_SIZE] = {

/*01*/    {method_play,             cmd_tone,               TonePlay},
/*02*/    {method_play,             cmd_sedmikrasky,        PlaySedmikrasky},
/*03*/    {method_read,             cmd_data,               PrintData},
/*04*/    {method_write,            cmd_data,               WriteData},
/*05*/    {method_enable,           cmd_pwm,                EnablePWM_OC2B},
/*06*/    {method_write,            cmd_pwm,                SetPWM_OC2B},
/*07*/    {method_write,            cmd_spi,                NULL}

};

uint16_t CommandDispatcher::Dispatch(const uint8_t* const pStrCmd, const uint8_t lng) {

    uint16_t result = CMD_RET_UKN;
    const char STR_CMD_OK[] = "CMD_OK\n";
    const char STR_CMD_ERR[] = "CMD_ERR\n";
    const char STR_CMD_UKN[] = "CMD_UKN\n";
    const char STR_CMD_FTL[] = "CMD_FTL\n";

    Uart *uart = Uart::getInstance();

    for(uint8_t idx = 0; idx < CMD_TABLE_SIZE; idx++) {
        if ((!memcmp(pStrCmd, cmdTable[idx].method.word, CMD_METHOD_LNG)) &&
        !memcmp(pStrCmd + CMD_METHOD_LNG + CMD_DELIMITER_LNG, cmdTable[idx].command.word, CMD_NAME_LNG)) {

            result = cmdTable[idx].cmdFunc(pStrCmd, lng);
            break;
        }
    }

    switch(result)
    {
        case CMD_RET_OK : 
        {
            uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>(STR_CMD_OK)), strlen(STR_CMD_OK));
        }
        break;
        case CMD_RET_ERR : 
        {
            uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>(STR_CMD_ERR)), strlen(STR_CMD_ERR));
        }
        break;
        case CMD_RET_UKN : 
        {
            uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>(STR_CMD_UKN)), strlen(STR_CMD_UKN));
        }
        break;
        default : 
        {
            uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>(STR_CMD_FTL)), strlen(STR_CMD_FTL));
        }
    }

    return result;
}
