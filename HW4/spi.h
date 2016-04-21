#ifndef DAC_H
#define DAC_H
#include <xc.h>

#define VoutA (char) 0x00
#define VoutB (char) 0x01
#define SS1   LATBbits.LATB15

void initSPI1();
void setVoltage(char channel, char voltage);
char SPI_IO(char write);
#endif