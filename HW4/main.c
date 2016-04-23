#include "PIC32_config.h"
#define  LEVELS     (int)       256
#define  PI         (double)    3.14159265
#define  I2C_FREQ   (int)       12000000
#define  PIC_FREQ   (int)       48000000
#define  A_FREQ     (int)       10
#define  B_FREQ     (int)       5
#define  A_UPDATER  (int)       PIC_FREQ/A_FREQ/LEVELS
#define  B_UPDATER  (int)       PIC_FREQ/B_FREQ/LEVELS

int main()
{
    int             Acount = 0, i = 0;
    unsigned char   Alevel = 0, Blevel = 0;
    unsigned char   sine[A_UPDATER];
    for (;i<A_UPDATER;i++)
    {
        sine[i] = ((LEVELS-1)/2*sin(((double)(2*PI*Acount))/((double)LEVELS)*2))+(LEVELS/2);
        Acount++;
    }
    Acount = 0;
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    WDTCONbits.ON = 0;
    initExpander(GP7);          // Make GP7 (button) input, rest outputs
    initSPI1();
    __builtin_enable_interrupts();
    
    while(1)
    {
        _CP0_SET_COUNT(0);
        setVoltage(A,Alevel);
        setVoltage(B,Blevel);
        Alevel = sine[Acount];
        Acount++;
        Blevel++;
        //setExpander(GP0,(char)((getExpander()&GP7)==GP7));  //Set LED on/off
        while(_CP0_GET_COUNT()<(B_UPDATER/2)){;}
    }   
}