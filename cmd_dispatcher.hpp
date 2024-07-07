#ifndef CMD_DISPATCHER_HPP
#define CMD_DISPATCHER_HPP

#include "cmd_defs.hpp"
#include "tone.hpp"

class CommandDispatcher
{
public: 
    CommandDispatcher(Peripherals& peripherals);
    uint16_t Dispatch(const uint8_t* const pStrCmd, const uint8_t lng);
private:
    Peripherals& peripherals;
};

#endif // CMD_DISPATCHER_H_INCLUDED
