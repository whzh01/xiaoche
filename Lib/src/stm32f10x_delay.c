#include "stm32f10x_delay.h"
#define SIZE 5
vu32 TimeDelay[SIZE] = {0};  

/*
 *函数名：TIM4_Config
 *描述：定时器4配置函数，与Systick功能一致，不可同时启用
 *输入：无
 *输出：无
 *调用：外部调用
 */
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
/*
 *函数名：TIM4_IRQHandler
 *描述：定时器4中断函数
 *输入：无
 *输出：无
 *调用：外部调用
 */
void TIM4_IRQHandler()
{
		/***产生延时的1us信号*********************/
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	}
}
/*
 *函数名：SysTickConfig
 *描述：配置滴答定时器
 *输入：无
 *输出：无
 *调用：外部调用
 */
void SysTickConfig()
{

	if(	SysTick_Config(72))
	{
		while(1);
	}
	NVIC_SetPriority(SysTick_IRQn,3);

}
/*
 *函数名：Delay_ms
 *描述：延时函数，单位ms
 *输入：count：计数值，多少毫秒
				numT：选择计数暂存区
 *输出：无
 *调用：外部调用
 */
void Delay_ms(u16 count,u8 numT)
{
	  TimeDelay[numT] = count*1000;  
    while(TimeDelay[numT] !=0);  
}
/*
 *函数名：Delay_us
 *描述：延时函数，单位us
 *输入：count：计数值，多少毫秒
				numT：选择计数暂存区
 *输出：无
 *调用：外部调用
 */
void Delay_us(u16 count,u8 numT) 
{
	  TimeDelay[numT] = count;  
    while(TimeDelay[numT] !=0);  
}
/*
 *函数名：SysTick_Handler
 *描述：滴答中断函数，对计数缓冲区的数值做减一处理
 *输入：无
 *输出：无
 *调用：外部调用
 */
void SysTick_Handler(void)
{
	for(int i=0;i<SIZE;i++)
	{
		if(TimeDelay[i] != 0)
			TimeDelay[i]--;
	}

}



