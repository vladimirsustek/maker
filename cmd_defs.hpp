#ifndef CMD_DEFS_HPP
#define CMD_DEFS_HPP

extern "C"
{
    #include "string.h"
    #include "stdio.h"
    #include "stdint.h"
}

#define CMD_EOL_LNG         ((1u))
#define CMD_DELIMITER_LNG   ((1u))
#define CMD_DELIMITER       (('_'))

#define CMD_PLATFORM_LNG    ((0u))

#define CMD_METHOD_LNG      ((2u+1u))
#define CMD_NAME_LNG        ((4u+1u))

#define CMD_ARG1_LNG        ((1u))
#define CMD_ARG2_LNG        ((2u))
#define CMD_ARG5_LNG        ((5u))

#define CMD_ARG_OFFSET      (CMD_PLATFORM_LNG + CMD_NAME_LNG + CMD_METHOD_LNG + CMD_DELIMITER_LNG*2)

#define CMD_RET_OK          ((0x0))
#define CMD_RET_ERR         ((0xFFFF))
#define CMD_RET_UKN         ((0xF0F0))

typedef uint16_t (*pfn_u8_cpuc8cu8)(const uint8_t* const, const uint8_t lng);

typedef struct CmdDisp {

    uint8_t cmdMethod[CMD_METHOD_LNG];
    uint8_t cmdName[CMD_NAME_LNG];
    pfn_u8_cpuc8cu8 cmdFunc;
} CmdDisp_t;

#endif // CMD_DEFS_H_INCLUDED
