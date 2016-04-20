#ifndef PIN_EXPANDER_H
#define PIN_EXPANDER_H
#include "i2c_master.h"
void initExpander(void);
void setExpander(char pin, char level);
char getExpander(void);
#endif