/*
 * cmd_table.hpp
 *
 *  Created on: Sep 1, 2024
 *      Author: 42077
 */

#ifndef CMD_DISPATCHER_THIS_APP_CMD_TABLE_HPP_
#define CMD_DISPATCHER_THIS_APP_CMD_TABLE_HPP_

#include "../Inc/tone_command.hpp"
#include "../Inc/eeprom_command.hpp"
#include "../Inc/pwm_command.hpp"
#include "../Inc/spi_command.hpp"

constexpr uint32_t HELP_MAX_LINE_LNG = 64u;
constexpr uint32_t CMD_TABLE_SIZE = 7u;

const CmdDisp_t cmdTable[CMD_TABLE_SIZE] = {
/*01*/    {method_play,             cmd_tone,               TonePlay},
/*02*/    {method_play,             cmd_sedmikrasky,        PlaySedmikrasky},
/*03*/    {method_enable,           cmd_pwm,                EnablePWM_OC2B},
/*04*/    {method_write,            cmd_pwm,                SetPWM_OC2B},
/*05*/    {method_read,             cmd_data,               PrintData},
/*06*/    {method_write,            cmd_data,               WriteData},
/*07*/    {method_write,            cmd_spi,                NULL}
};

#endif /* CMD_DISPATCHER_THIS_APP_CMD_TABLE_HPP_ */
