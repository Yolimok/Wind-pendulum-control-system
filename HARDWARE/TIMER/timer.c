#include "timer.h"
//通用定时器3中断初始化
//这里时钟选择为APB2都2倍，而APB1为36M
//arr:自动重装值
//psc:时钟预分频数
//这里使用的是定时器3
//Tout= ((arr+1)*(psc+1))/Tclk;
//Tclk: TIM3 输入时钟频率(单位为 Mhz)。
//Tout: TIM3 溢出时间(单位为 us)。
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//时钟使能TIM3使能
	
	//时钟TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //初始化 TIM3
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //允许更新中断
	
	//中断优先级 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //TIM3 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure); //初始化NVIC寄存器
	
	TIM_Cmd(TIM3, ENABLE); //使能 TIM3
}
void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//时钟使能TIM5使能
	
	//时钟TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //初始化 TIM5
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); //允许更新中断
	
	//中断优先级 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //TIM5 中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道被使能
	NVIC_Init(&NVIC_InitStructure); //初始化NVIC寄存器
	
	TIM_Cmd(TIM5, ENABLE); //使能 TIM5
}

//TIM2 PWM 全部初始化
//PWM 输出初始化
//arr:自动重装值
//psc:时钟预分频数
//频率f=Tclk/(arr+1)/(psc+1)
//周期T=1/f=((arr+1)*(psc+1))/Tclk
//TCLK=72MHz
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //使能定时器3时钟

	//设置该引脚为复用输出功能，输出 TIM2 CH1 的PWM脉冲波形   GPIOA.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO
	
	//设置该引脚为复用输出功能，输出 TIM2 CH2 的PWM脉冲波形   GPIOA.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO

	//设置该引脚为复用输出功能，输出 TIM2 CH3 的PWM脉冲波形   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO
	
	//设置该引脚为复用输出功能，输出 TIM2 CH4 的PWM脉冲波形   GPIOA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO
	
	//初始化 TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化 TIMx
	
	//初始化 TIM2 Channel1~4 PWM 模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性低
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure); //初始化外设 TIM2 OC1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); //初始化外设 TIM2 OC2
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器

	TIM_OC3Init(TIM2, &TIM_OCInitStructure); //初始化外设 TIM2 OC3
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器

	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //初始化外设 TIM2 OC4
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); //使能预装载寄存器



	TIM_Cmd(TIM2, ENABLE); //使能 TIM2
}

//TIM3 PWM 全部初始化
//PWM 输出初始化
//arr:自动重装值
//psc:时钟预分频数
//频率f=Tclk/(arr+1)/(psc+1)
//周期T=1/f=((arr+1)*(psc+1))/Tclk
//TCLK=72MHz
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能定时器3时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //使能 GPIO 和 AFIO 复用功能时钟
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //重映射 TIM3_CH2->PB5

	//设置该引脚为复用输出功能，输出 TIM3 CH2 的PWM脉冲波形   GPIOA.6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO
	
	//设置该引脚为复用输出功能，输出 TIM3 CH2 的PWM脉冲波形   GPIOA.7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 GPIO

	//设置该引脚为复用输出功能，输出 TIM3 CH2 的PWM脉冲波形   GPIOB.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIO
	
	//设置该引脚为复用输出功能，输出 TIM3 CH2 的PWM脉冲波形   GPIOB.1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化 GPIO
	
	//初始化 TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在自动重装载周期值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //初始化 TIMx
	
	//初始化 TIM3 Channel1~4 PWM 模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性低
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); //初始化外设 TIM3 OC1
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure); //初始化外设 TIM3 OC2
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器

	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //初始化外设 TIM3 OC3
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器

	TIM_OC4Init(TIM3, &TIM_OCInitStructure); //初始化外设 TIM3 OC4
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //使能预装载寄存器



	TIM_Cmd(TIM3, ENABLE); //使能 TIM3
}


