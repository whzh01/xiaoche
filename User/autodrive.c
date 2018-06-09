/********************************************************
���⴫����˵����
	������ֵ��
		��ɫ��0
		��ɫ��1����⵽��
		
*********************************************************/
/**ͷ�ļ�����----------------------------------------------*/
#include "autodrive.h"
/*��������  ---------------------------------------------*/
u8 signalMove=0,signalHeight=0;//�洢���ߴ������͸߶ȴ�������Ӧ����
u8 validMove=1;   //���ߴ������ź���Ч״̬λ����֤ͬһ��λ��ֻ����һ��
u8 validHeight=0;	//�߶ȴ������ź���Ч״̬λ����֤ͬһ��λ��ֻ����һ��
u8 keyBit=0;			//��ʱ��ȡң�����ź�״̬λ
u8 keyVal;      //�洢��ǰң���ź�ֵ
extern vu8 autodrive;
/**�ڲ���������-----------------------------------------------------*/


/*
 *��������SignalCheck
 *�������źż�����ú���
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void SignalCheck()
{
	TIM_TimeBaseInitTypeDef				TIM_InitStructure;
	
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 100-1;
	TIM_InitStructure.TIM_Prescaler = 36-1;					 /*****��ʱ100us***********************/
	TIM_TimeBaseInit(SIGNALTIM,&TIM_InitStructure);
	TIM_ITConfig(SIGNALTIM,TIM_IT_Update,ENABLE);
	TIM_Cmd(SIGNALTIM,ENABLE);
}
/*
 *��������TIM2_IRQHandler
 *������TIM2��ʱ�жϣ����ڼ�⴫�����ź�
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void TIM2_IRQHandler()
{
	static vu8 nkey0=0,nkey1=0;
	static vu8 nkey3=0,nkey4=0;
	static u16 npsc=0;//�ֱ���ȡ״̬λ��ÿ50ms��ȡһ�Ρ�
	
	if(TIM_GetITStatus(SIGNALTIM,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(SIGNALTIM,TIM_IT_Update);
		if(500 ==npsc)
		{
			
			npsc=0;
			keyBit=1;		//��ʱ�źţ������������ж�ʱ��ȡң�����ź�
			keyVal = PS2_DataKey();	 //�ֱ�����������
			if(PSB_L1 == keyVal)
			{
				//�Զ���ʻ
					autodrive=1;
			}else if(PSB_L2 == keyVal)
			{
				//ֹͣ�Զ���ʻ
					autodrive=0;
					EmStop();
			}else{}
		}else
		{
			npsc++;
		}
		//�ж�����λ�ô������ź�
		if(30==nkey1)
		{
			//1�ź���Ч
			nkey0=0;
			nkey1=0;
			validMove =1;
		}else if(30==nkey0 && validMove==1)
		{
			//0�ź���Ч
			validMove=0;  //��1�ź���Ч
			nkey0=0;
			nkey1=0;
			signalMove++;
		}else
		{
			if(1==GPIO_ReadInputDataBit(SENSORIO,SENSORIN1))
				nkey1++;
			else
				nkey0++;
		}
		//�жϸ߶ȴ������ź�
		if(30 == nkey4)
		{
			//1�ź���Ч
			nkey3=0;
			nkey4=0;
			validHeight =1;
		}else if(30 == nkey3 && validHeight==1)
		{
					//1�ź���Ч
			validHeight=0;  //��1�ź���Ч
			nkey3=0;
			nkey4=0;
			signalHeight++;
		}else
		{
			if(1 == GPIO_ReadInputDataBit(SENSORIO,SENSORIN2))
				nkey4++;
			else
				nkey3++;
		}
		
	}
}
/*
 *��������EmStop
 *����������ֹͣ���е��
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void EmStop()
{
	MoveMotorStop();
	PullMotorStop();
	RollMotorAStop();
	RollMotorBStop();
}
/*
 *��������Wait
 *�������źŵȴ����жϺ���
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void NOWait(u8 sig, u8 val)
{
	while((sig<val) && (autodrive ==1));
}
/*
 *��������RollForwardAction
 *������������������λ(��ഫ������
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void RollForwardAction()
{
	u8 sa=1,sb=1;
	u8 sa0=0,sa1=0,sb0=0,sb1=0;
	
	RollMotorAForward();
	RollMotorBForward();
	for(;sa!=0||sb!=0;)
	{
		if(autodrive ==0) 
		{
			EmStop();
			return;
		}
		if(sa !=0)
		{
			for(u8 cont=0;cont<30;cont++)
				GPIO_ReadInputDataBit(SENSORIO,SENSORIN4)==0?sa0++:sa1++;
			if(sa0>20) sa=0;
		}
		if(sb !=0)
		{
			for(u8 cont=0;cont<30;cont++)
				GPIO_ReadInputDataBit(SENSORIO,SENSORIN6)==0?sb0++:sb1++;	
			if(sb0>20) sb=0;
		}
		if(sb==0)
		{
			RollMotorAStop();
			USART_SendData(TESTUSART,0x1A);
		}
		if(sa==0)
		{
			RollMotorBStop();
			USART_SendData(TESTUSART,0x1B);
		}
	}

}
/*
 *��������RollBackAction
 *������������������λ(�ڲഫ������
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void RollBackAction()
{
	u8 sa0=0,sa1=0,sb0=0,sb1=0;
	
	RollMotorABack();
	RollMotorBBack();
	for(u8 sa=1,sb=1;sa!=0 || sb!=0;)
	{
		if(autodrive ==0) return;
		if(sa !=0)
		{
			for(u8 cont=0;cont<30;cont++)
				GPIO_ReadInputDataBit(SENSORIO,SENSORIN3)==0?sa0++:sa1++;
			if(sa0>20) sa=0;
		}
		if(sb !=0)
		{
			for(u8 cont=0;cont<30;cont++)
				GPIO_ReadInputDataBit(SENSORIO,SENSORIN5)==0?sb0++:sb1++;	
			if(sb0>20) sb=0;
		}
		if(sb==0)
		{
			RollMotorAStop();
			USART_SendData(TESTUSART,0x0A);
		}
		if(sa==0)
		{
			RollMotorBStop();
		  USART_SendData(TESTUSART,0x0B);
		}
	}
}
/*
 *��������Action
 *����������λ���¼���������
 *���룺��
 *�������
 *���ã��ⲿ����
 */

