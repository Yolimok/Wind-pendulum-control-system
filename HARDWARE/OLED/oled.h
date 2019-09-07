//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ÖĞ¾°Ô°µç×Ó
//µêÆÌµØÖ·£ºhttp://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  ÎÄ ¼ş Ãû   : OLED.H
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : HuangKai
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üĞŞ¸Ä   : 
//  ¹¦ÄÜÃèÊö   : ×Ö¿â°æ OLED SPI½Ó¿ÚÑİÊ¾Àı³Ì(STM32ÏµÁĞ)
//              ËµÃ÷: 
//              ------------------------ÒÔÏÂÎªOLEDÏÔÊ¾ËùÓÃµ½µÄ½Ó¿----------------------------------------
//              GND    µçÔ´µØ
//              VCC   ½Ó5V»ò3.3vµçÔ´
//              CLK   PA5£¨CLK£©
//              MOSI   PA7£¨DIN£©
//              DC   PB0
//              CS1   PB1
//              FSO   PA4                
//              CS2   PB2
//
// ĞŞ¸ÄÀúÊ·   :
// ÈÕ    ÆÚ   : 
// ×÷    Õß   : HuangKai
// ĞŞ¸ÄÄÚÈİ   : ´´½¨ÎÄ¼ş
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÖĞ¾°Ô°µç×Ó2014/3/16
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



//´ø²Îºê£¬¿ÉÒÔÏñÄÚÁªº¯ÊıÒ»ÑùÊ¹ÓÃ
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


/*Ğ´Ö¸Áîµ½LCDÄ£¿é*/
void transfer_command_lcd(int data1);   
/*Ğ´Êı¾İµ½LCDÄ£¿é*/
void transfer_data_lcd(int data1);
/*ÑÓÊ±*/
void delay(int n_ms);               
/*LCDÄ£¿é³õÊ¼»¯*/
void initial_lcd(void);
void lcd_address(unsigned char page,unsigned char column);
/*È«ÆÁÇåÆÁ*/
void clear_screen(void);
/*ÏÔÊ¾128x64µãÕóÍ¼Ïñ*/
void display_128x64(const unsigned char *dp);
/*ÏÔÊ¾132x64µãÕóÍ¼Ïñ*/
//void display_132x64(unsigned char *dp);
/*ÏÔÊ¾16x16µãÕóÍ¼Ïñ¡¢ºº×Ö¡¢ÉúÆ§×Ö»ò16x16µãÕóµÄÆäËûÍ¼±ê*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp);
/*ÏÔÊ¾8x16µãÕóÍ¼Ïñ¡¢ASCII, »ò8x16µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp);
/*ÏÔÊ¾5*7µãÕóÍ¼Ïñ¡¢ASCII, »ò5x7µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp);
/****ËÍÖ¸Áîµ½¾§ÁªÑ¶×Ö¿âIC***/
void send_command_to_ROM( unsigned char datu );
/****´Ó¾§ÁªÑ¶×Ö¿âICÖĞÈ¡ºº×Ö»ò×Ö·ûÊı¾İ£¨1¸ö×Ö½Ú£©***/
static unsigned char get_data_from_ROM(void);
/*´ÓÏà¹ØµØÖ·£¨addrHigh£ºµØÖ·¸ß×Ö½Ú,addrMid£ºµØÖ·ÖĞ×Ö½Ú,addrLow£ºµØÖ·µÍ×Ö½Ú£©ÖĞÁ¬Ğø¶Á³öDataLen¸ö×Ö½ÚµÄÊı¾İµ½ pBuffµÄµØÖ·*/
/*Á¬Ğø¶ÁÈ¡*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen );
/******************************************************************/
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text);
void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text);

#endif




