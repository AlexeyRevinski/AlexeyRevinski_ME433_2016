#include    "PIC32_config.h"
#include    <stdio.h>
int main()
{
    char            whoami_check = 0;
    unsigned char   data[14] = {0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03};
    //unsigned char   data[14]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    short           output[7] = {0,0,0,0,0,0,0};
    int             oc1_new=0,oc2_new=0;
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
        char2short(data,output,14);
        oc1_new = (PER2+1)/2+(output[6]/20);
        oc2_new = (PER2+1)/2;
        if(oc1_new>(PER2+1)){oc1_new=(PER2+1);}
        if(oc2_new>(PER2+1)){oc2_new=(PER2+1);}
        OC1RS = oc1_new;
        OC2RS = oc2_new;
        LATAbits.LATA4 = !LATAbits.LATA4;
        while(_CP0_GET_COUNT()<UPDATER){;}
    }        
}