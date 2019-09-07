#include "timer.h"
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB2��2������APB1Ϊ36M
//arr:�Զ���װֵ
//psc:ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3
//Tout= ((arr+1)*(psc+1))/Tclk;
//Tclk: TIM3 ����ʱ��Ƶ��(��λΪ Mhz)��
//Tout: TIM3 ���ʱ��(��λΪ us)��
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʱ��ʹ��TIM3ʹ��
	
	//ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //��ʼ�� TIM3
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //��������ж�
	
	//�ж����ȼ� NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure); //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM3, ENABLE); //ʹ�� TIM3
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//ʱ��ʹ��TIM5ʹ��
	
	//ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //��ʼ�� TIM5
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //��������ж�
	
	//�ж����ȼ� NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //TIM5 �ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ ͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure); //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM5, ENABLE); //ʹ�� TIM5
}

//TIM2 PWM ȫ����ʼ��
//PWM �����ʼ��
//arr:�Զ���װֵ
//psc:ʱ��Ԥ��Ƶ��
//Ƶ��f=Tclk/(arr+1)/(psc+1)
//����T=1/f=((arr+1)*(psc+1))/Tclk
//TCLK=72MHz
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʹ�ܶ�ʱ��3ʱ��

	//���ø�����Ϊ����������ܣ���� TIM2 CH1 ��PWM���岨��   GPIOA.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//���ø�����Ϊ����������ܣ���� TIM2 CH2 ��PWM���岨��   GPIOA.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO

	//���ø�����Ϊ����������ܣ���� TIM2 CH3 ��PWM���岨��   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//���ø�����Ϊ����������ܣ���� TIM2 CH4 ��PWM���岨��   GPIOA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//��ʼ�� TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //�������Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ�� TIMx
	
	//��ʼ�� TIM2 Channel1~4 PWM ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ�� PWM ģʽ 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������Ե�
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure); //��ʼ������ TIM2 OC1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); //��ʼ������ TIM2 OC2
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���

	TIM_OC3Init(TIM2, &TIM_OCInitStructure); //��ʼ������ TIM2 OC3
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���

	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //��ʼ������ TIM2 OC4
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���



	TIM_Cmd(TIM2, ENABLE); //ʹ�� TIM2
}

//TIM3 PWM ȫ����ʼ��
//PWM �����ʼ��
//arr:�Զ���װֵ
//psc:ʱ��Ԥ��Ƶ��
//Ƶ��f=Tclk/(arr+1)/(psc+1)
//����T=1/f=((arr+1)*(psc+1))/Tclk
//TCLK=72MHz
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܶ�ʱ��3ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //ʹ�� GPIO �� AFIO ���ù���ʱ��
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //��ӳ�� TIM3_CH2->PB5

	//���ø�����Ϊ����������ܣ���� TIM3 CH2 ��PWM���岨��   GPIOA.6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//���ø�����Ϊ����������ܣ���� TIM3 CH2 ��PWM���岨��   GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� GPIO

	//���ø�����Ϊ����������ܣ���� TIM3 CH2 ��PWM���岨��   GPIOB.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//���ø�����Ϊ����������ܣ���� TIM3 CH2 ��PWM���岨��   GPIOB.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ�� GPIO
	
	//��ʼ�� TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //�������Զ���װ������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //��ʼ�� TIMx
	
	//��ʼ�� TIM3 Channel1~4 PWM ģʽ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ�� PWM ģʽ 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������Ե�
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); //��ʼ������ TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); //��ʼ������ TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���

	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //��ʼ������ TIM3 OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���

	TIM_OC4Init(TIM3, &TIM_OCInitStructure); //��ʼ������ TIM3 OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���



	TIM_Cmd(TIM3, ENABLE); //ʹ�� TIM3
}


