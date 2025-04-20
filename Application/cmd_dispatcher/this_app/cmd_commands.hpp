#ifndef CMD_COMMANDS_HPP
#define CMD_COMMANDS_HPP

#include "cmd_defs.hpp"

/*** BASIC METHODS ***/
const METHOD method_play = METHOD("PL\0");
const METHOD method_read = METHOD("RD\0");
const METHOD method_write = METHOD("WR\0");
const METHOD method_enable = METHOD("EN\0");
const METHOD method_transceive =METHOD("TR\0");

/** COMMANDS */
const COMMAND cmd_tone = COMMAND("TONE\0");
const COMMAND cmd_sedmikrasky = COMMAND("SDMK\0");
const COMMAND cmd_data = COMMAND("EEPR\0");
const COMMAND cmd_pwm = COMMAND("PWM2\0");
const COMMAND cmd_spi = COMMAND("SPI0\0");

#endif // CMD_COMMANDS_H_INCLUDED
