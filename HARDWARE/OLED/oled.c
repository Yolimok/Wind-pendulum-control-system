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
#include "oled.h"
#include "stm32f10x.h"


void OLED_GPIO_Config(void);
void GBZK_GPIO_Config(void);







void GBZK_GPIO_Config(void)
{		
	/*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*¿ªÆôGPIOBµÄÍâÉèÊ±ÖÓ*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

	/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOBÒı½Å*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 ;	

	/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*µ÷ÓÃ¿âº¯Êı£¬³õÊ¼»¯GPIOB*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	/* ¹Ø±ÕËùÓĞledµÆ	*/
	GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 );	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_2 );
	
		/*¿ªÆôGPIOAµÄÍâÉèÊ±ÖÓ*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); 

	/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOAÒı½Å*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 ;	

	/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*µ÷ÓÃ¿âº¯Êı£¬³õÊ¼»¯GPIOA*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  

	/* ¹Ø±ÕËùÓĞledµÆ	*/
	GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 );	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4 );
	
}

void GBZK_ROMOUTSET(void)
{		
	/*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOCÒı½Å*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;	

	/*ÉèÖÃÒı½ÅËÙÂÊÎª50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;   


	/*µ÷ÓÃ¿âº¯Êı£¬³õÊ¼»¯GPIOC*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  	 

}

void GBZK_ROMOUTRESET(void)
{		
	/*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Ñ¡ÔñÒª¿ØÖÆµÄGPIOCÒı½Å*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;	

	/*ÉèÖÃÒı½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	/*µ÷ÓÃ¿âº¯Êı£¬³õÊ¼»¯GPIOC*/
  	GPIO_Init(GPIOA, &GPIO_InitStructure);		  	 
}


/*Ğ´Ö¸Áîµ½LCDÄ£¿é*/
void transfer_command_lcd(int data1)   
{
	char i;
	lcd_rs(0);;;
	lcd_cs1(0);
	for(i=0;i<8;i++)
   {lcd_sclk(0);;;
		
		if(data1&0x80) {lcd_sid(1);;;}
		else {lcd_sid(0);;;}
		lcd_sclk(1);
		__nop();;;
	//	lcd_sclk(0);;;
	 	data1<<=1;
   }
	 	lcd_rs(1);;;
	 lcd_cs1(1);
}

/*Ğ´Êı¾İµ½LCDÄ£¿é*/
void transfer_data_lcd(int data1)
{
	char i;
	lcd_rs(1);;;
	lcd_cs1(0);
	for(i=0;i<8;i++)
   {
		lcd_sclk(0);;;
		if(data1&0x80) {lcd_sid(1);;;}
		else {lcd_sid(0);;;}
		lcd_sclk(1);;;
		__nop();;;
		//lcd_sclk(0);;;
	 	data1<<=1;
   }lcd_rs(1);;;
	 lcd_cs1(1);
}

/*ÑÓÊ±*/
void delay(int n_ms)               
{
 int j,k;
 for(j=0;j<n_ms;j++)
 for(k=0;k<5500;k++);
}


