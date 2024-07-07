#ifndef CMD_PERIPHERALS_HPP
#define CMD_PERIPHERALS_HPP

#include "tone.hpp"


/* List of pointers to peripherals accesed by the command dispatcher. */
class Peripherals
{
public:
    Tone *tone;
};

#endif