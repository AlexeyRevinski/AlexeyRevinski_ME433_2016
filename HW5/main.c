#include "PIC32_config.h"
#include "ILI9163C.h"

int main(void)
{
    SPI1_init();
    LCD_init();
    LCD_clearScreen(0x0000);
    //{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
    LCD_drawChar('H');
    while(1){;}
}