/*LCDÄ£¿é³õÊ¼»¯*/
void initial_lcd()
{delay(400);
	//OLED_GPIO_Config();
	GBZK_GPIO_Config();
	lcd_cs1(0);
	Rom_CS(1);
       
	transfer_command_lcd(0xAE);   //display off
	transfer_command_lcd(0x20);	//Set Memory Addressing Mode	
	transfer_command_lcd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	transfer_command_lcd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	transfer_command_lcd(0xc8);	//Set COM Output Scan Direction
	transfer_command_lcd(0x00);//---set low column address
	transfer_command_lcd(0x10);//---set high column address
	transfer_command_lcd(0x40);//--set start line address
	transfer_command_lcd(0x81);//--set contrast control register
	transfer_command_lcd(0xFF);
	transfer_command_lcd(0xa1);//--set segment re-map 0 to 127
	transfer_command_lcd(0xa6);//--set normal display
	transfer_command_lcd(0xa8);//--set multiplex ratio(1 to 64)
	transfer_command_lcd(0x3F);//
	transfer_command_lcd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	transfer_command_lcd(0xd3);//-set display offset
	transfer_command_lcd(0x00);//-not offset
	transfer_command_lcd(0xd5);//--set display clock divide ratio/oscillator frequency
	transfer_command_lcd(0xf0);//--set divide ratio
	transfer_command_lcd(0xd9);//--set pre-charge period
	transfer_command_lcd(0x22); //
	transfer_command_lcd(0xda);//--set com pins hardware configuration
	transfer_command_lcd(0x12);
	transfer_command_lcd(0xdb);//--set vcomh
	transfer_command_lcd(0x20);//0x20,0.77xVcc
	transfer_command_lcd(0x8d);//--set DC-DC enable
	transfer_command_lcd(0x14);//
	transfer_command_lcd(0xaf);//--turn on oled panel 
	lcd_cs1(1);
}

void lcd_address(unsigned char page,unsigned char column)
{

	transfer_command_lcd(0xb0 + column);   /*ÉèÖÃÒ³µØÖ·*/
	transfer_command_lcd(((page & 0xf0) >> 4) | 0x10);	/*ÉèÖÃÁĞµØÖ·µÄ¸ß4Î»*/
	transfer_command_lcd((page & 0x0f) | 0x00);	/*ÉèÖÃÁĞµØÖ·µÄµÍ4Î»*/	
}

/*È«ÆÁÇåÆÁ*/
void clear_screen()
{
	unsigned char i,j;
	lcd_cs1(0);
	Rom_CS(1);	
	for(i=0;i<8;i++)
	{
		transfer_command_lcd(0xb0+i);
		transfer_command_lcd(0x00);
		transfer_command_lcd(0x10);
		for(j=0;j<128;j++)
		{
		  	transfer_data_lcd(0x00);
		}
	}
 	lcd_cs1(1);
}

/*ÏÔÊ¾128x64µãÕóÍ¼Ïñ*/
void display_128x64(const unsigned char *dp)
{
	unsigned int i,j;
	lcd_cs1(0);
	for(j=0;j<8;j++)
	{
		lcd_address(0,j);
		for (i=0;i<128;i++)
		{	
			transfer_data_lcd(*dp);					/*Ğ´Êı¾İµ½LCD,Ã¿Ğ´ÍêÒ»¸ö8Î»µÄÊı¾İºóÁĞµØÖ·×Ô¶¯¼Ó1*/
			dp++;
		}
	}
	lcd_cs1(1);
}


/*ÏÔÊ¾16x16µãÕóÍ¼Ïñ¡¢ºº×Ö¡¢ÉúÆ§×Ö»ò16x16µãÕóµÄÆäËûÍ¼±ê*/
void display_graphic_16x16(unsigned int page,unsigned int column,const unsigned char *dp)
{
	unsigned int i,j;
 	lcd_cs1(0);
	Rom_CS(1); 	
	for(j=2;j>0;j--)
	{
		lcd_address(column,page);
		for (i=0;i<16;i++)
		{	
			transfer_data_lcd(*dp);					/*Ğ´Êı¾İµ½LCD,Ã¿Ğ´ÍêÒ»¸ö8Î»µÄÊı¾İºóÁĞµØÖ·×Ô¶¯¼Ó1*/
			dp++;
		}
		page++;
	}
	lcd_cs1(1);
}


/*ÏÔÊ¾8x16µãÕóÍ¼Ïñ¡¢ASCII, »ò8x16µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_8x16(unsigned int page,unsigned char column,unsigned char *dp)
{
	unsigned int i,j;
	lcd_cs1(0);	
	for(j=2;j>0;j--)
	{
		lcd_address(column,page);
		for (i=0;i<8;i++)
		{	
			transfer_data_lcd(*dp);					/*Ğ´Êı¾İµ½LCD,Ã¿Ğ´ÍêÒ»¸ö8Î»µÄÊı¾İºóÁĞµØÖ·×Ô¶¯¼Ó1*/
			dp++;
		}
		page++;
	}
	lcd_cs1(1);
}


