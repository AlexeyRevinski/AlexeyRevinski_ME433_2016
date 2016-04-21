#include "pin_expander.h"
void initExpander(char IO_dir)
{
    ANSELBbits.ANSB2 = 0;       // I2C2 analog off;
    ANSELBbits.ANSB3 = 0;       // I2C2 analog off;
    i2c_master_setup();
    i2c_master_write(IODIR,IO_dir);
}
void setExpander(char pin, char level)
{
    char read_byte,write_byte;
    read_byte = i2c_master_read(OLAT);
    if (level==0)
    {
        write_byte = read_byte&~(pin);
    }
    else if (level==1)
    {
        write_byte = read_byte|pin;
    }
    i2c_master_write(OLAT,write_byte);
}
char getExpander(char pin)
{
    ;
}