#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "motor.h"
/*
空心杯引脚连接方式：
motor_a:PA0,PC0;
motor_b:PA1,PC1;
motor_c:PA2,PC2;
motor_d:PA3,PC3;
*/
void motor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOC端口时钟
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				 //GPIOC.0~GPIOC.3 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
 GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);						 //GPIOC.0~GPIOC.3 输出低
}

//建议direction取1,向内转，否则会影响对面空心杯的转动
//direction:方向，0，正转/向外，1：反转/向内
//speed:速度，范围：0~10000
void motor_a(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR1=0;TIM_SetCompare1(TIM2,speed);}//向外
		else	{MOTOR1=1;TIM_SetCompare1(TIM2,10000-speed);}//向内
}
void motor_b(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR2=0;TIM_SetCompare2(TIM2,speed);}//向外
		else	{MOTOR2=1;TIM_SetCompare2(TIM2,10000-speed);}//向内
}
void motor_c(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR3=0;TIM_SetCompare3(TIM2,speed);}//向外
		else	{MOTOR3=1;TIM_SetCompare3(TIM2,10000-speed);}//向内
}
void motor_d(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR4=0;TIM_SetCompare4(TIM2,speed);}//向外
		else	{MOTOR4=1;TIM_SetCompare4(TIM2,10000-speed);}//向内
}
//对四个空心杯分两组
void motor_x(float speed)
{
		if(speed>=0) {motor_b(1,speed);motor_d(1,0);}
		else	{ motor_b(1,0);motor_d(1,-speed);}
}
void motor_y(float speed)
{
		if(speed>=0) {motor_a(1,speed);motor_c(1,0);}
		else	{ motor_a(1,0);motor_c(1,-speed);}
}








