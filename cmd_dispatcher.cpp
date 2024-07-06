#include "cmd_commands.hpp"
#include "cmd_defs.hpp"

#define CMD_TABLE_SIZE  (1u)

uint16_t HelloCommand(const uint8_t* const ptr, const uint8_t lng)
{
    (void)ptr;
    (void)lng;
    printf("HelloCommand:%s\n", ptr);
    return 0;
}

static const CmdDisp_t cmdTable[CMD_TABLE_SIZE] = {

/*01*/    {CMD_METHOD_DO,  CMD_HELLOCMD_INIT, HelloCommand}

};

uint16_t CmdDispatch(const uint8_t* const pStrCmd, const uint8_t lng) {

    uint16_t result = CMD_RET_UKN;

    for(uint8_t idx = 0; idx < CMD_TABLE_SIZE; idx++) {
        if ((!memcmp(pStrCmd, cmdTable[idx].cmdMethod, CMD_METHOD_LNG-1)) &&
        !memcmp(pStrCmd + CMD_METHOD_LNG-1 + CMD_DELIMITER_LNG, cmdTable[idx].cmdName, CMD_NAME_LNG-1)) {

            result = cmdTable[idx].cmdFunc(pStrCmd, lng-1);
            printf("Match hit\n");
            break;
        }
    }
    /* printf redirected to UART in the uartprintf. */
    printf("<< %s  >> RET = 0x%04x\n", pStrCmd, result);

    return result;
}
