#ifndef CMD_DEFS_HPP
#define CMD_DEFS_HPP

extern "C"
{
    #include "string.h"
    #include "stdio.h"
    #include "stdint.h"
}


constexpr uint32_t CMD_EOL_LNG=1u;
constexpr uint8_t CMD_EOL = '\n';
constexpr uint32_t CMD_DELIMITER_LNG=1u;
constexpr char CMD_DELIMITER='_';

constexpr uint32_t CMD_PLATFORM_LNG	=0u;

constexpr uint32_t CMD_METHOD_LNG=2u;
constexpr uint32_t CMD_NAME_LNG=4u;

constexpr uint32_t CMD_ARG1_LNG=1u;
constexpr uint32_t CMD_ARG5_LNG=5u;

constexpr uint32_t CMD_ARG_OFFSET=(CMD_PLATFORM_LNG + CMD_NAME_LNG + CMD_METHOD_LNG + CMD_DELIMITER_LNG*2);

constexpr uint32_t CMD_RET_OK = 0x0;
constexpr uint32_t CMD_RET_ERR = 0xFFFF;
constexpr uint32_t CMD_RET_ARG_ERR = 0x0F0F;
constexpr uint32_t CMD_RET_UKN = 0xF0F0;

typedef uint32_t (*pfn_u32_cpuc8cu8)(const uint8_t* const, const uint8_t lng);

typedef enum {NOARG = 0, DEC_UI16 = 1} cmdType_e;

typedef struct
{
	cmdType_e etype;
	const char* str;

}argTypeLUT_t;

typedef struct CommandAr
{
	cmdType_e type;
	uint32_t min;
	uint32_t max;
} CommandArg;

typedef struct DispatcherCommand
{
	pfn_u32_cpuc8cu8 function;
	const CommandArg arg;

} DispatcherCommand_t;

class METHOD
{
public:
    METHOD(const char* p) {strcpy(const_cast<char*>(word), const_cast<char*>(p));}
    char word[3];
};

class COMMAND
{
public:
    COMMAND(const char* p) {strcpy(const_cast<char*>(word), const_cast<char*>(p));}
    char word[4];
};


typedef struct CmdDisp{
    METHOD method;
    COMMAND command;
    DispatcherCommand_t cmdFunc;
} CmdDisp_t;

const CommandArg DEC_UI16_BOOL =
{
		DEC_UI16, 0, 1
};

const CommandArg NO_ARG =
{
		NOARG, 0, 0
};

const argTypeLUT_t argTypeLUTtable[2] =
{
		{NOARG, "NOARG"},
		{DEC_UI16, "DEC_UI16"}

};

#endif // CMD_DEFS_H_INCLUDED
