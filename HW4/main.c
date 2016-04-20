#include "PIC32_config.h"
#define  WAIT_TIME 12000

int main()
{
    char read_byte = 0;
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 1;			// LED is on
    initSPI1();
    initExpander(GP7);          // GP7 is input (button); rest are outputs
    __builtin_enable_interrupts();
    
    while(1)
    {
        read_byte = i2c_master_read(GPIO);
        if (read_byte==GP7)
        {
            i2c_master_write(GPIO,GP0); // turn on GP0 - yellow LED
        }
    }   
}