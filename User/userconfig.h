/**************************************************************
	userconfig.h 负责统一分配硬件资源，包括串口，定时器，AD等
			包含用户自定义的头文件
			只被包含于用户自定义的文件中，原库文件及系统配置文件
			不需要包含此文件

*************************************************************/
#ifndef __USERCONFIG_H
#define __USERCONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "servo.h"
#include "sensor.h"
#include "motor.h"
#include "autodrive.h"
#include "pstwo.h"
/* Define ------------------------------------------------------------------*/	 

#define TIMMOTOR			TIM3             /*产生控制电机的pwm----------*/
#define USARTCLAW			USART2					/**发送舵机控制信号**********/   
#define TESTUSART			USART1	        /**测试串口或用作信息传输检测**/
#define SIGNALTIM			TIM2						/**用于获取传感器信号和执行动作定时**/
/*******************************
	 PB6-11用于电机驱动板
				IN1,2,3,4,5,6	 
	 PB12-15用于遥控器SPI通讯
	****************************/
#define MOTORIO					GPIOB
#define MOTORIN1				GPIO_Pin_8			
#define MOTORIN2				GPIO_Pin_9
#define MOTORIN3	 			GPIO_Pin_10
#define MOTORIN4				GPIO_Pin_11
#define MOTORIN5				GPIO_Pin_6
#define MOTORIN6				GPIO_Pin_7
#define PWMTIMIO				GPIOC
#define PWMTIMIO1				GPIO_Pin_6
#define PWMTIMIO2				GPIO_Pin_7
#define PWMTIMIO3				GPIO_Pin_8
#define SENSORIO				GPIOB
#define SENSORIN1				GPIO_Pin_0
#define SENSORIN2				GPIO_Pin_1
#define CONTROLIO				GPIOB
#define CONTROLCS				GPIO_Pin_12
#define CONTROLSCK			GPIO_Pin_13
#define CONTROLMI				GPIO_Pin_14
#define CONTROLMO				GPIO_Pin_15


	 
	 
	 
	 
	 

	 
	 
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 




