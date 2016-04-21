#ifndef DAC_H
#define DAC_H

#define VoutA (char) 0x00
#define VoutB (char) 0x01

void initSPI1();
void setVoltage(char channel, char voltage);
char SPI_IO(char write);
#endif