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
#define MOTORIN7				GPIO_Pin_0
#define MOTORIN8				GPIO_Pin_1
#define CONTROLIO				GPIOB
#define CONTROLCS				GPIO_Pin_12
#define CONTROLSCK			GPIO_Pin_13
#define CONTROLMI				GPIO_Pin_14
#define CONTROLMO				GPIO_Pin_15
/*****************************************
	PC6~PC8用于产生驱动电机的PWM
*****************************************/
#define PWMTIMIO				GPIOC
#define PWMTIMIO1				GPIO_Pin_6
#define PWMTIMIO2				GPIO_Pin_7
#define PWMTIMIO3				GPIO_Pin_8
#define PWMTIMIO4				GPIO_Pin_9
/*****************************************
	PB0~1 用于接收传感器信号
*****************************************/
#define SENSORIO				GPIOC
#define SENSORIN1				GPIO_Pin_0    //行走定位传感器
#define SENSORIN2				GPIO_Pin_1		//高度传感器
#define SENSORIN3				GPIO_Pin_2    //移动机械爪定位传感器A外
#define SENSORIN4				GPIO_Pin_3		//移动机械爪定位传感器A内
#define SENSORIN5				GPIO_Pin_4		//移动机械爪定位传感器B外
#define SENSORIN6				GPIO_Pin_5		//移动机械爪定位传感器B内

/*****************************************
	PA9~PA10作为第二功能，USART1的发送和
	接收引脚，作为测试输出使用,正式程序
	中不启用该端口
*****************************************/
#define CK						GPIOA
#define CK1TX					GPIO_Pin_9
#define CK1RX					GPIO_Pin_10


	 
	 
	 
	 
	 

	 
	 
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 




