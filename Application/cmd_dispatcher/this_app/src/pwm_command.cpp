#include "pwm_command.hpp"

#include "tim.hpp"

uint32_t EnablePWM_OC2B(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
         CMD_DELIMITER_LNG*2 + CMD_ARG5_LNG+
         CMD_EOL_LNG) != lng) {

        return CMD_RET_ERR;
    }

    uint16_t enable_arg = (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;
    if(enable_arg != 0u && enable_arg != 1u)
    {
        return CMD_RET_ERR;
    }

    bool enable = static_cast<bool>(enable_arg);
    Tim* tim = Tim::getInstance();
    tim->enableFastPWM_OC2B(enable);

    return 0;
}



uint32_t SetPWM_OC2B(const uint8_t* const pStrCmd, const uint8_t lng)
{
    if ((CMD_METHOD_LNG + CMD_NAME_LNG +
         CMD_DELIMITER_LNG*2 + CMD_ARG5_LNG+
         CMD_EOL_LNG) != lng) {

        return CMD_RET_ERR;
    }

    uint16_t period = (pStrCmd[CMD_ARG_OFFSET + 0] - '0')*10000;

    period += (pStrCmd[CMD_ARG_OFFSET + 1] - '0')*1000;
    period += (pStrCmd[CMD_ARG_OFFSET + 2] - '0')*100;
    period += (pStrCmd[CMD_ARG_OFFSET + 3] - '0')*10;
    period += (pStrCmd[CMD_ARG_OFFSET + 4] - '0')*1;

    if(period > UINT8_MAX)
    {
        return CMD_RET_ERR;
    }

    Tim* tim = Tim::getInstance();

    tim->setPWM_OC2B(static_cast<uint8_t>(period));

    return 0;
}