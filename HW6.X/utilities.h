#ifndef UTILITIES_H
#define UTILITIES_H
#include <xc.h>
#define PIC_FREQ    48000000
#define SAM_FREQ    50
#define PER2        4999
#define UPDATER     PIC_FREQ/SAM_FREQ
void char2short(char* data, short* output, char sizedata);
void tim2_setup(void);
#endif