void Action()
{
	//��ʼ����
		SetMoveMotorSpeed(160);
		MoveMotorBack();
		ClawOpen();
		PullMotorForward();
	//	Wait(signalHeight,2);
		while(signalHeight <2 && autodrive ==1);
		PullMotorStop();
	//�����ٶ�
		SetMoveMotorSpeed(90);
}
/*
 *��������Action1
 *����������λ���¼���������1
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void Action1(u8 height)
{
	//�ظ��ź�4�㶯�����߶��źŲ�ͬ
	//ͣ���գ���2����->B��
		MoveMotorStop();
		PullMotorBack();
//		Wait(signalHeight,height-1);
	  while(signalHeight<height-1 && (autodrive ==1));
	  PullMotorStop();
		ClawClose();
		PullMotorForward();
//		Wait(signalHeight,height);
		while(signalHeight<height && (autodrive ==1));
		PullMotorStop();
		SetMoveMotorSpeed(60);
		MoveMotorForward();
		Delay_ms(1200,0);
    SetMoveMotorSpeed(90);	
}
/*
 *��������Action2
 *����������λ���¼���������2
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void Action2(u8 h1,u8 h2)    
{
	//ͣ���ƣ��£������ϣ��ȣ���
		SetPullMotorSpeed(80);
		SetRollMotorSpeed(130);
		MoveMotorStop();
	//���߶���
		RollBackAction();
//		Delay_ms(1000,0);
		Delay_ms(1000,0);
		PullMotorBack();
	//	Wait(signalHeight,h1);
		while(signalHeight<h1 && (autodrive ==1));
		PullMotorStop();
		ClawOpen();
		SetPullMotorSpeed(80);
		PullMotorForward();
		Delay_ms(1000,0);
		SetPullMotorSpeed(200);
	//	Wait(signalHeight,h2);
		while(signalHeight<h2 && (autodrive ==1));
		PullMotorStop();
		SetMoveMotorSpeed(150);
		SetRollMotorSpeed(180);
	  MoveMotorBack();
		RollForwardAction();
}
void Action3(u8 h)
{
	//���٣���1
	SetMoveMotorSpeed(10);
	Delay_ms(1000,0);
	SetMoveMotorSpeed(50);
//	PullMotorBack();
//	while(signalHeight<h);
//	PullMotorStop();
}
void Action4()
{
	u8 cHeight=signalHeight;
	MoveMotorStop();
//	PullMotorBack();
//	while(signalHeight<7);
//	PullMotorStop();
	PullMotorForward();
	while(signalHeight < cHeight+1);
	ClawOpen();
	PullMotorForward();
	while(signalHeight<9);
	PullMotorStop();
	SetMoveMotorSpeed(80);
	MoveMotorBack();
}


/**********************************
1.�޶���
2.�½�ץȡ���Ӳ�������������ʻ
3.�޶���
4.����ָ��λ�ã���������
5.
6.�����һλ��
7.����ڶ�λ�ã�ִ�ж���2
8.
9.�����һλ��
10.ִ�ж���4
11.
12.�����һλ��
13.����ڶ�λ��
14.�������λ�ã�ִ�ж���2
15.
16.����ڶ�λ��
17.�����һλ��
18.ִ�ж���4������

************************************/

