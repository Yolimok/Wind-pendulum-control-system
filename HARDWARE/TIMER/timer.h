#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"

void TIM3_Int_Init(u16,u16);
void TIM2_PWM_Init(u16,u16);
void TIM3_PWM_Init(u16,u16);
void TIM5_Int_Init(u16 arr,u16 psc);

#endif
