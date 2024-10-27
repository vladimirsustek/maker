/*
 * cmd_ioport.hpp
 *
 *  Created on: Sep 1, 2024
 *      Author: 42077
 */

#ifndef CMD_DISPATCHER_THIS_APP_CMD_IOPORT_HPP_
#define CMD_DISPATCHER_THIS_APP_CMD_IOPORT_HPP_

#include "uart.hpp"

extern "C"
{
	#include <stdint.h>
}

static Uart *uart = nullptr;

void cmdDispOutInit()
{
	uart = Uart::getInstance();
}

void cmdDispOutMsg(char *pMsg, uint32_t lng)
{
	uart->write(reinterpret_cast<uint8_t*>(pMsg), lng);
}

void cmdDispOutMsg(const char *pMsg, uint32_t lng)
{
	uart->write(reinterpret_cast<uint8_t*>(const_cast<char*>(pMsg)), lng);
}

#endif /* CMD_DISPATCHER_THIS_APP_CMD_IOPORT_HPP_ */