/*
 *��������MotorSensorJudge
 *���������߶�λ�������ж�λ��,����һ�����ظ�����
 *���룺count����ǰλ�ã��߹��ļ���ֵ
 *�������
 *���ã��ⲿ����
 ***/
void MotorSensorJudge(u8 count)
{
	static u8 coutVal=0;
	if(coutVal != count)
	{
		coutVal = count;
	}else
	{
		//�����ظ�����ִ��
		return;
	}
	switch (count)
	{
		case 1:
			Action();
			break;
		case 2:
			//������A������ʻ
		//	SetMoveMotorSpeed(130);
			break;
		case 3:
			//������ʻ
			Action3(3);
			break;
		case 4:
			//�½���ץȡ�����������������ʻ
			Action1(4);
			break;
		case 5:
			SetMoveMotorSpeed(150);
			Delay_ms(1200,0);
			Delay_ms(1200,0);
			SetMoveMotorSpeed(130);
			break;
		case 6:
		//	Delay_ms(850,0);
		//����
		//	SetMoveMotorSpeed(45);
		//	RollBackAction();
			SetMoveMotorSpeed(55);
			break;
		case 7:
			//ֹͣ���½���������Ʒ����������������
			Action2(5,6);
			break;
		case 8:
			//����
			break;
		case 9:
		//����
			Action3(7);
			break;
		case 10:		
			break;
		case 11:
			//�ظ��ź�4����
			Action1(8);
			break;
		case 12:
			//����
			SetMoveMotorSpeed(140);
			Delay_ms(1200,0);
			Delay_ms(1200,0);
			SetMoveMotorSpeed(110);
			break;
		case 13:
			break;
		case 14:
			//����
			SetMoveMotorSpeed(55);
		//	SetMoveMotorSpeed(45);
			SetPullMotorSpeed(200);
			PullMotorForward();
//			Wait(signalHeight,9);
			while(signalHeight<9 && (autodrive ==1));
			PullMotorStop();
		//������ɺ���μ���ֹͣ
			SetMoveMotorSpeed(50);
		//	RollBackAction();
				
			break;
		case 15:
			//�ظ��ź�7����
			Action2(10,11);
			break;
		case 16:
			//����
			break;
		case 17:
			break;
		case 18:
			//����
			Action3(13);
			break;
		case 19:
			break;
		case 20:
			//�ظ��ź�4����
			Action1(14);
			break;
		case 21:
			//����
			SetMoveMotorSpeed(140);
			Delay_ms(1200,0);
			Delay_ms(1200,0);
			SetMoveMotorSpeed(110);		
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			//����
			SetMoveMotorSpeed(10);
			SetPullMotorSpeed(200);
			PullMotorForward();
	//		Wait(signalHeight,16);
			while(signalHeight<16 && (autodrive ==1));
			PullMotorStop();
			SetMoveMotorSpeed(55);
		
			break;
		case 25:
			//�ظ��ź�7����
			MoveMotorStop();
			//��
			RollBackAction();
			Delay_ms(1000,0);
			PullMotorBack();
//	 	  Wait(signalHeight,17);
		  while(signalHeight<17 && (autodrive ==1));
			PullMotorStop();
			ClawOpen();
			break;
		default:
			break;
	}
}



/*
 *��������AutoDriveConfig
 *�������Զ���ʻ���ú���
 *���룺��
 *�������
 *���ã��ⲿ����
 */
