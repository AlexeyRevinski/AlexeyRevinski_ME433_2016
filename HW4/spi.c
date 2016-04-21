#include "spi.h"
void initSPI1()
{
    // PIN ASSIGNMENTS
    TRISBbits.TRISB8    = 0;        //Slave Select 1 pin
    SS1                 = 1;        //SS1 to high - no communication             
    SDI1Rbits.SDI1R     = 0b0100;   //SDI1 - RPB8
    RPB13Rbits.RPB13R   = 0b0011;   //SDO1 - RPB13
    
    //SPI1 SFRS
    SPI1CON             = 0;  // turn off the spi module and reset it
    SPI1CONbits.MSSEN   = 0;  // manual toggle
    SPI1CONbits.CKP     = 0;  // active = high; idle = low
    SPI1CONbits.CKE     = 0;  // data clocked when going from i->a, so low->high (rising edge)
    SPI1CONbits.MSTEN   = 1;  // PIC32 is the master
    SPI1CONbits.ON      = 1;  // turn on spi 1
    SPI1CONbits.MODE16  = 1;  // 16 bit word transfer
    SPI1CONbits.SMP     = 1;  // No input from MCP4902 - shouldn't matter
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1BUF;                  // clear the rx buffer
    SPI1BRG             = 0x176;// baud rate to 64kHz [SPI1BRG = (48000000/(2*64000))-1]
}
void setVoltage(char channel, char voltage)
{
    ;
}

unsigned char spi_io(unsigned char buf) {
  SPI1BUF = buf;
  while(!SPI1STATbits.SPIRBF) {;}
  return SPI1BUF;
}