#include "key.h"
#include "delay.h"
/**************ʹ��˵��**********************
����������ţ���PG8����PG11	 ��PG12����PG15
��������Ϊ��	0  1  2  3 
						4  5  6  7
						8  9  10 11
						12 13 14 15 
************************************/
int key_count=0;
//�� PG8-PG11 	��PG12-PG15
void Key_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
   
	 /********4�����*********/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOG, &GPIO_InitStructure);
	 
	 /********4������*********/
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOG, &GPIO_InitStructure);	
}

int KeyScan(void)
{
   uchar KeyVal;
	
   GPIO_Write(GPIOG, (GPIOG->ODR & 0xf0ff | 0x0f00));	 //��������12λ0xf0ff������PG8��PG11ȫ������ߡ�
	  
	 if((GPIOG->IDR & 0xf000)==0x0000)   								 //���PG12��PG15ȫΪ����û�а�������
		  return -1;
	 else
	 {	
	    delay_ms(5);    //��ʱ5msȥ����
			
	    if((GPIOG->IDR & 0xf000)==0x0000)
	    return -1;
	 }
	 GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0100));	//����PG8�ø�	 
	 switch(GPIOG->IDR & 0xf000)	//��һ�У��ɵ͵��ߣ�ͬ����׸��
	 {
     	case 0x1000: KeyVal=0; break;
			case 0x2000: KeyVal=1;	break;
			case 0x4000: KeyVal=2;	break;
			case 0x8000: KeyVal=3;	break;
   }
	 while((GPIOG->IDR & 0xf000)	> 0);     //�ȴ������ͷ�
	 
	 GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0200));	//����PG9�ø�
		switch(GPIOG->IDR & 0xf000)		        
		{
			case 0x1000: KeyVal=4;	break;
			case 0x2000: KeyVal=5;	break;
			case 0x4000: KeyVal=6;	break;
			case 0x8000: KeyVal=7;	break;
		}
    while((GPIOG->IDR & 0xf000)	> 0);
		
	  GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0400));	//����PG10�ø�
		switch(GPIOG->IDR & 0xf000)		        
		{
			case 0x1000: KeyVal=8;	break;
			case 0x2000: KeyVal=9;	break;
			case 0x4000: KeyVal=10;	break;
			case 0x8000: KeyVal=11;	break;
		}
    while((GPIOG->IDR & 0xf000)	> 0);
		
	  GPIO_Write(GPIOG,(GPIOG->ODR & 0xf0ff | 0x0800));	//����PG11�ø�
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
��������Ϊ��	0  1  2  3 
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
