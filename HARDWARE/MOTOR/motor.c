#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "motor.h"
/*
���ı��������ӷ�ʽ��
motor_a:PA0,PC0;
motor_b:PA1,PC1;
motor_c:PA2,PC2;
motor_d:PA3,PC3;
*/
void motor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��GPIOC�˿�ʱ��
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				 //GPIOC.0~GPIOC.3 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
 GPIO_ResetBits(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);						 //GPIOC.0~GPIOC.3 �����
}

//����directionȡ1,����ת�������Ӱ�������ı���ת��
//direction:����0����ת/���⣬1����ת/����
//speed:�ٶȣ���Χ��0~10000
void motor_a(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR1=0;TIM_SetCompare1(TIM2,speed);}//����
		else	{MOTOR1=1;TIM_SetCompare1(TIM2,10000-speed);}//����
}
void motor_b(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR2=0;TIM_SetCompare2(TIM2,speed);}//����
		else	{MOTOR2=1;TIM_SetCompare2(TIM2,10000-speed);}//����
}
void motor_c(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR3=0;TIM_SetCompare3(TIM2,speed);}//����
		else	{MOTOR3=1;TIM_SetCompare3(TIM2,10000-speed);}//����
}
void motor_d(u16 direction,u16 speed)
{
		if(direction==0)	{MOTOR4=0;TIM_SetCompare4(TIM2,speed);}//����
		else	{MOTOR4=1;TIM_SetCompare4(TIM2,10000-speed);}//����
}
//���ĸ����ı�������
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








