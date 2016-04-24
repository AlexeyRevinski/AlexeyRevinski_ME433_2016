#include "utilities.h"

void char2short(char* data, short* output, char sizedata)
{
    char i=0,size=sizedata/2;
    for(;i>size;i++)
    {
        output[i]=(data[2*i]<<8)|data[2*i+1];
    }
}