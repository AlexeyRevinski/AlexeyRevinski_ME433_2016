#include "spi.h"
void initSPI1()
{
    SDI1Rbits.SDI1R     = 0b0100;//SDI1 - RPB8
    RPB13Rbits.RPB13R   = 0b0011;//SDO1 - RPB13
    RPB15Rbits.RPB15R   = 0b0011;//SS1  - RPB15
}
void setVoltage(char channel, char voltage)
{
    ;
}
char SPI_IO(char write)
{
    ;
}