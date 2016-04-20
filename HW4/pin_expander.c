#include "pin_expander.h"
void initExpander(char IO_dir)
{
    ANSELBbits.ANSB2 = 0;       // I2C2 analog off;
    i2c_master_setup();
    //i2c_master_write(GPIO,IO_dir);
}
void setExpander(char pin, char level)
{    
    ;
}
char getExpander(char pin)
{
    ;
}