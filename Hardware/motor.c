/*Include----------------------------------------------*/
#include "motor.h"
/*Define  ---------------------------------------------*/
#define MOTORPERIOD		200-1
#define MOTORPRE			72-1
#define MOTORDUTY1		0
#define MOTORDUTY2    0
#define MOTORDUTY3    0


void MoveMotorForward()
{
	GPIO_SetBits(MOTORIO,MOTORIN1);
	GPIO_ResetBits(MOTORIO,MOTORIN2);
	Delay_ms(10);
}
void MoveMotorBack()
{
	GPIO_ResetBits(MOTORIO,MOTORIN1);
	GPIO_SetBits(MOTORIO,MOTORIN2);

}
void MoveMotorStop()
{
	GPIO_ResetBits(MOTORIO,MOTORIN1);
	GPIO_ResetBits(MOTORIO,MOTORIN2);
	Delay_ms(10);
}
void PullMotorForward()
{
	GPIO_SetBits(MOTORIO,MOTORIN3);
	GPIO_ResetBits(MOTORIO,MOTORIN4);
	Delay_ms(10);
}
void PullMotorBack()
{
	GPIO_ResetBits(MOTORIO,MOTORIN3);
	GPIO_SetBits(MOTORIO,MOTORIN4);
	Delay_ms(10);
}
void PullMotorStop()
{
	GPIO_ResetBits(MOTORIO,MOTORIN3);
	GPIO_ResetBits(MOTORIO,MOTORIN4);
}
void RollMotorForward()
{
	GPIO_SetBits(MOTORIO,MOTORIN5);
	GPIO_ResetBits(MOTORIO,MOTORIN6);
	Delay_ms(10);
}
void RollMotorBack()
{
	GPIO_ResetBits(MOTORIO,MOTORIN5);
	GPIO_SetBits(MOTORIO,MOTORIN6);
	Delay_ms(10);
}
void RollMotorStop()
{
	GPIO_ResetBits(MOTORIO,MOTORIN5);
	GPIO_ResetBits(MOTORIO,MOTORIN6);
}
void SetPullMotorSpeed(u16 speed)
{
	TIMMOTOR->CCR2=speed;
}
void SetMoveMotorSpeed(u16 speed)
{
	TIMMOTOR->CCR1=speed;
}
void SetRollMotorSpeed(u16 speed)
{
	TIMMOTOR->CCR3=speed;
}

void MotorConfig()
{
	
	TIM_TimeBaseInitTypeDef			TIM_InitStructure;
	TIM_OCInitTypeDef						TIM_OCInitStructure;
	GPIO_InitTypeDef						GPIO_InitStructure;
	/***************定时器IO口初始化****************************/
	GPIO_InitStructure.GPIO_Pin = PWMTIMIO1|PWMTIMIO2|PWMTIMIO3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWMTIMIO,&GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	/***************电机正反转输出IO初始化**************************/
	GPIO_InitStructure.GPIO_Pin = MOTORIN1 |MOTORIN2 |MOTORIN3 |MOTORIN4 |MOTORIN5 |MOTORIN6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTORIO,&GPIO_InitStructure);
	
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = MOTORPERIOD;
	TIM_InitStructure.TIM_Prescaler = MOTORPRE;
	TIM_TimeBaseInit(TIMMOTOR,&TIM_InitStructure);
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = MOTORDUTY1;
	TIM_OC1Init(TIMMOTOR,&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = MOTORDUTY2;
	TIM_OC2Init(TIMMOTOR,&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_Pulse = MOTORDUTY3;
	TIM_OC3Init(TIMMOTOR,&TIM_OCInitStructure);
	TIM_Cmd(TIMMOTOR,ENABLE);
	
	MoveMotorStop();
	PullMotorStop();
	RollMotorStop();
}


