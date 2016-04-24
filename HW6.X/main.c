#include    "PIC32_config.h"
int main()
{
    char            whoami_check = 0;
    unsigned char   data[14];
    // PIC32 Setup
    __builtin_disable_interrupts();
    __builtin_mtc0(_CP0_CONFIG,_CP0_CONFIG_SELECT,0xa4210583);
    BMXCONbits.BMXWSDRM = 0x0;  // 0 data RAM access wait states
    INTCONbits.MVEC = 0x1;      // enable multi vector interrupts
    DDPCONbits.JTAGEN = 0;      // disable JTAG to get pins back
    TRISAbits.TRISA4 = 0;       // RA4 is output
    TRISBbits.TRISB4 = 1;       // RB4 is input
    LATAbits.LATA4 = 0;			// LED is off
    i2c_master_setup();
    tim2_setup();
    oc1_setup();
    oc2_setup();
    __builtin_enable_interrupts();
    
    whoami_check = i2c_master_read(IMU_ADDR,WHO_AM_I);
    if (whoami_check == WHOAMI_VAL)
    {
        ;//LATAbits.LATA4 = 1;
    }
    
    while(1)
    {
        _CP0_SET_COUNT(0);
        i2c_master_read_all(IMU_ADDR,OUT_TEMP_L,14,data);
        LATAbits.LATA4 = !LATAbits.LATA4;
        while(_CP0_GET_COUNT()<UPDATER){;}
    }        
}