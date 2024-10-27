#ifndef CMD_COMMANDS_HPP
#define CMD_COMMANDS_HPP

#include "cmd_defs.hpp"

/*** BASIC METHODS ***/
const METHOD method_play = METHOD("PL");
const METHOD method_read = METHOD("RD");
const METHOD method_write = METHOD("WR");
const METHOD method_enable = METHOD("EN");
const METHOD method_transceive =METHOD("TR");

/** COMMANDS */
const COMMAND cmd_tone = COMMAND("TONE");
const COMMAND cmd_sedmikrasky = COMMAND("SDMK");
const COMMAND cmd_data = COMMAND("EEPR");
const COMMAND cmd_pwm = COMMAND("PWM2");
const COMMAND cmd_spi = COMMAND("SPI0");

#endif // CMD_COMMANDS_H_INCLUDED
