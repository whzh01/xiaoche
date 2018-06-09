#include "sensor.h"

u8 filter(u8);


void SensorConfig()
{
	GPIO_InitTypeDef 	GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SENSORIN1 | SENSORIN2 |SENSORIN3 |SENSORIN4 |SENSORIN5 |SENSORIN6;
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IN_FLOATING;
	GPIO_Init(SENSORIO,&GPIO_InitStructure);
	
}
/***************************************************
		��ȡ��������ֵ
		��ȡʱ����С��10ms
***************************************************/
u8 GetSensorVal1()
{
	                          
	return filter(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
}
u8 GetSensorVal2()
{
	return filter(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));
}

void SensorTest()
{
	u16 num;
	
	USART_SendData(TESTUSART, GetSensorVal1());
	for(num=0;num<3000 && USART_GetFlagStatus(TESTUSART,USART_FLAG_TC) != SET;num++);
	USART_SendData(TESTUSART,GetSensorVal2());
	for(num=0;num<3000 && USART_GetFlagStatus(TESTUSART,USART_FLAG_TC) != SET;num++);
}
/****************************************
	����ƽ���˲��㷨
	����ֵ1�ظ�����<5.���0����֮���1
	
****************************************/
u8 filter(u8 val)
{
	const u8 N=9;
	static u8 valArr[N+1]={2};
	static u8 nCount=0;
	u8 count=0,value=0;
	
	
	if(2 == valArr[N])
	{
		for(count=0;count<N;count++)
		{
			valArr[count]=val;
		}
	}else
	{
		if(N+1==nCount) nCount=0;
		valArr[nCount++] = val;
		for(count=0;count<N;count++)
		{
			value+= valArr[count];
		}
		if(value%(N+1)<5)
			return 0;
		else 
			return 1;
	}
	return val;
}

