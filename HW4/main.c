#include "PIC32_config.h"
#define  WAIT_TIME 12000

int main()
{
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 1;			// LED is on
    ANSELBbits.ANSB2 = 0;       // I2C2 analog off
    __builtin_enable_interrupts();
    
    while(1)
    {
	    // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
        _CP0_SET_COUNT(0);
        LATAINV = 0b10000;
        for(;_CP0_GET_COUNT()<(WAIT_TIME+1);)
        {
            while(!PORTBbits.RB4){;}
        }
    }   
}