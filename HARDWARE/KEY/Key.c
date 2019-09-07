#include "key.h"
#include "delay.h"
/**************使用说明**********************
矩阵键盘引脚：行PG8——PG11	 列PG12——PG15
按键表盘为：	0  1  2  3 
						4  5  6  7
						8  9  10 11
						12 13 14 15 
************************************/
int key_count=0;
//行 PG8-PG11 	列PG12-PG15
void Key_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
   
	 /********4行输出*********/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOG, &GPIO_InitStructure);
	 
	 /********4列输入*********/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOG, &GPIO_InitStructure);	
}

int KeyScan(void)
{
   uchar KeyVal;
	
   GPIO_Write(GPIOG, (GPIOG->ODR & 0xf0ff | 0x0f00));	 //不管其余12位0xf0ff，先让PG8到PG11全部输出高。
	  
	 if((GPIOG->IDR & 0xf000)==0x0000)   								 //如果PG12到PG15全为零则没有按键按下
		  return -1;
	 else
	 {	
	    delay_ms(5);    //延时5ms去抖动
			
	    if((GPIOG->IDR & 0xf000)==0x0000)
	    return -1;
	 }
	 GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0100));	//仅将PG8置高	 
	 switch(GPIOG->IDR & 0xf000)	//第一行，由低到高，同理，不赘述
	 {
     	case 0x1000: KeyVal=0; break;
			case 0x2000: KeyVal=1;	break;
			case 0x4000: KeyVal=2;	break;
			case 0x8000: KeyVal=3;	break;
   }
	 while((GPIOG->IDR & 0xf000)	> 0);     //等待按键释放
	 
	 GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0200));	//仅将PG9置高
		switch(GPIOG->IDR & 0xf000)		        
		{
			case 0x1000: KeyVal=4;	break;
			case 0x2000: KeyVal=5;	break;
			case 0x4000: KeyVal=6;	break;
			case 0x8000: KeyVal=7;	break;
		}
    while((GPIOG->IDR & 0xf000)	> 0);
		
	  GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0400));	//仅将PG10置高
		switch(GPIOG->IDR & 0xf000)		        
		{
			case 0x1000: KeyVal=8;	break;
			case 0x2000: KeyVal=9;	break;
			case 0x4000: KeyVal=10;	break;
			case 0x8000: KeyVal=11;	break;
		}
    while((GPIOG->IDR & 0xf000)	> 0);
		
	  GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0800));	//仅将PG11置高
		switch(GPIOG->IDR & 0xf000)		        
		{
			case 0x1000: KeyVal=12;	break;
			case 0x2000: KeyVal=13;	break;
			case 0x4000: KeyVal=14;	break;
			case 0x8000: KeyVal=15;	break;
		}
		while((GPIOG->IDR & 0xf000)	> 0);
	  key_count++;
		return KeyVal;
}

/************************************
按键表盘为：	0  1  2  3 
							4  5  6  7
							8  9  10 11
							12 13 14 15 
************************************/
void GetKeyVal(void) 
{
    int num;
	  num = KeyScan();
	  switch(num)
	  { 
        case 0: printf("0\n"); break;					  				      
				case 1: printf("1\n"); break;					  				       
				case 2: printf("2\n"); break;					  				     
				case 3: printf("3\n"); break;					  				     
				case 4: printf("4\n"); break;				 	       
				case 5: printf("5\n"); break;					  				      
				case 6: printf("6\n"); break;					  				      
				case 7: printf("7\n"); break;					 			       
				case 8: printf("8\n"); break;								 		       
				case 9: printf("9\n"); break;							 				     	
			  case 10: printf("10\n"); break;						 				      		
				case 11: printf("11\n"); break;					 				      
				case 12: printf("12\n"); break;							 				      	
			  case 13: printf("13\n"); break;							 				       	
				case 14: printf("14\n"); break;					 				      
				case 15: printf("15\n"); break;					 			      
    }
}
