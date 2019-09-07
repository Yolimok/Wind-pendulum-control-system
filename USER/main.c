#include "stm32f10x.h"
#include "oled.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "other.h"
#include "motor.h"
#include "pid.h"
#include "timer.h"
#include "key.h"
#include "arithmetic.h"
#include <stdio.h>
#include <math.h>
volatile float last_pitch=0,last_roll=0,last_length_x=0,last_length_y=0;
//����������ʾ���ݹ���Ҫ20ms���ҵ�ʱ��
/*		pitch<0	1	|y	pitch>0
				roll<0	|		roll<0
			0~90��		|	90~180��				
		2	__��������	|____��������4	x
								|
				90~180��|		0~90��
�ڶ�����pitch<0	|		pitch>0��һ����
			roll>0		|3	roll>0	*/
			//pitch: x��Ƕȣ�roll��y��Ƕ�
int main(void)
{	 
	volatile int key=0,mode=0;
	float set_value_key[3]={0,0,0};
	volatile float set_length=0,set_angle=0,set_radius=0,set_value=0;
	Key_Config();  				//������ʼ��
	uart_init(115200);//���ڳ�ʼ��,������Ϊ115200
	delay_init();	//��ʱ��ʼ�� 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	motor_init();	//���ı���ʼ��
	TIM2_PWM_Init(9999,71);//Ƶ��f=72000000/10000/72=100
	TIM3_Int_Init(1999,719);//��ʱ���жϣ�����Ϊ20ms
	motor_a(1,0);motor_c(1,0);
	motor_b(1,0);motor_d(1,0);
	initial_lcd();	   //OLED��ʼ��

//	delay_ms(500);
	MPU_Init();					//��ʼ��MPU6050
	while(mpu_dmp_init())
 	{
		delay_ms(200);
		display_GB2312_string(0,72,"error");
	}  
	clear_screen();
	display_GB2312_string(0,1,"������");
	display_GB2312_string(0,72,"OK");
	while(1)
	{
		key=KeyScan();
		if(key>10)	{mode=key-10;key_count--;}
		switch (mode)
			{ case 1: {display_GB2312_string(2,1,"ģʽһ:ֱ��");break;}
				case 2:{display_GB2312_string(2,1,"ģʽ��:ֱ��");display_GB2312_string(4,1,"���ó���:");
								set_length=set_value/10;oled_display_set_length(4,84,set_length);break;}
				case 3:{display_GB2312_string(2,1,"ģʽ��:б��");display_GB2312_string(4,1,"���ýǶ�:");
								set_angle=set_value;		oled_display_set_angle(4,84,set_angle);break;}
				case 4: {display_GB2312_string(2,1,"ģʽ��:�ƶ�");break;}
				case 5:{display_GB2312_string(2,1,"ģʽ��:��Բ");display_GB2312_string(4,1,"���ð뾶:");
								set_radius=set_value/10;oled_display_set_radius(4,84,set_radius);break;}}
		if((key>=0)&&(key<10))
		{set_value_key[key_count-1]=key;set_value=set_value_key[0]*100+set_value_key[1]*10+set_value_key[2];}
		if(key==10) break;
	}
	display_GB2312_string(6,1,"�������");
//	motor_init();					//���ı���ʼ��
//	motor_a(1,0);motor_c(1,0);
//	motor_b(1,0);motor_d(1,0);
	while(1)
	{
		printf("%d  ",mode);
		while(mode==1){first();}
		while(mode==2){second(set_length);}
		while(mode==3){third(set_angle);}
		while(mode==4){fourth();}
		while(mode==5){fifth(set_radius);}
	}
}

//��ʱ��3�жϷ������
void TIM3_IRQHandler(void) //TIM3 �ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���TIM3�����ж��Ƿ���
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //���TIM3�����жϱ�־
		pid_flag=0;
		current_stright_speed_x=(length_x-last_length_x)/0.02;
		current_stright_speed_y=(length_y-last_length_y)/0.02;//�����ٶȣ���λΪcm/s
		last_length_x=length_x;
		last_length_y=length_y;
		printf("�жϿ�");
		current_angle_speed_x=(pitch-last_pitch)/0.02;
		current_angle_speed_y=(roll-last_roll)/0.02;//�����ٶȣ���λΪ��/s
		last_pitch=pitch;
		last_roll=roll;
	}
}





