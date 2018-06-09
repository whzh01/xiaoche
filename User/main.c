/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* 头文件包含------------------------------------------------------------------*/
#include <stdio.h>
#include "userconfig.h"

vu8 autodrive=0;

void PrintConfig()
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	USART_InitTypeDef			USART_InitStructure;
	GPIO_InitStructure.GPIO_Pin =CK1RX |CK1TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode= USART_Mode_Tx |USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(TESTUSART,&USART_InitStructure);
	USART_Cmd(TESTUSART,ENABLE);

}
void Print(u16 text)
{

  USART_SendData(TESTUSART,text);
//	for(unum=0;unum<4000 && !USART_GetFlagStatus(USARTCLAW,USART_FLAG_TC) ;unum++);

}
/*
 *函数名：main
 *描述：主程序
 *输入：无
 *输出：无
 *调用：主程序调用
 */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
	
	extern u8 angLX,angLY,angRX,angRY;/**键值,四个模拟值, */
	extern vu8 keyBit; /**键读取状态位*/
	extern u8 signalMove,signalHeight;
	extern u8 keyVal;

	
	RCCStart();
	Delay_Config();
	NVIC_Config();
  PrintConfig();
	AutoDriveConfig();
//	LEDInit();
	SetPullMotorSpeed(200);
	SetRollMotorSpeed(160);

  while (1)
  {
		
		if(autodrive==1) MotorSensorJudge(signalMove);
		
		if(1==keyBit)        //定时读取按键
		{
//		keyVal = PS2_DataKey();	 //手柄按键捕获处理
//			if(!PS2_RedLight())
//			{
//				angLY = PS2_AnologData(PSS_LY);
//				angLX = PS2_AnologData(PSS_LX);
//				angRX = PS2_AnologData(PSS_RY);
//				angRY = PS2_AnologData(PSS_RX);
//			}
				keyBit=0;		
		//		Print(keyVal);			
		}		
		
		if(keyVal!=0)      //有按键按下
		{
			if(PSB_PINK == keyVal)
			{
				ClawClose();
			}
			else if(PSB_RED == keyVal)
			{
				ClawOpen();
			}
			else if(PSB_PAD_UP == keyVal)
			{
				SetMoveMotorSpeed(100);
				MoveMotorForward();	
				while(keyVal ==PSB_PAD_UP);
				MoveMotorStop();
			}else if(PSB_PAD_DOWN == keyVal)
			{
				SetMoveMotorSpeed(100);
				MoveMotorBack();
				while(keyVal ==PSB_PAD_DOWN);
				MoveMotorStop();
			}else if(PSB_GREEN == keyVal)
			{
				SetPullMotorSpeed(200);
				PullMotorForward();
				while(keyVal ==PSB_GREEN);				
				PullMotorStop();
			}else if(PSB_BLUE == keyVal)
			{
				SetPullMotorSpeed(200);
				PullMotorBack();
				while(keyVal ==PSB_BLUE);
				PullMotorStop();
			}else if(PSB_PAD_RIGHT == keyVal)
			{
				SetRollMotorSpeed(150);	
				RollMotorAForward();
				RollMotorBForward();
				while(keyVal ==PSB_PAD_RIGHT);
				RollMotorAStop();
				RollMotorBStop();
			}else if(PSB_PAD_LEFT == keyVal)
			{
				SetRollMotorSpeed(150);	
				RollMotorABack();
				RollMotorBBack();
				while(keyVal ==PSB_PAD_LEFT);
				RollMotorAStop();
				RollMotorBStop();
			}else {}
		}else
		{   
    }
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
