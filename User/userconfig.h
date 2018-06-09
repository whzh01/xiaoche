/**************************************************************
	userconfig.h ����ͳһ����Ӳ����Դ���������ڣ���ʱ����AD��
			�����û��Զ����ͷ�ļ�
			ֻ���������û��Զ�����ļ��У�ԭ���ļ���ϵͳ�����ļ�
			����Ҫ�������ļ�

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

#define TIMMOTOR			TIM3             /*�������Ƶ����pwm----------*/
#define USARTCLAW			USART2					/**���Ͷ�������ź�**********/   
#define TESTUSART			USART1	        /**���Դ��ڻ�������Ϣ������**/
#define SIGNALTIM			TIM2						/**���ڻ�ȡ�������źź�ִ�ж�����ʱ**/
/*******************************
	 PB6-11���ڵ��������
				IN1,2,3,4,5,6	 
	 PB12-15����ң����SPIͨѶ
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
	PC6~PC8���ڲ������������PWM
*****************************************/
#define PWMTIMIO				GPIOC
#define PWMTIMIO1				GPIO_Pin_6
#define PWMTIMIO2				GPIO_Pin_7
#define PWMTIMIO3				GPIO_Pin_8
#define PWMTIMIO4				GPIO_Pin_9
/*****************************************
	PB0~1 ���ڽ��մ������ź�
*****************************************/
#define SENSORIO				GPIOC
#define SENSORIN1				GPIO_Pin_0    //���߶�λ������
#define SENSORIN2				GPIO_Pin_1		//�߶ȴ�����
#define SENSORIN3				GPIO_Pin_2    //�ƶ���еצ��λ������A��
#define SENSORIN4				GPIO_Pin_3		//�ƶ���еצ��λ������A��
#define SENSORIN5				GPIO_Pin_4		//�ƶ���еצ��λ������B��
#define SENSORIN6				GPIO_Pin_5		//�ƶ���еצ��λ������B��

/*****************************************
	PA9~PA10��Ϊ�ڶ����ܣ�USART1�ķ��ͺ�
	�������ţ���Ϊ�������ʹ��,��ʽ����
	�в����øö˿�
*****************************************/
#define CK						GPIOA
#define CK1TX					GPIO_Pin_9
#define CK1RX					GPIO_Pin_10


	 
	 
	 
	 
	 

	 
	 
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 




