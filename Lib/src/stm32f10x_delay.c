#include "stm32f10x_delay.h"

vu32 TimeDelay = 0;  

void TIM4_Config()
{
	TIM_TimeBaseInitTypeDef				TIM_InitStructure;
		/***产生延时的1us信号*********************/
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 36-1;
	TIM_InitStructure.TIM_Prescaler = 0;					 /*****定时1us***********************/
	TIM_TimeBaseInit(TIM4,&TIM_InitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	NVIC_SetPriority(SysTick_IRQn,3);
}
void TIM4_IRQHandler()
{
		/***产生延时的1us信号*********************/
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		if(TimeDelay != 0)
			TimeDelay--;
	}
}
void SysTickConfig()
{

	if(	SysTick_Config(72))
	{
		while(1);
	}
	NVIC_SetPriority(SysTick_IRQn,3);

}
void Delay_ms(u16 count)
{
	  TimeDelay = count*1000;  
    while(TimeDelay !=0);  
}

void Delay_us(u16 count) 
{
	  TimeDelay = count;  
    while(TimeDelay !=0);  
}
void SysTick_Handler(void)
{

	if(TimeDelay != 0)
		TimeDelay--;
}



