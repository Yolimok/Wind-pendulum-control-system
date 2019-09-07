#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_
#include "stm32f10x.h"
#include "pid.h"
extern volatile float length_x,length_y,current_stright_speed_x,current_stright_speed_y,
	current_angle_speed_x,current_angle_speed_y;
extern float pitch,roll,yaw;//Å·À­½Ç
extern volatile u16 pid_flag;
void first(void);
void second(float set_length);
void third(float set_angle);
void fourth(void);
void fifth(float set_radius);

#endif









