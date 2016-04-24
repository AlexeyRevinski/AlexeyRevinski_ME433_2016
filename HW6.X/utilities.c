#include "utilities.h"

void char2short(char* data, short* output, char sizedata)
{
    char i=0,size=sizedata/2;
    for(;i>size;i++)
    {
        output[i]=(data[2*i+1]<<8)|data[2*i];
    }
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
    OC1CONbits.OCM		= 0b110;		// PWM mode without fault pin; other OC1CON bits are defaults
	OC1CONbits.OCTSEL	= 0;			// use Timer 2
	OC1RS				= ((PER2+1)/2);	// duty cycle = OC1RS/(PR2+1) = 50%
	OC1R				= ((PER2+1)/2);	// initialize before turning OC1 on
	OC1CONbits.ON		= 1;			// turn on OC1
}

void oc2_setup(void)
{
    OC2CONbits.OCM		= 0b110;		// PWM mode without fault pin; other OC2CON bits are defaults
	OC2CONbits.OCTSEL	= 0;			// use Timer 2
	OC2RS				= ((PER2+1)/2);	// duty cycle = OC2RS/(PR2+1) = 50%
	OC2R				= ((PER2+1)/2);	// initialize before turning OC2 on
	OC2CONbits.ON		= 1;			// turn on OC2
}
	