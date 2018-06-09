#include "stm32f10x_delay.h"
#define SIZE 5
#define STM_SYSCLK		72
static u16 fac_ms=0;	 
static u16 fac_us=0;	
vu32 TimeDelay[SIZE] = {0};  
vu32 TimeDelayus=0;


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
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 72-1;
	TIM_InitStructure.TIM_Prescaler = 1000-1;					 /*****定时1000us***********************/
	TIM_TimeBaseInit(TIM4,&TIM_InitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_GetFlagStatus(TIM4,TIM_FLAG_Update);
	TIM_Cmd(TIM4,ENABLE);
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
		for(u8 i=0;i<SIZE;i++)
		{
			if(TimeDelay[i] != 0)
				TimeDelay[i]-=1;
		}
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

	if(	SysTick_Config(STM_SYSCLK))
	{
		while(1);
	}
  SysTick->CTRL =0x00;
  fac_us=STM_SYSCLK/8;  
  fac_ms=fac_us*1000;  
}
/*
 *函数名：Delay_ms
 *描述：延时函数，单位ms，可以利用计数暂存区实现多个同时延时互不影响
 *输入：count：计数值，多少毫秒
				numT：选择计数暂存区
 *输出：无
 *调用：外部调用
 */
void Delay_ms(u16 count,u8 numT)
{
	  TimeDelay[numT] = count;
    while(TimeDelay[numT] !=0);  
}
/*
 *函数名：Delay_us
 *描述：延时函数，单位us,只能单个延时
 *输入：nus：计数值，多少微秒
 *输出：无
 *调用：外部调用
 */
void Delay_us(u16 nus)  
{  
    u32 temp;  
    SysTick->LOAD	=(u32)(nus*fac_us);  
    SysTick->VAL	=0x00;  
    SysTick->CTRL	=0x01;  
    do  
    {  
        temp=SysTick->CTRL;  
    }  
    while(temp&0x01&&!(temp&0x10000));
    SysTick->CTRL	=0x00;
    SysTick->VAL	=0x00;     
} 

/*
 *函数名：Delay_Config
 *描述：延时配置函数
 *输入：无
 *输出：无
 *调用：外部调用
 */
void Delay_Config()
{
	TIM4_Config();
	SysTickConfig();
}



