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
    LATAbits.LATA4 = 0;			// LED is off
    initExpander(GP7);          // Make GP7 (button) input, rest outputs
    initSPI1();
    __builtin_enable_interrupts();
    
    while(1)
    {
        setExpander(GP0,(char)((getExpander()&GP7)==GP7));  //Set LED on/off
        setVoltage(A,150);
        setVoltage(B,255);
    }   
}