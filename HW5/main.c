#include "PIC32_config.h"
#include "ILI9163C.h"
#include "i2c_master.h"
#include "utilities.h"
#include <stdio.h>

#define MARGIN 5

unsigned short txtcolor = WHITE;
unsigned short scrcolor = BLACK;

int main(void)
{
    int             c=0,i=0,average_count=0,data_ready=0;
    char            line[length];
    unsigned char   data[14];
    short           output[7],values[7] = {0,0,0,0,0,0,0};
    
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
    LCD_drawString(MARGIN,5 ,"Temp  :         C");
    LCD_drawString(MARGIN,20,"Gyro X:         mdps");
    LCD_drawString(MARGIN,35,"Gyro Y:         mdps");
    LCD_drawString(MARGIN,50,"Gyro Z:         mdps");
    LCD_drawString(MARGIN,65,"Accl X:         mg");
    LCD_drawString(MARGIN,80,"Accl Y:         mg");
    LCD_drawString(MARGIN,95,"Accl Z:         mg");
    
    
    while(1)
    {
        _CP0_SET_COUNT(0);
        if (c==7){data_ready = 0; c = 0;}
        i2c_master_read_all(IMU_ADDR,OUT_TEMP_L,14,data);
        char2short(data,output,14);
        output[0] = output[0]/16;
        output[1] = output[1]*875/100;
        output[2] = output[2]*875/100;
        output[3] = output[3]*875/100;
        output[4] = output[4]/16;
        output[5] = output[5]/16;
        output[6] = output[6]/16;
        i = 0;
        for(;i<7;i++){values[i] = (values[i]+output[i])/2;}
        if (average_count==9)
        {
            data_ready = 1;
            average_count = 0;
        }
        if (data_ready)
        {
            clearline(line);
            if (c==0)   {sprintf(line,"%d ",values[c]+25);}
            else        {sprintf(line,"%d ",values[c]);}
            LCD_drawString(MARGIN+8*6,c*15+MARGIN,line);
            values[c]=0;
            c++;
        }
        LATAbits.LATA4 = !LATAbits.LATA4;
        average_count++;
        while(_CP0_GET_COUNT()<UPDATER){;}
    }        
}

