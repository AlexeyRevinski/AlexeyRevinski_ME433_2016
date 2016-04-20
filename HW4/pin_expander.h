#ifndef PIN_EXPANDER_H
#define PIN_EXPANDER_H
#include "i2c_master.h"
#include <xc.h>

// MCP23008 ADDRESSES AND VALUES
#define IODIR   (char) 0x00
#define GPIO    (char) 0x09
#define G0      (char) 1<<0
#define G1      (char) 1<<1
#define G2      (char) 1<<2
#define G3      (char) 1<<3
#define G4      (char) 1<<4
#define G5      (char) 1<<5
#define G6      (char) 1<<6
#define G7      (char) 1<<7

void initExpander(char IO_dir);
void setExpander(char pin, char level);
char getExpander(char pin);
#endif