#ifndef __OTHER_H
#define __OTHER_H
#include "stm32f10x.h"
#include "sys.h"
void usart1_send_char(u8 c);
void usart1_niming_report(u8 fun,u8*data,u8 len);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);
void oled_display_angle(unsigned char y,unsigned char x,float angle);
void oled_display_set_angle(unsigned char y,unsigned char x,float angle);
void oled_display_set_length(unsigned char y,unsigned char x,float length);
void oled_display_set_radius(unsigned char y,unsigned char x,float length);
void oled_display_mode(unsigned char y,unsigned char x,int mode);
void my_usart_report(short pitch,short roll,short yaw,short synthesis_angle,short pid_out_x,short pid_out_y);
void uart_putbuff(USART_TypeDef* USARTx,uint8_t *buff,uint32_t length);
void vcan_sendware(uint8_t *wareaddr, uint32_t waresize);
#endif
















