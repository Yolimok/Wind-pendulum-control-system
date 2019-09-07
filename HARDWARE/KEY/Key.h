#ifndef __KEY_H
#define __KEY_H

#include <stm32f10x.h>
#include "usart.h"


#define uint unsigned int 
#define uchar unsigned char

extern int key_count;


void Key_Config(void);
int KeyScan(void);
void GetKeyVal(void);

#endif

