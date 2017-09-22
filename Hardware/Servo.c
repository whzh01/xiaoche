/*Include		******************************************************************************/
#include "servo.h"

/*Define ********************************************************************************/

/********************动作组********************/
u8 DM_Action0[5]   = { 0xff, 0x09, 0x00, 0x00, 0x00 };               //关闭机械爪
u8 DM_Action1[5]   = { 0xff, 0x09, 0x00, 0x01, 0x00 };               //打开机械抓
u8 DM_Action2[5]   = { 0xff, 0x09, 0x00, 0x02, 0x00 };               //调节中位
u8 DM_Action3[5]   = { 0xff, 0x09, 0x00, 0x03, 0x00 };               //动作组3


/********************急停，恢复******************/
u8 DMStart[5]={0xFF, 0x0b ,0x00 ,0x01 ,0x00};
u8 DMStop[5]= {0xFF, 0x0b ,0x00 ,0x00 ,0x00};

/*Declaration************************************************************************************************/
void SendCmd(u8*,u8);




void ClawOpen()
{
	SendCmd(DM_Action1,5);
	Delay_ms(1000,0);
}
void ClawClose()
{
	SendCmd(DM_Action0,5);
	Delay_ms(1000,0);
}
void ServoStart()
{
	SendCmd(DMStart,5);
}
void ServoStop()
{
	SendCmd(DMStop,5);
}
void SendCmd(u8* d,u8 num)
{
	u8  cnum;
	u16 unum;
	for(cnum=0;cnum<num;cnum++)
	{
		USART_SendData(USARTCLAW,*(d++));
		for(unum=0;unum<4000 && !USART_GetFlagStatus(USARTCLAW,USART_FLAG_TC) ;unum++);
	}
}
void ServoConfig()
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	USART_InitTypeDef			USART_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode= USART_Mode_Tx |USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USARTCLAW,&USART_InitStructure);
	USART_Cmd(USARTCLAW,ENABLE);
	USART_GetFlagStatus(USARTCLAW,USART_FLAG_TC);
	
}
/***********************************************************
void USART2_IRQHandler(void)
{
  
	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
    USART_SendData(USART2, TxBuffer[TxCounter++]); 
    if(TxCounter == count) 
		{
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);// 全部发送完成
		}
    USART_ClearITPendingBit(USART2, USART_IT_TXE); 
  }
	else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
	
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART2,USART_IT_ORE);

}
*********************************************************/

