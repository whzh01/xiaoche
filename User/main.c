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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "userconfig.h"


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
	
	u8  i;
	extern u8 keyVal,angLX,angLY,angRX,angRY;/**键值,四个模拟值, */
	extern vu8 keyBit; /**键读取状态位*/
	
	
	RCCStart();
	SysTickConfig();
	AutoDriveConfig();
	LEDInit();
	NVICConfig();
	SetMoveMotorSpeed(50);
	SetPullMotorSpeed(50);
	
  while (1)
  {
		/******************************
		测试舵机的开闭
		****************************** 
		
		USART_SendData(USARTCLAW,0x99);
		ClawClose();
		Delay_ms(1000);
		Delay_ms(1000);
		ClawOpen();
		Delay_ms(1000);
		Delay_ms(1000);
		*************************/
			if(1==keyBit)        //定时读取按键
			{
					PS2_DataKey();	 //手柄按键捕获处理
					if(!PS2_RedLight())
					{
						angLY = PS2_AnologData(PSS_LY);
						angLX = PS2_AnologData(PSS_LX);
						angRX = PS2_AnologData(PSS_RY);
						angRY = PS2_AnologData(PSS_RX);	
					}else
					{
						angLY = angLX=angRX = angRY=127;
					}
					keyBit=0;			
			}
			
			if(keyVal!=0)                   //有按键按下
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
					SetMoveMotorSpeed(80);
					MoveMotorForward();
					Delay_ms(100);
					SetMoveMotorSpeed(0);
				}else if(PSB_PAD_DOWN == keyVal)
				{
					SetMoveMotorSpeed(50);
					MoveMotorBack();
					Delay_ms(100);
					SetMoveMotorSpeed(0);
		
				}else if(PSB_GREEN == keyVal)
				{
					SetPullMotorSpeed(50);
					PullMotorForward();
					Delay_ms(100);
					SetPullMotorSpeed(0);
		
				}else if(PSB_BLUE == keyVal)
				{
					SetPullMotorSpeed(50);
					PullMotorBack();
					Delay_ms(100);
					SetPullMotorSpeed(0);
				}else 
				{
					
				}
		  }else
			{
				if(angLY-127>10)
				{
					SetMoveMotorSpeed((angLY-127)*100/127);
					MoveMotorBack();
					Delay_ms(100);
					SetMoveMotorSpeed(0);
				}else if(127-angLY>10)
				{
					SetMoveMotorSpeed((127-angLY)*100/127);
					MoveMotorForward();
					Delay_ms(100);
					SetMoveMotorSpeed(0);
				}else if(angRY-127>10)
				{
					SetPullMotorSpeed((angRY-127)*100/127);
					PullMotorBack();
					Delay_ms(100);
					SetPullMotorSpeed(0);
				}else if(127-angRY>10)
				{
					SetPullMotorSpeed((127-angRY)*100/127);
					PullMotorForward();
					Delay_ms(100);
					SetPullMotorSpeed(0);
				}else
				{
				}
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
