#ifndef CMD_COMMANDS_HPP
#define CMD_COMMANDS_HPP

#include "cmd_defs.hpp"

/*** BASIC METHODS ***/
const METHOD method_play = METHOD("PL");
const METHOD method_read = METHOD("RD");
const METHOD method_write = METHOD("WR");

/** COMMANDS */
const COMMAND cmd_tone = COMMAND("TONE"); //Tone
const COMMAND cmd_data = COMMAND("EEPR");

#endif // CMD_COMMANDS_H_INCLUDED
