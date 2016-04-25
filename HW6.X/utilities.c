#include "utilities.h"

void char2short(char *data, short *output, int sizedata)
{
    int i=0,size=sizedata/2;
    output[0] = (((short)data[1])<<8)|((short)data[0]);
    output[1] = (((short)data[3])<<8)|((short)data[2]);
    output[2] = (((short)data[5])<<8)|((short)data[4]);
    output[3] = (((short)data[7])<<8)|((short)data[6]);
    output[4] = (((short)data[9])<<8)|((short)data[8]);
    output[5] = (((short)data[11])<<8)|((short)data[10]);
    output[6] = (((short)data[13])<<8)|((short)data[12]);
    /*for(;i>size;i++)
    {
        output[i]=(((short)data[2*i+1])<<8)|((short)data[2*i]);
    }*/
}

void tim2_setup(void)
{
    T2CONbits.TCKPS 	= 4;			// timer2 pre-scaler N=16 (1:16)
	PR2 				= PER2;			// period2 = (4999+1) * 16 * 12.5ns = 0.001s, 1 kHz
	TMR2 				= 0;			// set timer to 0;
    T2CONbits.ON		= 1;			// turn on Timer2
}

void oc1_setup(void)
{
    RPA0Rbits.RPA0R     = 0x05;         // RA0 - OC1
    OC1CONbits.OCM		= 0x06;         // PWM mode without fault pin; other OC1CON bits are defaults
	OC1CONbits.OCTSEL	= 0;			// use Timer 2
	OC1RS				= ((PER2+1)/2);	// duty cycle = OC1RS/(PR2+1) = 50%
	OC1R				= ((PER2+1)/2);	// initialize before turning OC1 on
	OC1CONbits.ON		= 1;			// turn on OC1
}

void oc2_setup(void)
{
    RPA1Rbits.RPA1R     = 0x05;         // RA1 - OC2
    OC2CONbits.OCM		= 0x06;         // PWM mode without fault pin; other OC2CON bits are defaults
	OC2CONbits.OCTSEL	= 0;			// use Timer 2
	OC2RS				= ((PER2+1)/2);	// duty cycle = OC2RS/(PR2+1) = 50%
	OC2R				= ((PER2+1)/2);	// initialize before turning OC2 on
	OC2CONbits.ON		= 1;			// turn on OC2
}
	