/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DELAY_H
#define __STM32F10x_DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void SysTickConfig(void);
void Delay_ms(u16,u8 numT);
void Delay_us(u16,u8 numT);
void SysTick_Handler(void);
void TIM4_IRQHandler(void);
void TIM4_Config(void); 
	 
	 
	 
	 

#ifdef __cplusplus
}
#endif

#endif 

