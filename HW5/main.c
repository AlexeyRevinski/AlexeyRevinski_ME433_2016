#include    "PIC32_config.h"
#define     WHOAMI_ADDR (char)  0x0F     // 0b00001111
#define     WHOAMI_VAL  (char)  0x69     // 0b1101001
#define     IMU_ADDR    (char)  0x6B     // 0b1101011(R/W)
int main()
{
    char whoami_check = 0;
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    i2c_master_setup();
    __builtin_enable_interrupts();
    
    whoami_check = i2c_master_read(IMU_ADDR,WHOAMI_ADDR);
    if (whoami_check == WHOAMI_VAL)
    {
        LATAbits.LATA4 = 1;
    }
    
    while(1)
    {
        ;
    }   
}