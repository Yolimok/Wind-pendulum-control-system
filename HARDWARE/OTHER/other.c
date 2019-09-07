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
#include <math.h>


//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{   	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
	USART_SendData(USART1,c);  
} 
//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}
//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz)
{
	u8 tbuf[12]; 
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;
	usart1_niming_report(0XA1,tbuf,12);//�Զ���֡,0XA1
}	
//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw)
{
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
	tbuf[0]=(aacx>>8)&0XFF;
	tbuf[1]=aacx&0XFF;
	tbuf[2]=(aacy>>8)&0XFF;
	tbuf[3]=aacy&0XFF;
	tbuf[4]=(aacz>>8)&0XFF;
	tbuf[5]=aacz&0XFF; 
	tbuf[6]=(gyrox>>8)&0XFF;
	tbuf[7]=gyrox&0XFF;
	tbuf[8]=(gyroy>>8)&0XFF;
	tbuf[9]=gyroy&0XFF;
	tbuf[10]=(gyroz>>8)&0XFF;
	tbuf[11]=gyroz&0XFF;	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAF,tbuf,28);//�ɿ���ʾ֡,0XAF
}  

void my_usart_report(short pitch,short roll,short yaw,short synthesis_angle,short pid_out_x,short pid_out_y)
{
	u8 tbuf[12]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//��0
	tbuf[0]=(pitch>>8)&0XFF;
	tbuf[1]=pitch&0XFF;
	tbuf[2]=(roll>>8)&0XFF;
	tbuf[3]=roll&0XFF;
	tbuf[4]=(yaw>>8)&0XFF;
	tbuf[5]=yaw&0XFF; 
	tbuf[6]=(synthesis_angle>>8)&0XFF;
	tbuf[7]=synthesis_angle&0XFF;
	tbuf[8]=(pid_out_x>>8)&0XFF;
	tbuf[9]=pid_out_x&0XFF;
	tbuf[10]=(pid_out_y>>8)&0XFF;
	tbuf[11]=pid_out_y&0XFF;	
	usart1_niming_report(0XAF,tbuf,12);//�ɿ���ʾ֡,0XAF
}  
void oled_display_angle(unsigned char y,unsigned char x,float angle)
{
	unsigned char display_string[]="      ";
	short temp=0;
	temp=angle*10;
	if(temp<0) {display_string[0]='-'; temp=-temp;}
	else display_string[0]=' ';
	display_string[1]=0x30+temp/1000;
	display_string[2]=0x30+temp/100%10;
	display_string[3]=0x30+temp/10%10;
	display_string[4]='.';
	display_string[5]=0x30+temp%10;
	display_GB2312_string(y,x,display_string);
}
void oled_display_set_angle(unsigned char y,unsigned char x,float angle)
{
	unsigned char display_string[]="   ";
	short temp=0;
	temp=angle;
	if(key_count>=1)	display_string[0]=0x30+temp/100;
	if(key_count>=2)	display_string[1]=0x30+temp/10%10;
	if(key_count>=3)	display_string[2]=0x30+temp%10;
	printf("%d/n",temp);
	display_GB2312_string(y,x,display_string);
}
void oled_display_set_length(unsigned char y,unsigned char x,float length)
{
	unsigned char display_string[]="     ";
	short temp=0;
	temp=length;
	if(key_count>=1)	display_string[0]=0x30+temp/10;
	if(key_count>=2)	display_string[1]=0x30+temp%10;
	display_GB2312_string(y,x,display_string);
	printf("%d/n",temp);
}
void oled_display_set_radius(unsigned char y,unsigned char x,float length)
{
	unsigned char display_string[]="     ";
	short temp=0;
	temp=length;
	if(key_count>=1)	display_string[0]=0x30+temp/10;
	if(key_count>=2)	display_string[1]=0x30+temp%10;
	display_GB2312_string(y,x,display_string);
}



//ɽ��������ֵ�ͨѶЭ��
//����ʾ������ʾ���ݲ���
void uart_putbuff(USART_TypeDef* USARTx,uint8_t *buff,uint32_t length)
{
	uint32_t i;
	for(i=0;i<length;i++)
	{
		USART_SendData(USARTx,*buff);
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		delay_us(90);
		buff++;
	}
}
void vcan_sendware(uint8_t *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    

    uart_putbuff(USART1,cmdf, sizeof(cmdf));

    uart_putbuff(USART1,wareaddr, waresize);//��������

    uart_putbuff(USART1,cmdr, sizeof(cmdr));    
}













