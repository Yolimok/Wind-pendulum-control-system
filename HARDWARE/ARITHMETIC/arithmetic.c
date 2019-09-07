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
#include "arithmetic.h"
#include <stdio.h>
#include <math.h>
#define POLE_LENGTH 90.5f		//֧���ܸ߶�
#define SWAY_LENGTH 71.5f		//�ڸ˳���
#define PI 3.14159265f		
float pitch,roll,yaw;//ŷ����
u16 volatile pid_flag=0;
volatile float length_x=0,length_y=0,current_stright_speed_x=0,current_stright_speed_y=0,
	current_angle_speed_x=0,current_angle_speed_y=0;
void first(void)
{motor_c(1,9000);
	delay_ms(200);
	while(1)
	{	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ���ǵ�ֵ
	{ 
		if(fabs(roll)<5)
		{
			if(current_angle_speed_y>=0)	motor_a(1,4000);
			if(current_angle_speed_y<0)	motor_c(1,4000);
		}else{motor_y(0);}
	}}
}
void second(float set_length)
{
	float send_data[8];
	volatile float length=0,sway_angle=0,current_sway_angle=0,standard_speed=0,pid_speed_y=0;
	static PID_LocTypeDef PID_straight;
			PID_straight.kp=482;	
			PID_straight.ki=18.7;
			PID_straight.kd=2;
	set_length=set_length/2;//����ֱ�߳��ȵ�һ��
	sway_angle=atan(set_length/POLE_LENGTH);//�趨�ĸ˵İڽǣ��ýǶ�Ϊ������
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ���ǵ�ֵ
		{ 
			length=sqrt((POLE_LENGTH*tan(pitch*PI/180))*(POLE_LENGTH*tan(pitch*PI/180))
							+(POLE_LENGTH*tan(roll*PI/180))*(POLE_LENGTH*tan(roll*PI/180)));//���㼤����Բ�ľ���
			current_sway_angle=atan(length/POLE_LENGTH);//���㵱ǰ�ڽ�,�ýǶ�Ϊ������
			if(roll<0) length=-length;
			if(fabs(length)<set_length)
			standard_speed=(sqrt(2*980*SWAY_LENGTH*(cos(current_sway_angle)-cos(atan(set_length/POLE_LENGTH))))
			/SWAY_LENGTH)*180/PI;//������ٶȣ���λΪ��/s
			else standard_speed=0;
			if(current_angle_speed_y<0) standard_speed=-standard_speed;
			if(pid_flag==0)
			{
				pid_flag=1;
				pid_speed_y=PID_location(standard_speed,current_angle_speed_y,&PID_straight);
				motor_y(pid_speed_y);
			}//20ms����һ��PID��ִ��
			send_data[0]=pitch*10;
			send_data[1]=roll*10;
			send_data[2]=length;
			send_data[3]=0;
			send_data[4]=current_angle_speed_y;
			send_data[5]=0;
			send_data[6]=standard_speed;
			send_data[7]=0;
			vcan_sendware((uint8_t *)send_data,sizeof(send_data));
		}
	} 	
}
void third(float set_angle)
{
	volatile float length=0,angle=0,set_length=0,standard_speed=0,standard_speed_x=0,standard_speed_y=0,
		pid_speed_x=0,pid_speed_y=0,sway_angle=0,current_sway_angle=0,set_length_x=0,set_length_y=0;
	float send_data[8];
	static PID_LocTypeDef PID_straight_x; 
	static PID_LocTypeDef PID_straight_y;
			PID_straight_x.kp=482;	
			PID_straight_x.ki=18.7;
			PID_straight_x.kd=2;
			PID_straight_y.kp=482;
			PID_straight_y.ki=18.7;
			PID_straight_y.kd=2;//PID��������
	set_length=30;//����ֱ�߳��ȵ�һ��
	sway_angle=atan(set_length/POLE_LENGTH);//�趨�ĸ˵İڽǣ��ýǶ�Ϊ������
	while(mpu_dmp_get_data(&pitch,&roll,&yaw)!=0);
	motor_x(9000*cos(set_angle*PI/180));motor_y(9000*sin(set_angle*PI/180));
	delay_ms(20);
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ���ǵ�ֵ
		{ 
			length=sqrt((POLE_LENGTH*tan(pitch*PI/180))*(POLE_LENGTH*tan(pitch*PI/180))
							+(POLE_LENGTH*tan(roll*PI/180))*(POLE_LENGTH*tan(roll*PI/180)));//���㼤����Բ�ľ���
			angle=(atan((tan(roll*PI/180)/tan(pitch*PI/180))))*180/PI;
			if(angle<0)	angle=angle+180;		//���㼤���ļ�����Ƕ�
			current_sway_angle=atan(length/POLE_LENGTH);//���㵱ǰ�ڽ�,�ýǶ�Ϊ������
			length_x=fabs(length*cos(angle*PI/180));
			length_y=fabs(length*sin(angle*PI/180));
			if(pitch<0)	length_x=-length_x;
			if(roll<0)	length_y=-length_y;//���㵱ǰλ�ó�����x,y���ϵķ���
			if(fabs(length)<set_length)
			standard_speed=(sqrt(2*980*SWAY_LENGTH*(cos(current_sway_angle)-cos(atan(set_length/POLE_LENGTH))))
			/SWAY_LENGTH)*180/PI;//������ٶȣ���λΪ��/s
			else standard_speed=0;
			if(set_angle<90)
			{
				standard_speed_x=fabs(standard_speed*cos(set_angle*PI/180));
				standard_speed_y=fabs(standard_speed*sin(set_angle*PI/180));
				if((current_angle_speed_x<=0)&&(current_angle_speed_y>=0))
					{standard_speed_x=standard_speed_x;standard_speed_y=fabs(standard_speed_y);}
				if((current_angle_speed_x>=0)&&(current_angle_speed_y<=0))
					{standard_speed_x=-standard_speed_x;standard_speed_y=-fabs(standard_speed_y);}
			}else
			{
				standard_speed_x=fabs(standard_speed*cos(set_angle*PI/180));
				standard_speed_y=fabs(standard_speed*sin(set_angle*PI/180));
				if((current_angle_speed_x<=0)&&(current_angle_speed_y>=0))
					{standard_speed_x=-standard_speed_x;standard_speed_y=standard_speed_y;}
				if((current_angle_speed_x>=0)&&(current_angle_speed_y<=0))
					{standard_speed_x=standard_speed_x;standard_speed_y=-standard_speed_y;}
			}
			if(pid_flag==0)
			{
				pid_flag=1;
				pid_speed_x=PID_location(standard_speed_x,current_angle_speed_x,&PID_straight_x);
				pid_speed_y=PID_location(standard_speed_y,current_angle_speed_y,&PID_straight_y);
				if(current_angle_speed_x>=0) {if(pid_speed_x<=0) pid_speed_x=0;}
				if(current_angle_speed_y>=0) {if(pid_speed_y<=0) pid_speed_y=0;}
				if(current_angle_speed_x<0) {if(pid_speed_x>0) pid_speed_x=0;}
				if(current_angle_speed_y<0) {if(pid_speed_y>0) pid_speed_y=0;}
				motor_x(pid_speed_x);motor_y(pid_speed_y);
			}//20ms����һ��PID��ִ��
			send_data[0]=pitch*10;
			send_data[1]=roll*10;
			send_data[2]=length;
			send_data[3]=angle;
			send_data[4]=current_angle_speed_x;
			send_data[5]=current_angle_speed_y;
			send_data[6]=standard_speed_x;
			send_data[7]=standard_speed_y;
			vcan_sendware((uint8_t *)send_data,sizeof(send_data));
		}
	} 	
}
void fourth(void)
{
		float send_data[8];
		volatile float length=0,set_length=0,standard_speed_x=0,standard_speed_y=0,
		pid_speed_x=0,pid_speed_y=0,sway_angle=0,current_sway_angle=0;
		static PID_LocTypeDef PID_straight_x; 
		static PID_LocTypeDef PID_straight_y;
			PID_straight_x.kp=482;	
			PID_straight_x.ki=18.7;
			PID_straight_x.kd=2;
			PID_straight_y.kp=482;
			PID_straight_y.ki=18.7;
			PID_straight_y.kd=2;//PID��������
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ���ǵ�ֵ
		{ 
//			length=sqrt((POLE_LENGTH*tan(pitch*PI/180))*(POLE_LENGTH*tan(pitch*PI/180))
//							+(POLE_LENGTH*tan(roll*PI/180))*(POLE_LENGTH*tan(roll*PI/180)));//���㼤����Բ�ľ���
//			current_sway_angle=atan(length/POLE_LENGTH);//���㵱ǰ�ڽ�,�ýǶ�Ϊ������
			if(pid_flag==0)
			{
				pid_flag=1;
				pid_speed_x=PID_location(standard_speed_x,current_angle_speed_x,&PID_straight_x);
				pid_speed_y=PID_location(standard_speed_y,current_angle_speed_y,&PID_straight_y);
				motor_x(pid_speed_x);
				motor_y(pid_speed_y);
			}//20ms����һ��PID��ִ��
			send_data[0]=pitch*10;
			send_data[1]=roll*10;
			send_data[2]=length;
			send_data[3]=0;
			send_data[4]=current_angle_speed_x;
			send_data[5]=current_angle_speed_y;
			send_data[6]=standard_speed_x;
			send_data[7]=standard_speed_y;
			vcan_sendware((uint8_t *)send_data,sizeof(send_data));
		}
	} 	
}
void fifth(float set_radius)
{
	volatile float length=0,angle=0,radius_angle=0,standard_speed=0,standard_speed_x=0,standard_speed_y=0,
		pid_speed_x=0,pid_speed_y=0;
	
		float send_data[8];
	static PID_LocTypeDef PID_circle_x; 
	static PID_LocTypeDef PID_circle_y;
			PID_circle_x.kp=420;	
			PID_circle_x.ki=1.6;
			PID_circle_x.kd=8;
			PID_circle_y.kp=420;
			PID_circle_y.ki=1.6;
			PID_circle_y.kd=8;//PID��������	
	radius_angle=atan(set_radius/POLE_LENGTH);//�ýǶ�Ϊ������
	standard_speed=sqrt(980*set_radius*SWAY_LENGTH*sin(radius_angle)/POLE_LENGTH);
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)//��ȡŷ���ǵ�ֵ
		{ 
			length=sqrt((POLE_LENGTH*tan(pitch*PI/180))*(POLE_LENGTH*tan(pitch*PI/180))
							+(POLE_LENGTH*tan(roll*PI/180))*(POLE_LENGTH*tan(roll*PI/180)));//���㼤����Բ�ľ���
			length=length*SWAY_LENGTH/sqrt(POLE_LENGTH*POLE_LENGTH+length*length);//���㵱ǰ��������Բ�ľ���
			angle=(atan((tan(roll*PI/180)/tan(pitch*PI/180))))*180/PI;
			if(angle<0)	angle=angle+180;		//���㼤���ļ�����Ƕ�
			length_x=fabs(length*cos(angle*PI/180));
			length_y=fabs(length*sin(angle*PI/180));
			if(pitch<0)	length_x=-length_x;
			if(roll<0)	length_y=-length_y;//���㵱ǰλ�ó�����x,y���ϵķ���
			
			standard_speed_x=fabs(standard_speed*sin(angle*PI/180));
			standard_speed_y=fabs(standard_speed*cos(angle*PI/180));
			if((pitch>0)&&(roll>0)) {standard_speed_x=-standard_speed_x;}
			else {if((pitch<0)&&(roll>0))	{standard_speed_x=-standard_speed_x;standard_speed_y=-standard_speed_y;}
						else	{if((pitch<0)&&(roll<0)) {standard_speed_y=-standard_speed_y;}}}
			if(pid_flag==0)
			{
				pid_flag=1;
				pid_speed_x=PID_location(standard_speed_x,current_stright_speed_x,&PID_circle_x);
				pid_speed_y=PID_location(standard_speed_y,current_stright_speed_y,&PID_circle_y);
				motor_x(pid_speed_x);
				motor_y(pid_speed_y);
			}//20ms����һ��PID��ִ��
			send_data[0]=pitch*10;
			send_data[1]=roll*10;
			send_data[2]=length;
			send_data[3]=angle;
			send_data[4]=current_stright_speed_x;
			send_data[5]=current_stright_speed_y;
			send_data[6]=standard_speed_x;
			send_data[7]=standard_speed_y;
			vcan_sendware((uint8_t *)send_data,sizeof(send_data));
		}
	}
}











