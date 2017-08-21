/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DELAY_H
#define __STM32F10x_DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void SysTickConfig(void);
void Delay_ms(u16);
void Delay_us(u16);
void SysTick_Handler(void);

	 
	 
	 
	 
	 

#ifdef __cplusplus
}
#endif

#endif 

