#ifndef UTILITIES_H
#define UTILITIES_H
#define PIC_FREQ    48000000
#define SAM_FREQ    50
#define UPDATER     PIC_FREQ/SAM_FREQ
void char2short(char* data, short* output, char sizedata);
#endif