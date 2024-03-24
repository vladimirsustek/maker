extern "C"
{
    #include <stdint.h>
}

class IPeripheral
{
public:
    virtual uint16_t write(uint8_t* pData, uint16_t size) = 0;
    virtual uint16_t read(uint8_t* pData, uint16_t size) = 0;
    virtual uint16_t isRxISR(void) = 0;
    virtual uint16_t isTxISR(void) = 0;
};