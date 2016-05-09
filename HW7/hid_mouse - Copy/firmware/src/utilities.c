#include "utilities.h"

void char2short(unsigned char *data, short *output, int sizedata)
{
    int i=0,size=sizedata/2;
    for(;i<=size;i++)
    {
        //output[i]=(((short)data[2*i+1])<<8)|((short)data[2*i]);
        output[i]=(((unsigned short)data[2*i+1])<<8)|(data[2*i]);
    }
}

void clearline(char* line)
{
    int i=0;
    for(;i<length+1;i++)
    {
        line[i] = ' ';
    }
}
	