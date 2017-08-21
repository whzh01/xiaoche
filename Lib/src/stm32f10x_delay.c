#include "stm32f10x_delay.h"

vu32 TimeDelay = 0;  

void SysTickConfig()
{
	
	NVIC_InitTypeDef		NVIC_InitStructure;
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



