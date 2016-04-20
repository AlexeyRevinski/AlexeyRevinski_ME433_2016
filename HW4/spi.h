#ifndef DAC_H
#define DAC_H
void initSPI1();
void setVoltage(char channel, char voltage);
char SPI_IO(char write);
#endif