/*ÏÔÊ¾5*7µãÕóÍ¼Ïñ¡¢ASCII, »ò5x7µãÕóµÄ×ÔÔì×Ö·û¡¢ÆäËûÍ¼±ê*/
void display_graphic_5x7(unsigned int page,unsigned char column,unsigned char *dp)
{
	unsigned int col_cnt;
	unsigned char page_address;
	unsigned char column_address_L,column_address_H;
	page_address = 0xb0+page-1;
	
	lcd_cs1(0);	
	
	column_address_L =(column&0x0f)-1;
	column_address_H =((column>>4)&0x0f)+0x10;
	
	transfer_command_lcd(page_address); 		/*Set Page Address*/
	transfer_command_lcd(column_address_H);	/*Set MSB of column Address*/
	transfer_command_lcd(column_address_L);	/*Set LSB of column Address*/
	
	for (col_cnt=0;col_cnt<6;col_cnt++)
	{	
		transfer_data_lcd(*dp);
		dp++;
	}
	lcd_cs1(1);
}

/****ËÍÖ¸Áîµ½¾§ÁªÑ¶×Ö¿âIC***/
void send_command_to_ROM( unsigned char datu )
{
	unsigned char i;
	for(i=0;i<8;i++ )
	{
		if(datu&0x80)
			{lcd_sid(1);;;__nop();}
		else
			{lcd_sid(0);;; __nop(); }
			datu = datu<<1;
			lcd_sclk(0);;;__nop();
			lcd_sclk(1);;;__nop();
	}
}

/****´Ó¾§ÁªÑ¶×Ö¿âICÖĞÈ¡ºº×Ö»ò×Ö·ûÊı¾İ£¨1¸ö×Ö½Ú£©***/
static unsigned char get_data_from_ROM( )
{
	
	unsigned char i;
	unsigned char ret_data=0;
	lcd_sclk(1);;;  __nop();
	GBZK_ROMOUTSET();
	for(i=0;i<8;i++)
	{
		Rom_OUT(1);;; __nop();
		lcd_sclk(0);;;__nop();
		ret_data=ret_data<<1;
		if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) )
		{ret_data=ret_data+1;;;__nop();}
		else
			ret_data=ret_data+0;;;__nop();	
		lcd_sclk(1);
	}
	GBZK_ROMOUTRESET();
	return(ret_data);
}



/*´ÓÏà¹ØµØÖ·£¨addrHigh£ºµØÖ·¸ß×Ö½Ú,addrMid£ºµØÖ·ÖĞ×Ö½Ú,addrLow£ºµØÖ·µÍ×Ö½Ú£©ÖĞÁ¬Ğø¶Á³öDataLen¸ö×Ö½ÚµÄÊı¾İµ½ pBuffµÄµØÖ·*/
/*Á¬Ğø¶ÁÈ¡*/
void get_n_bytes_data_from_ROM(unsigned char addrHigh,unsigned char addrMid,unsigned char addrLow,unsigned char *pBuff,unsigned char DataLen )
{
	unsigned char i;
	Rom_CS(0);
	lcd_cs1(1);	
	lcd_sclk(0);
	send_command_to_ROM(0x03);
	send_command_to_ROM(addrHigh);
	send_command_to_ROM(addrMid);
	send_command_to_ROM(addrLow);
	for(i = 0; i < DataLen; i++ )
	     *(pBuff+i) =get_data_from_ROM();
	Rom_CS(1);
}


/******************************************************************/

