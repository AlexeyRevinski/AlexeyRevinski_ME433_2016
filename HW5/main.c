#include "PIC32_config.h"
#include "ILI9163C.h"
int main(void)
{
    SPI1_init();
    LCD_init();
    LCD_clearScreen(0x0000);
    LCD_drawPixel(120, 120, 0xFFFF);
    while(1){;}
}