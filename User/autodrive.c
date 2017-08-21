/*Include----------------------------------------------*/
#include "autodrive.h"
/*Define  ---------------------------------------------*/
static u8 signalCount1=0,signalCount2=0;
vu8 keyBit=0;


void SignalCheck()
{
	TIM_TimeBaseInitTypeDef				TIM_InitStructure;
	
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 1000;
	TIM_InitStructure.TIM_Prescaler = 72-1;					 /*****¶¨Ê±***********************/
	TIM_TimeBaseInit(SIGNALTIM,&TIM_InitStructure);
	TIM_ITConfig(SIGNALTIM,TIM_IT_Update,ENABLE);
	TIM_Cmd(SIGNALTIM,ENABLE);
}
/*********************************
 The following are interrupt handler functions; 
*********************************/
void TIM2_IRQHandler()
{
	static vu8 nkey=0;
	if(TIM_GetITStatus(SIGNALTIM,TIM_IT_Update))
	{
		TIM_ClearITPendingBit(SIGNALTIM,TIM_IT_Update);
		if(50==nkey)
		{
			nkey=0;
			keyBit=1;
		
		}else
		{
			if(0==keyBit)
				nkey++;
		}
	}
}

void MotorSensorJudge(u8 count)
{
	switch (count)
	{
		case 2:
			
			break;
		case 4:
			break;
		default:
			break;
	}
}

void MotorSensorCount()
{
	static u8 motorSensorCount=0;
	motorSensorCount++;
}
void PullSensorJudge(u8 count)
{
	switch (count)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}
void PullSensorCount()
{
	static u8 pullSensorCount=0;
}
void Action()
{
	

	SetMoveMotorSpeed(1800);
	MoveMotorForward();
	Delay_ms(500);
//		Delay_ms(1100);
//		Delay_ms(1100);
//		MoveMotorStop();
//		Delay_ms(1100);
//		Delay_ms(1100);
//		speed=1500;
//		SetMoveMotorSpeed(speed);
//		MoveMotorBack();
//		Delay_ms(1100);
//		Delay_ms(1100);
//		Delay_ms(1100);
//		SetMoveMotorSpeed(0);
//		Delay_ms(1100);
//		Delay_ms(1100);
}
void Action1()
{
	SetMoveMotorSpeed(0);
	Delay_ms(50);
	MoveMotorStop();
	SetPullMotorSpeed(1800);
	PullMotorBack();
	ClawOpen();
	Delay_ms(1000);
	PullMotorStop();
	ClawClose();
	Delay_ms(1000);
	Delay_ms(500);
	SetPullMotorSpeed(500);
	PullMotorForward();
	Delay_ms(1000);
	SetPullMotorSpeed(1500);
	Delay_ms(1000);
}

void Action3()
{
	
}
void AutoDriveConfig()
{
	MotorConfig();
	ServoConfig();
	SensorConfig();
	PS2_Init();
	Delay_ms(1100);
	PS2_SetInit();
	SignalCheck();
}













