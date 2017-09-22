/********************************************************
红外传感器说明：
	检测输出值：
		白色：0
		黑色：1（检测到）
		
*********************************************************/
/**头文件包含----------------------------------------------*/
#include "autodrive.h"
/*常量定义  ---------------------------------------------*/
u8 signalMove=0,signalHeight=0;//存储行走传感器和高度传感器感应次数
u8 validMove=1;   //行走传感器信号有效状态位，保证同一个位置只计数一次
u8 validHeight=0;	//高度传感器信号有效状态位，保证同一个位置只计数一次
u8 keyBit=0;			//定时读取遥控器信号状态位
u8 keyVal;      //存储当前遥控信号值
/**内部函数声明-----------------------------------------------------*/


/*
 *函数名：SignalCheck
 *描述：信号检测配置函数
 *输入：无
 *输出：无
 *调用：外部调用
 */
void SignalCheck()
{
	TIM_TimeBaseInitTypeDef				TIM_InitStructure;
	
	TIM_InitStructure.TIM_ClockDivision=0;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Period = 100-1;
	TIM_InitStructure.TIM_Prescaler = 36-1;					 /*****定时100us***********************/
	TIM_TimeBaseInit(SIGNALTIM,&TIM_InitStructure);
	TIM_ITConfig(SIGNALTIM,TIM_IT_Update,ENABLE);
	TIM_Cmd(SIGNALTIM,ENABLE);
}
/*
 *函数名：TIM2_IRQHandler
 *描述：TIM2定时中断，用于检测传感器信号
 *输入：无
 *输出：无
 *调用：外部调用
 */
