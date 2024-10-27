#ifndef SPI_HPP
#define SPI_HPP

extern "C"
{
    #include <stdio.h>
    #include <avr/io.h>
}

class Spi
{
public:
    static Spi* getInstance();
    uint16_t write(uint8_t *pData, uint16_t size);
    uint16_t read(uint8_t* pData, uint16_t size);
    uint16_t writeAndRead(uint8_t *pWrData, uint8_t* pReadData, uint16_t size);
private:
    void enableMasterSpi();
    Spi() = default;
    ~Spi() = default;
    static Spi* instance;
};

#endif 