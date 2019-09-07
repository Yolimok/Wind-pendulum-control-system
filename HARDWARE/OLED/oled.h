//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : OLED.H
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : �ֿ�� OLED SPI�ӿ���ʾ����(STM32ϵ��)
//              ˵��: 
//              ------------------------����ΪOLED��ʾ���õ��Ľӿ----------------------------------------
//              GND    ��Դ��
//              VCC   ��5V��3.3v��Դ
//              CLK   PA5��CLK��
//              MOSI   PA7��DIN��
//              DC   PB0
//              CS1   PB1
//              FSO   PA4                
//              CS2   PB2
//
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/
#define _OLED_H_
#ifdef _OLED_H_



/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  0
#define OFF 1



//���κ꣬��������������һ��ʹ��
#define lcd_cs1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_1);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_1)

#define lcd_rs(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)


#define lcd_sid(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_7);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define lcd_sclk(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_5);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define Rom_CS(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_2);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_2)

#define Rom_OUT(a)	if (a)	\
					GPIO_SetBits(GPIOA,GPIO_Pin_4);\
					else		\
					GPIO_ResetBits(GPIOA,GPIO_Pin_4)

					



extern unsigned char const bmp1[];
extern unsigned char const jiong1[];
extern unsigned char const lei1[];


/*дָ�LCDģ��*/
void transfer_command_lcd(int data1);   
/*д���ݵ�LCDģ��*/
void transfer_data_lcd(int data1);
/*��ʱ*/
void delay(int n_ms);               
/*LCDģ���ʼ��*/
void initial_lcd(void);
void lcd_address(unsigned char page,unsigned char column);
/*ȫ������*/
void clear_screen(void);
/*��ʾ128x64����ͼ��*/
void display_128x64(const unsigned char *dp);
/*��ʾ132x64����ͼ��*/
//void display_132x64(unsigned char *dp);
/*��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*��ʾ8x16����ͼ��ASCII, ��8x16����������ַ�������ͼ��*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*��ʾ5*7����ͼ��ASCII, ��5x7����������ַ�������ͼ��*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****��ָ�����Ѷ�ֿ�IC***/
void send_command_to_ROM( unsigned char datu );
/****�Ӿ���Ѷ�ֿ�IC��ȡ���ֻ��ַ����ݣ�1���ֽڣ�***/
static unsigned char get_data_from_ROM(void);
/*����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ�����������DataLen���ֽڵ����ݵ� pBuff�ĵ�ַ*/
/*������ȡ*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);

#endif




