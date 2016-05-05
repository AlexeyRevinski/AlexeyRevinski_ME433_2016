#ifndef UTILITIES_H
#define UTILITIES_H
#include <xc.h>
#define PIC_FREQ    48000000
#define SAM_FREQ    50
#define PER2        2999
#define UPDATER     PIC_FREQ/SAM_FREQ
#define length      21
void char2short(char *data, short *output, int sizedata);
void clearline(char* line);
#endif