void TIM2_IRQHandler()
{
	static vu8 nkey0=0,nkey1=0;
	static vu8 nkey3=0,nkey4=0;
	static u16 npsc=0;//手柄读取状态位，每2ms读取一次。
	
	if(TIM_GetITStatus(SIGNALTIM,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(SIGNALTIM,TIM_IT_Update);
		if(500 ==npsc)
		{
			npsc=0;
			keyBit=1;		//定时信号，用于主程序中定时读取遥控器信号
			keyVal = PS2_DataKey();	 //手柄按键捕获处理
			if(PSB_L2 == keyVal)
			{		
				PullMotorStop();
				MoveMotorStop();
				RollMotorStop();
			}
		}else
		{
			npsc++;
		}
		//判断行走位置传感器信号
		if(30==nkey1)
		{
			//1信号有效
			nkey0=0;
			nkey1=0;
			validMove =1;
		}else if(30==nkey0 && validMove==1)
		{
			//0信号有效
			validMove=0;  //置1信号无效
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
		//判断高度传感器信号
		if(30 == nkey4)
		{
			//1信号有效
			nkey3=0;
			nkey4=0;
			validHeight =1;
		}else if(30 == nkey3 && validHeight==1)
		{
					//1信号有效
			validHeight=0;  //置1信号无效
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
 *函数名：Action
 *描述：行走位置事件触发动作
 *输入：无
 *输出：无
 *调用：外部调用
 */

void Action()
{
	//起始动作
		SetMoveMotorSpeed(200);
		MoveMotorBack();
		ClawOpen();
		PullMotorForward();
		while(signalHeight <2);
		PullMotorStop();
}
/*
 *函数名：Action1
 *描述：行走位置事件触发动作1
 *输入：无
 *输出：无
 *调用：外部调用
 */
void Action1(u8 height)
{
	//重复信号4点动作，高度信号不同
	//停，闭，上2，匀->B，
		MoveMotorStop();
		PullMotorBack();
	  while(signalHeight<height-1);
	  PullMotorStop();
		ClawClose();
		PullMotorForward();
		while(signalHeight<height);
		PullMotorStop();
		SetMoveMotorSpeed(90);
		MoveMotorForward();
}
/*
 *函数名：Action2
 *描述：行走位置事件触发动作2
 *输入：无
 *输出：无
 *调用：外部调用
 */
void Action2(u8 h1,u8 h2)    
{
	//停，绕，下，开，上，匀，回
		SetPullMotorSpeed(80);
		SetRollMotorSpeed(130);
		MoveMotorStop();
		RollMotorBack();
		while(GPIO_ReadInputDataBit(SENSORIO,SENSORIN3));
		RollMotorStop();
		Delay_ms(1000,0);
	/**重新修正位置**/
		RollMotorForward();
		while(GPIO_ReadInputDataBit(SENSORIO,SENSORIN3));
		RollMotorStop();
		Delay_ms(1000,0);
		Delay_ms(1000,0);
		Delay_ms(1000,0);
		PullMotorBack();
		while(signalHeight <h1);
		PullMotorStop();
		ClawOpen();
		SetPullMotorSpeed(80);
		PullMotorForward();
		Delay_ms(1000,0);
		SetPullMotorSpeed(200);
		while(signalHeight<h2);
		PullMotorStop();
		SetMoveMotorSpeed(150);
		SetRollMotorSpeed(150);
	  MoveMotorBack();
		RollMotorForward();
		while(GPIO_ReadInputDataBit(SENSORIO,SENSORIN4));
		RollMotorStop();
}
void Action3(u8 h)
{
	//减速，下1
	SetMoveMotorSpeed(60);
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
1.无动作
2.下降抓取箱子并提升，反向行驶
3.无动作
4.到达指定位置，下落箱子
5.
6.到达第一位置
7.到达第二位置，执行动作2
8.
9.到达第一位置
10.执行动作4
11.
12.到达第一位置
13.到达第二位置
14.到达第三位置，执行动作2
15.
16.到达第二位置
17.到达第一位置
18.执行动作4，结束

************************************/

/*
 *函数名：MotorSensorJudge
 *描述：行走定位传感器判断位置,方案一，无重复过点
 *输入：count：当前位置，走过的计数值
 *输出：无
 *调用：外部调用
 ***/
void MotorSensorJudge(u8 count)
{
	static u8 coutVal=0;
	if(coutVal != count)
	{
		coutVal = count;
	}else
	{
		//动作重复，不执行
		return;
	}
	switch (count)
	{
		case 1:
			Action();
			break;
		case 2:
			//加速向A方向行驶
		//	SetMoveMotorSpeed(200);
			break;
		case 3:
			//减速行驶
			Action3(3);
			break;
		case 4:
			//下降，抓取，提升，反向低速行驶
			Action1(4);
			break;
		case 5:
			SetMoveMotorSpeed(200);
			break;
		case 6:
			Delay_ms(850,0);
			SetMoveMotorSpeed(60);
			break;
		case 7:
			//停止，下降，放下物品，提升，反向行走
			Action2(5,6);
			break;
		case 8:
			//加速
		SetMoveMotorSpeed(200);
			break;
		case 9:
			break;
		case 10:		
					//减速
			Action3(7);
			break;
		case 11:
			//重复信号4动作
			Action1(8);
			break;
		case 12:
						//加速
			SetMoveMotorSpeed(200);
			break;
		case 13:
			break;
		case 14:
			//减速
			SetMoveMotorSpeed(10);
			SetPullMotorSpeed(200);
			PullMotorForward();
			while(signalHeight<9);
			PullMotorStop();
			SetMoveMotorSpeed(60);
			break;
		case 15:
			//重复信号7动作
			Action2(10,11);
			break;
		case 16:
			//加速
		SetMoveMotorSpeed(200);
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			//减速
			Action3(13);
			break;
		case 20:
			//重复信号4动作
		Action1(14);
			break;
		case 21:
			//加速
			SetMoveMotorSpeed(200);
			break;
		case 22:
			break;
		case 23:	
			break;
		case 24:
			//减速
			SetMoveMotorSpeed(0);
			SetPullMotorSpeed(200);
			PullMotorForward();
			while(signalHeight<16);
			PullMotorStop();
			SetMoveMotorSpeed(90);
			break;
		case 25:
			//重复信号7动作
			MoveMotorStop();
			//绕
			RollMotorBack();
			while(GPIO_ReadInputDataBit(SENSORIO,SENSORIN3));
			RollMotorStop();
			Delay_ms(1000,0);
			Delay_ms(1000,0);
			Delay_ms(1000,0);
			PullMotorBack();
			while(signalHeight<17);
			PullMotorStop();
			ClawOpen();
			break;
		default:
			break;
	}
}



/*
 *函数名：AutoDriveConfig
 *描述：自动行驶配置函数
 *输入：无
 *输出：无
 *调用：外部调用
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
 *函数名：MotorSensorJudge
 *描述：行走定位传感器判断位置,方案一，无重复过点
 *输入：count：当前位置，走过的计数值
 *输出：无
 *调用：外部调用
 ***
 --------------------------------------------
 程序备份，行走测试成功
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
			//加速向A方向行驶
			SetMoveMotorSpeed(200);
			break;
		case 3:
			//减速行驶
		  SetMoveMotorSpeed(80);
			break;
		case 4:
			//下降，抓取，提升，反向低速行驶
			Action1(count);
			break;
		case 5:
			SetMoveMotorSpeed(200);
			break;
		case 6:
			SetMoveMotorSpeed(80);
			break;
		case 7:
			//停止，下降，放下物品，提升，反向行走
			Action2(count);
			break;
		case 8:
			//加速
		SetMoveMotorSpeed(200);
			break;
		case 9:
			break;
		case 10:		
					//减速
		SetMoveMotorSpeed(80);			
			break;
		case 11:
			//重复信号4动作
			Action1(count);
			break;
		case 12:
						//加速
			SetMoveMotorSpeed(200);
			break;
		case 13:
			break;
		case 14:
			//减速
			SetMoveMotorSpeed(80);
			break;
		case 15:
			//重复信号7动作
			Action2(count);
			break;
		case 16:
			//加速
		SetMoveMotorSpeed(200);
			break;
		case 17:
			break;
		case 18:
			break;
		case 19:
			//减速
		SetMoveMotorSpeed(80);
			break;
		case 20:
			//重复信号4动作
		Action1(count);
			break;
		case 21:
			//加速
			SetMoveMotorSpeed(200);
			break;
		case 22:
			break;
		case 23:		
			break;
		case 24:
			//减速
			SetMoveMotorSpeed(80);
			break;
		case 25:
			//重复信号7动作
			MoveMotorStop();
			break;
		default:
			break;
	}
}
*/

/*
 *函数名：MotorSensorJudge
 *描述：行走定位传感器判断位置,方案二，有重复过点
 *输入：count：当前位置，走过的计数值
 *输出：无
 *调用：外部调用
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
			//加速向A方向行驶
			SetMoveMotorSpeed(200);
			break;
		case 3:
			//减速行驶
		  SetMoveMotorSpeed(80);
			break;
		case 4:
			//下降，抓取，提升，反向低速行驶
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









