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

/* ͷ�ļ�����------------------------------------------------------------------*/
#include <stdio.h>
#include "userconfig.h"

u8 EmerStop=0;//����ֹͣ״̬λ�����е��

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
 *��������main
 *������������
 *���룺��
 *�������
 *���ã����������
 */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
	
	extern u8 keyVal,angLX,angLY,angRX,angRY;/**��ֵ,�ĸ�ģ��ֵ, */
	extern vu8 keyBit; /**����ȡ״̬λ*/
	//extern u8 signalCount1;
	extern u8 signalMove,signalHeight;
	u8 autodrive=0;
	
	RCCStart();
	SysTickConfig();
//	TIM4_Config();
  PrintConfig();
	AutoDriveConfig();
//	LEDInit();
	NVICConfig();
	SetPullMotorSpeed(180);
/**
 while(1)
 {
	 if(1==keyBit)
	 {
		PS2_DataKey();
		 keyBit=0;
	 }		 
	 Print(keyVal);
	 Delay_ms(100);
 }
 */
  while (1)
  {
		if(autodrive==1)
			MotorSensorJudge(signalMove);
		else
		{
			PullMotorStop();
			MoveMotorStop();
			RollMotorStop();
		}
		if(1==keyBit)        //��ʱ��ȡ����
		{
			keyVal = PS2_DataKey();	 //�ֱ�����������
	//				PS2_DataKey();	 //�ֱ�����������
//				if(!PS2_RedLight())
//				{
//					angLY = PS2_AnologData(PSS_LY);
//					angLX = PS2_AnologData(PSS_LX);
//					angRX = PS2_AnologData(PSS_RY);
//					angRY = PS2_AnologData(PSS_RX);
//				}
				keyBit=0;		
	//			Print(GPIO_ReadInputDataBit(SENSORIO,SENSORIN3));			
		}		
		if(keyVal!=0)                   //�а�������
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
				SetMoveMotorSpeed(200);
				MoveMotorForward();	
				while(keyVal !=PSB_PAD_UP);
				MoveMotorStop();
			}else if(PSB_PAD_DOWN == keyVal)
			{
				SetMoveMotorSpeed(200);
				MoveMotorBack();
				Delay_ms(20);
				MoveMotorStop();
			}else if(PSB_GREEN == keyVal)
			{
				SetPullMotorSpeed(200);
				PullMotorForward();
				while(keyVal !=PSB_GREEN);				
				PullMotorStop();
			}else if(PSB_BLUE == keyVal)
			{
				SetPullMotorSpeed(200);
				PullMotorBack();
				while(keyVal !=PSB_BLUE);
				PullMotorStop();
			}else if(PSB_PAD_RIGHT == keyVal)
			{
				SetRollMotorSpeed(150);	
				RollMotorForward();
				while(keyVal !=PSB_PAD_RIGHT);
				RollMotorStop();
			}else if(PSB_PAD_LEFT == keyVal)
			{
				SetRollMotorSpeed(130);	
				RollMotorBack();
				while(keyVal !=PSB_PAD_LEFT);
				RollMotorStop();
			}else if(PSB_L1 == keyVal)
			{
					autodrive=1;
			}else if(PSB_L2 == keyVal)
			{
					autodrive=0;
			}
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
