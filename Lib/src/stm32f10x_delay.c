#include "stm32f10x_delay.h"
#define SIZE 5
#define STM_SYSCLK		72
static u16 fac_ms=0;	 
static u16 fac_us=0;	
vu32 TimeDelay[SIZE] = {0};  
vu32 TimeDelayus=0;


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
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 72-1;
	TIM_InitStructure.TIM_Prescaler = 1000-1;					 /*****��ʱ1000us***********************/
	TIM_TimeBaseInit(TIM4,&TIM_InitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_GetFlagStatus(TIM4,TIM_FLAG_Update);
	TIM_Cmd(TIM4,ENABLE);
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
		for(u8 i=0;i<SIZE;i++)
		{
			if(TimeDelay[i] != 0)
				TimeDelay[i]-=1;
		}
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

	if(	SysTick_Config(STM_SYSCLK))
	{
		while(1);
	}
  SysTick->CTRL =0x00;
  fac_us=STM_SYSCLK/8;  
  fac_ms=fac_us*1000;  
}
/*
 *��������Delay_ms
 *��������ʱ��������λms���������ü����ݴ���ʵ�ֶ��ͬʱ��ʱ����Ӱ��
 *���룺count������ֵ�����ٺ���
				numT��ѡ������ݴ���
 *�������
 *���ã��ⲿ����
 */
void Delay_ms(u16 count,u8 numT)
{
	  TimeDelay[numT] = count;
    while(TimeDelay[numT] !=0);  
}
/*
 *��������Delay_us
 *��������ʱ��������λus,ֻ�ܵ�����ʱ
 *���룺nus������ֵ������΢��
 *�������
 *���ã��ⲿ����
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
 *��������Delay_Config
 *��������ʱ���ú���
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void Delay_Config()
{
	TIM4_Config();
	SysTickConfig();
}



