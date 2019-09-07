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
//主函数中显示数据共需要20ms左右的时间
/*		pitch<0	1	|y	pitch>0
				roll<0	|		roll<0
			0~90度		|	90~180度				
		2	__第三象限	|____第四象限4	x
								|
				90~180度|		0~90度
第二象限pitch<0	|		pitch>0第一象限
			roll>0		|3	roll>0	*/
			//pitch: x轴角度，roll：y轴角度
int main(void)
{	 
	volatile int key=0,mode=0;
	float set_value_key[3]={0,0,0};
	volatile float set_length=0,set_angle=0,set_radius=0,set_value=0;
	Key_Config();  				//按键初始化
	uart_init(115200);//串口初始化,波特率为115200
	delay_init();	//延时初始化 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	motor_init();	//空心杯初始化
	TIM2_PWM_Init(9999,71);//频率f=72000000/10000/72=100
	TIM3_Int_Init(1999,719);//定时器中断，周期为20ms
	motor_a(1,0);motor_c(1,0);
	motor_b(1,0);motor_d(1,0);
	initial_lcd();	   //OLED初始化

//	delay_ms(500);
	MPU_Init();					//初始化MPU6050
	while(mpu_dmp_init())
 	{
		delay_ms(200);
		display_GB2312_string(0,72,"error");
	}  
	clear_screen();
	display_GB2312_string(0,1,"风力摆");
	display_GB2312_string(0,72,"OK");
	while(1)
	{
		key=KeyScan();
		if(key>10)	{mode=key-10;key_count--;}
		switch (mode)
			{ case 1: {display_GB2312_string(2,1,"模式一:直线");break;}
				case 2:{display_GB2312_string(2,1,"模式二:直线");display_GB2312_string(4,1,"设置长度:");
								set_length=set_value/10;oled_display_set_length(4,84,set_length);break;}
				case 3:{display_GB2312_string(2,1,"模式三:斜线");display_GB2312_string(4,1,"设置角度:");
								set_angle=set_value;		oled_display_set_angle(4,84,set_angle);break;}
				case 4: {display_GB2312_string(2,1,"模式四:制动");break;}
				case 5:{display_GB2312_string(2,1,"模式五:画圆");display_GB2312_string(4,1,"设置半径:");
								set_radius=set_value/10;oled_display_set_radius(4,84,set_radius);break;}}
		if((key>=0)&&(key<10))
		{set_value_key[key_count-1]=key;set_value=set_value_key[0]*100+set_value_key[1]*10+set_value_key[2];}
		if(key==10) break;
	}
	display_GB2312_string(6,1,"设置完毕");
//	motor_init();					//空心杯初始化
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

//定时器3中断服务程序
void TIM3_IRQHandler(void) //TIM3 中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查TIM3更新中断是否发生
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update ); //清除TIM3更新中断标志
		pid_flag=0;
		current_stright_speed_x=(length_x-last_length_x)/0.02;
		current_stright_speed_y=(length_y-last_length_y)/0.02;//计算速度，单位为cm/s
		last_length_x=length_x;
		last_length_y=length_y;
		printf("中断开");
		current_angle_speed_x=(pitch-last_pitch)/0.02;
		current_angle_speed_y=(roll-last_roll)/0.02;//计算速度，单位为度/s
		last_pitch=pitch;
		last_roll=roll;
	}
}





