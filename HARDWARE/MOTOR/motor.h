#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#define MOTOR1 PCout(0)
#define MOTOR2 PCout(1)
#define MOTOR3 PCout(2)
#define MOTOR4 PCout(3)

void motor_init(void);
void motor_a(u16 direction,u16 speed);
void motor_b(u16 direction,u16 speed);
void motor_c(u16 direction,u16 speed);
void motor_d(u16 direction,u16 speed);
void motor_x(float speed);
void motor_y(float speed);

#endif


