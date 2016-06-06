#ifndef UTILITIES_H
#define UTILITIES_H
#include <xc.h>
#define PIC_FREQ    48000000
#define SAM_FREQ    50
#define PER2        2999
#define MAX         (PER2+1)
#define UPDATER     PIC_FREQ/SAM_FREQ
#define RSPD        OC2RS                //Right Motor Speed   (0 to (PER2+1))
#define LSPD        OC1RS                //Left  Motor Speed   (0 to (PER2+1))
#define RFOR        LATAbits.LATA0       //Right Motor Forward (true/false)
#define LFOR        LATBbits.LATB2       //Left  Motor Forward (true/false)
#define LED         LATAbits.LATA4       //LED on/off
#define MIDDLE      320
void char2short(char *data, short *output, int sizedata);
void tim2_setup(void);
void gio_setup(void);
void oc1_setup(void);
void oc2_setup(void);
#endif