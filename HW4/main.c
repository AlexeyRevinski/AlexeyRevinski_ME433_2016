#include "PIC32_config.h"
#define  LEVELS     (int)       256
#define  PI         (double)    3.14159265
#define  I2C_FREQ   (int)       12000000
#define  A_FREQ     (int)       10
#define  B_FREQ     (int)       5
#define  UPDATER    (int)       I2C_FREQ/B_FREQ/LEVELS

int main()
{
    int             Acount = 0, Bcount = 0;
    unsigned char   Alevel = 0, Blevel = 0, half = 0;
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    initExpander(GP7);          // Make GP7 (button) input, rest outputs
    initSPI1();
    __builtin_enable_interrupts();
    
    while(1)
    {
        _CP0_SET_COUNT(0);
        half = !half;
        setVoltage(A,Alevel);
        setVoltage(B,Blevel);
        Alevel = ((LEVELS-1)/2*sin(((double)(2*PI*Acount))/((double)UPDATER)))+(LEVELS/2);
        Acount++;
        if (half){Blevel++;}
        //setExpander(GP0,(char)((getExpander()&GP7)==GP7));  //Set LED on/off
        while(_CP0_GET_COUNT()<UPDATER){;}
    }   
}