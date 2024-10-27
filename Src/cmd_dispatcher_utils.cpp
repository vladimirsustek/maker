#include "cmd_dispatcher_util.hpp"


uint8_t readBuffer[26] = {0};
uint8_t writeBuffer[26] = {0};

void hex2AsciiHex_andPrint(const uint8_t *pArr, uint8_t arrLng, pfn_u8_cu8 fn)
{
    if (pArr == nullptr || fn == nullptr)
    {
        return;
    }
    for(uint16_t k = 0; k < arrLng; k++)
    {
        const uint8_t space = static_cast<uint8_t>(' ');
        uint8_t upperNible = (pArr[k] & 0xF0) >> 4;
        uint8_t lowerNible = (pArr[k] & 0x0F);

        if(upperNible >= 0 && upperNible<= 9)
        {
            upperNible+= '0';
        }
        else
        {
            upperNible = (upperNible - 0xA) + 'A';
        }

        if(lowerNible >= 0 && lowerNible<= 9)
        {
            lowerNible += '0';
        }
        else
        {
            lowerNible = (lowerNible - 0xA) + 'A';
        }
        /*
        fn->write(&upperNible, sizeof(uint8_t));
        uart->write(&lowerNible, sizeof(uint8_t));
        uart->write(const_cast<uint8_t*>(&space), sizeof(uint8_t));
        */
    }
}

uint8_t asciiHex2Hex(uint8_t *inArr, uint8_t inArrLng, uint8_t* outArr, uint8_t outArrLng)
{

    if(inArr == nullptr || outArr == nullptr)
    {
            return static_cast<uint8_t>(-1);
    }

    if(outArrLng != (inArrLng>>1))
    {
            return static_cast<uint8_t>(-2);
    }

    for(uint16_t i = CMD_ARG_OFFSET+3; i < outArrLng*2+CMD_ARG_OFFSET+3; i++)
    {
        uint8_t nibble;

        if(inArr[i] >= '0' && inArr[i] <= '9')
        {
            nibble = inArr[i] - '0';
        }
        else if (inArr[i] >= 'A' && inArr[i] <= 'F')
        {
            nibble = inArr[i] -'A' + 10;
        }
        else if (inArr[i] >= 'A' && inArr[i] <= 'F')
        {
            nibble = inArr[i] -'a' + 10;
        }
        else
        {
            return static_cast<uint8_t>(-3);
        }

        uint8_t idx = i - (CMD_ARG_OFFSET+3);

        /* %2 even odd splitter */
        if ((idx & 1u) == 0)
        {
            writeBuffer[idx>>1] = (nibble << 4);
        }
        else
        {
            writeBuffer[idx>>1] |= nibble;
        }
    }

    return static_cast<uint8_t>(0);

}

uint8_t* getReadBuffer()
{
    return readBuffer;
}

uint8_t* getWriteBuffer()
{
    return writeBuffer;
}