#include "tone_command.hpp"

uint16_t PlayTone(const uint8_t* const pStrCmd, const uint8_t lng, Peripherals* hardware)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
         CMD_DELIMITER_LNG*3 + CMD_ARG5_LNG*2+
         CMD_EOL_LNG) != lng) {

        return CMD_RET_ERR;
    }

    uint16_t freq = (pStrCmd[CMD_ARG_OFFSET + 0] - '0')*10000;

    freq += (pStrCmd[CMD_ARG_OFFSET + 1] - '0')*1000;
    freq += (pStrCmd[CMD_ARG_OFFSET + 2] - '0')*100;
    freq += (pStrCmd[CMD_ARG_OFFSET + 3] - '0')*10;
    freq += (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;

    uint16_t duration = (pStrCmd[CMD_ARG_OFFSET + 6] - '0')*10000;

    duration += (pStrCmd[CMD_ARG_OFFSET + 7] - '0')*1000;
    duration += (pStrCmd[CMD_ARG_OFFSET + 8] - '0')*100;
    duration += (pStrCmd[CMD_ARG_OFFSET + 9] - '0')*10;
    duration += (pStrCmd[CMD_ARG_OFFSET + 10] - '0')*1;

    hardware->tone->playTone(static_cast<Note>(freq), duration);

    return 0;
}