void AutoDriveConfig()
{
	MotorConfig();
	ServoConfig();
	SensorConfig();
	PS2_Init();
	PS2_SetInit();
	Delay_ms(1000,0);
	Delay_ms(1000,0);
	SignalCheck();
}

/*
 *��������MotorSensorJudge
 *���������߶�λ�������ж�λ��,����һ�����ظ�����
 *���룺count����ǰλ�ã��߹��ļ���ֵ
 *�������
 *���ã��ⲿ����
 ***
 --------------------------------------------
 ���򱸷ݣ����߲��Գɹ�
 --------------------------------------------
void MotorSensorJudge(u8 count)
{
	
	switch (count)
	{
		case 1:
			SetMoveMotorSpeed(80);	
			MoveMotorBack();
			break;
		case 2:
			//������A������ʻ
			SetMoveMotorSpeed(200);
			break;
		case 3:
			//������ʻ
		  SetMoveMotorSpeed(80);
			break;
		case 4:
			//�½���ץȡ�����������������ʻ
			Action1(count);
			break;
		case 5:
			SetMoveMotorSpeed(200);
			break;
		case 6:
			SetMoveMotorSpeed(80);
			break;
		case 7:
			//ֹͣ���½���������Ʒ����������������
			Action2(count);
			break;
		case 8:
			//����
		SetMoveMotorSpeed(200);
			break;
		case 9:
			break;
		case 10:		
					//����
		SetMoveMotorSpeed(80);			
			break;
		case 11:
			//�ظ��ź�4����
			Action1(count);
			break;
		case 12:
						//����
			SetMoveMotorSpeed(200);
			break;
		case 13:
			break;
		case 14:
			//����
			SetMoveMotorSpeed(80);
			break;
		case 15:
			//�ظ��ź�7����
			Action2(count);
			break;
		case 16:
			//����
		SetMoveMotorSpeed(200);
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			//����
		SetMoveMotorSpeed(80);
			break;
		case 20:
			//�ظ��ź�4����
		Action1(count);
			break;
		case 21:
			//����
			SetMoveMotorSpeed(200);
			break;
		case 22:
			break;
		case 23:		
			break;
		case 24:
			//����
			SetMoveMotorSpeed(80);
			break;
		case 25:
			//�ظ��ź�7����
			MoveMotorStop();
			break;
		default:
			break;
	}
}
*/

/*
 *��������MotorSensorJudge
 *���������߶�λ�������ж�λ��,�����������ظ�����
 *���룺count����ǰλ�ã��߹��ļ���ֵ
 *�������
 *���ã��ⲿ����
 **
void MotorSensorJudge(u8 count)
{
	switch (count)
	{
		case 1:
			SetMoveMotorSpeed(80);	
			MoveMotorBack();
			Delay_ms(10);
			break;
		case 2:
			//������A������ʻ
			SetMoveMotorSpeed(200);
			break;
		case 3:
			//������ʻ
		  SetMoveMotorSpeed(80);
			break;
		case 4:
			//�½���ץȡ�����������������ʻ
			Action1(count);
			break;
		case 5:
			break;
		case 6:
			SetMoveMotorSpeed(200);
			break;
		case 7:
			SetMoveMotorSpeed(80);
			break;
		case 8:
			Action2(count);
			break;
		case 9:
			break;
		case 10:
			SetMoveMotorSpeed(200);
			break;
		case 11:
			SetMoveMotorSpeed(80);
			break;
		case 12:
			break;
		case 13:
			Action1(count);
			break;
		case 14:
			break;
		case 15:
			break;
		case 16:
			SetMoveMotorSpeed(200);
			break;
		case 17:
			SetMoveMotorSpeed(80);
			break;
		case 18:
			Action2(count);
			break;
		case 19:
			break;
		case 20:
			SetMoveMotorSpeed(200);
			break;
		case 21:
			SetMoveMotorSpeed(80);
			break;
		case 22:
			break;
		case 23:
			break;
		case 24:
			Action1(count);
			break;
		case 25:
			break;
		case 26:
			break;
		case 27:
			break;
		case 28:
			SetMoveMotorSpeed(200);
			break;
		case 29:
			SetMoveMotorSpeed(80);
			break;
		case 30:
			MoveMotorStop();
			break;
		default:
			break;
	}
}
*/









