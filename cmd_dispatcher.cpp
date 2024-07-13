#include "cmd_commands.hpp"
#include "cmd_defs.hpp"
#include "cmd_dispatcher.hpp"
#include "tone_command.hpp"

constexpr uint CMD_TABLE_SIZE = 1u;

const CmdDisp_t cmdTable[CMD_TABLE_SIZE] = {

/*01*/    {method,  command, TonePlay}

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
    /* printf redirected to UART in the uartprintf. */
    //printf("<< %s>> RET = 0x%04x\n", pStrCmd, result);

    return result;
}
