#include "PIC32_config.h"
#include "ILI9163C.h"
#include "i2c_master.h"
#include "utilities.h"
#include <stdio.h>


unsigned short txtcolor = WHITE;
unsigned short scrcolor = BLACK;

int main(void)
{
    int             var = 1337;
    char            line[length];
    char            whoami_check = 0;
    unsigned char   data[14];
    short           output[7];
    int             oc1_new=0,oc2_new=0;
    // Setup
    __builtin_disable_interrupts();
     __builtin_mtc0(_CP0_CONFIG,_CP0_CONFIG_SELECT,0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    SPI1_init();
    LCD_init();
    i2c_master_setup();
    __builtin_enable_interrupts();
    
    setTxtColor(GREEN);
    setScrColor(BLACK);
    clearline(line);
    LCD_clearScreen(scrcolor);
    sprintf(line,"Hello World %d!",var);
    LCD_drawString(28,32,line);
    clearline(line);
    setTxtColor(RED);
    LCD_drawString(5,100,"\"!\" outside screen!");
    
    
    /*
    whoami_check = i2c_master_read(IMU_ADDR,WHO_AM_I);
    if (whoami_check == WHOAMI_VAL)
    {
        LATAbits.LATA4 = 1;
    }*/
    
    while(1)
    {
        _CP0_SET_COUNT(0);
        i2c_master_read_all(IMU_ADDR,OUT_TEMP_L,14,data);
        char2short(data,output,14);
        oc1_new = (PER2+1)/2+(output[4]/20);
        oc2_new = (PER2+1)/2+(output[5]/20);
        LATAbits.LATA4 = !LATAbits.LATA4;
        while(_CP0_GET_COUNT()<UPDATER){;}
    }        
}