unsigned long  fontaddr=0;
void display_GB2312_string(unsigned char y,unsigned char x,unsigned char *text)
{
	unsigned char i= 0;
	unsigned char addrHigh,addrMid,addrLow ;
	unsigned char fontbuf[32];			
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			/*¹ú±ê¼òÌå£¨GB2312£©ºº×ÖÔÚ¾§ÁªÑ¶×Ö¿âICÖĞµÄµØÖ·ÓÉÒÔÏÂ¹«Ê½À´¼ÆËã£º*/
			/*Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0*/
			/*ÓÉÓÚµ£ĞÄ8Î»µ¥Æ¬»úÓĞ³Ë·¨Òç³öÎÊÌâ£¬ËùÒÔ·ÖÈı²¿È¡µØÖ·*/
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = (unsigned long)(fontaddr*32);
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*µØÖ·µÄ¸ß8Î»,¹²24Î»*/
			addrMid = (fontaddr&0xff00)>>8;      /*µØÖ·µÄÖĞ8Î»,¹²24Î»*/
			addrLow = fontaddr&0xff;	     /*µØÖ·µÄµÍ8Î»,¹²24Î»*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*È¡32¸ö×Ö½ÚµÄÊı¾İ£¬´æµ½"fontbuf[32]"*/
			display_graphic_16x16(y,x,fontbuf);/*ÏÔÊ¾ºº×Öµ½LCDÉÏ£¬yÎªÒ³µØÖ·£¬xÎªÁĞµØÖ·£¬fontbuf[]ÎªÊı¾İ*/
			i+=2;
			x+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			/*¹ú±ê¼òÌå£¨GB2312£©15x16µãµÄ×Ö·ûÔÚ¾§ÁªÑ¶×Ö¿âICÖĞµÄµØÖ·ÓÉÒÔÏÂ¹«Ê½À´¼ÆËã£º*/
			/*Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0*/
			/*ÓÉÓÚµ£ĞÄ8Î»µ¥Æ¬»úÓĞ³Ë·¨Òç³öÎÊÌâ£¬ËùÒÔ·ÖÈı²¿È¡µØÖ·*/
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (unsigned long)(fontaddr*32);
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*µØÖ·µÄ¸ß8Î»,¹²24Î»*/
			addrMid = (fontaddr&0xff00)>>8;      /*µØÖ·µÄÖĞ8Î»,¹²24Î»*/
			addrLow = fontaddr&0xff;	     /*µØÖ·µÄµÍ8Î»,¹²24Î»*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*È¡32¸ö×Ö½ÚµÄÊı¾İ£¬´æµ½"fontbuf[32]"*/
			display_graphic_16x16(y,x,fontbuf);/*ÏÔÊ¾ºº×Öµ½LCDÉÏ£¬yÎªÒ³µØÖ·£¬xÎªÁĞµØÖ·£¬fontbuf[]ÎªÊı¾İ*/
			i+=2;
			x+=16;
		}
		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{						
			unsigned char fontbuf[16];			
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);			
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;

			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16 );/*È¡16¸ö×Ö½ÚµÄÊı¾İ£¬´æµ½"fontbuf[32]"*/
			
			display_graphic_8x16(y,x,fontbuf);/*ÏÔÊ¾8x16µÄASCII×Öµ½LCDÉÏ£¬yÎªÒ³µØÖ·£¬xÎªÁĞµØÖ·£¬fontbuf[]ÎªÊı¾İ*/
			i+=1;
			x+=8;
		}
		else
			i++;	
	}
	
}

void display_string_5x7(unsigned char y,unsigned char x,unsigned char *text)
{
	unsigned char i= 0;
	unsigned char addrHigh,addrMid,addrLow ;
	while((text[i]>0x00))
	{
		if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{						
			unsigned char fontbuf[8];			
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*8);
			fontaddr = (unsigned long)(fontaddr+0x3bfc0);			
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;

			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,8);/*È¡8¸ö×Ö½ÚµÄÊı¾İ£¬´æµ½"fontbuf[32]"*/
			
			display_graphic_5x7(y,x,fontbuf);/*ÏÔÊ¾5x7µÄASCII×Öµ½LCDÉÏ£¬yÎªÒ³µØÖ·£¬xÎªÁĞµØÖ·£¬fontbuf[]ÎªÊı¾İ*/
			i+=1;
			x+=6;
		}
		else
		i++;	
	}
	
}


