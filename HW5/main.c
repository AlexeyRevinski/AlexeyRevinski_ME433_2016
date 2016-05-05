#include "PIC32_config.h"
#include "ILI9163C.h"
int main(void)
{
    SPI1_init();
    LCD_init();
    LCD_clearScreen(0x00FF);
    while(1){;}
}