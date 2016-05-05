#include "PIC32_config.h"
#include "ILI9163C.h"
#include <stdio.h>

int main(void)
{
    char str[25];
    sprintf(str,"Hello World 1337!");
    SPI1_init();
    LCD_init();
    LCD_clearScreen(0x0000);
    LCD_drawString(20,20,str,9);
    //LCD_drawChar(20,20,str[1]);
    while(1){;}
}