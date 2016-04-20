#include "PIC32_config.h"

int main()
{
    __builtin_disable_interrupts();

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);

    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;

    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;

    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    
    // do your TRIS and LAT commands here
    
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 1;			// LED is on
    
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