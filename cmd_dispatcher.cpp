#include "cmd_commands.hpp"
#include "cmd_defs.hpp"
#include "cmd_dispatcher.hpp"

#include "tone_command.hpp"
#include "eeprom_command.hpp"

constexpr uint CMD_TABLE_SIZE = 3u;

const CmdDisp_t cmdTable[CMD_TABLE_SIZE] = {

/*01*/    {method_play,  cmd_tone, TonePlay},
/*02*/    {method_read,  cmd_data, PrintData},
/*03*/    {method_write, cmd_data, WriteData}

};

uint16_t CommandDispatcher::Dispatch(const uint8_t* const pStrCmd, const uint8_t lng) {

    uint16_t result = CMD_RET_UKN;

    for(uint8_t idx = 0; idx < CMD_TABLE_SIZE; idx++) {
        if ((!memcmp(pStrCmd, cmdTable[idx].method.word, CMD_METHOD_LNG)) &&
        !memcmp(pStrCmd + CMD_METHOD_LNG + CMD_DELIMITER_LNG, cmdTable[idx].command.word, CMD_NAME_LNG)) {

            result = cmdTable[idx].cmdFunc(pStrCmd, lng);
            break;
        }
    }

    if(result)
    {
        printf("Err\n");
    }
    else
    {
        printf("OK\n");
    }

    return result;
}
