#include "pin_expander.h"
void initExpander(void)
{
    i2c_master_setup();
    ANSELBbits.ANSB2 = 0;       // I2C2 analog off;
}
void setExpander(char pin, char level)
{
    ;
}
char getExpander(char pin)
{
    ;
}