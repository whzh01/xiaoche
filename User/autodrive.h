/**************************************************************
	autodrive.h 
	起重小车自动运行配置及控制文件

*************************************************************/
#ifndef __AUTODRIVE_H
#define __AUTODRIVE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "userconfig.h"

void AutoDriveConfig(void);	 
void MotorSensorJudge(u8 count);
void MotorSensorCount(void);
void PullSensorJudge(u8 count);
void PullSensorCount(void);
void EmStop(void);
void SignalCheck(void);

	 
void TIM2_IRQHandler(void);	 
	 
	 
	 
	 
	 	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 

