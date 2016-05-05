#include "PIC32_config.h"
#include "ILI9163C.h"
#include <stdio.h>

void clearline(char* line);
unsigned short txtcolor = WHITE;
unsigned short scrcolor = BLACK;
int main(void)
{
    int var = 1337;
    char line[length];
    clearline(line);
    SPI1_init();
    LCD_init();
    setTxtColor(GREEN);
    setScrColor(BLACK);
    LCD_clearScreen(scrcolor);
    sprintf(line,"Hello World %d!",var);
    LCD_drawString(28,32,line);
    clearline(line);
    setTxtColor(RED);
    LCD_drawString(5,100,"\"!\" outside screen!");
    while(1){;}
}

void clearline(char* line)
{
    int i=0;
    for(;i<length+1;i++)
    {
        line[i] = ' ';
    }
}