#include "stm32f10x_delay.h"
#define SIZE 5
vu32 TimeDelay[SIZE] = {0};  

/*
 *��������TIM4_Config
 *��������ʱ��4���ú�������Systick����һ�£�����ͬʱ����
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void TIM4_Config()
{
	TIM_TimeBaseInitTypeDef				TIM_InitStructure;
		/***������ʱ��1us�ź�*********************/
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 36-1;
	TIM_InitStructure.TIM_Prescaler = 0;					 /*****��ʱ1us***********************/
	TIM_TimeBaseInit(TIM4,&TIM_InitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	NVIC_SetPriority(SysTick_IRQn,3);
}
/*
 *��������TIM4_IRQHandler
 *��������ʱ��4�жϺ���
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void TIM4_IRQHandler()
{
		/***������ʱ��1us�ź�*********************/
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	
	}
}
/*
 *��������SysTickConfig
 *���������õδ�ʱ��
 *���룺��
 *�������
 *���ã��ⲿ����
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
 *��������Delay_ms
 *��������ʱ��������λms
 *���룺count������ֵ�����ٺ���
				numT��ѡ������ݴ���
 *�������
 *���ã��ⲿ����
 */
void Delay_ms(u16 count,u8 numT)
{
	  TimeDelay[numT] = count*1000;  
    while(TimeDelay[numT] !=0);  
}
/*
 *��������Delay_us
 *��������ʱ��������λus
 *���룺count������ֵ�����ٺ���
				numT��ѡ������ݴ���
 *�������
 *���ã��ⲿ����
 */
void Delay_us(u16 count,u8 numT) 
{
	  TimeDelay[numT] = count;  
    while(TimeDelay[numT] !=0);  
}
/*
 *��������SysTick_Handler
 *�������δ��жϺ������Լ�������������ֵ����һ����
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void SysTick_Handler(void)
{
	for(int i=0;i<SIZE;i++)
	{
		if(TimeDelay[i] != 0)
			TimeDelay[i]--;
	}

}



