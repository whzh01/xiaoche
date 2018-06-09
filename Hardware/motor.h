#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
 extern "C" {
#endif

#define DEV 35

/* Includes ------------------------------------------------------------------*/
#include "userconfig.h"
	
void MotorConfig(void);	 
void MoveMotorForward(void); 
void MoveMotorBack(void);
void MoveMotorStop(void);
void PullMotorForward(void);
void PullMotorBack(void);
void PullMotorStop(void);
void RollMotorAForward(void);
void RollMotorABack(void);
void RollMotorAStop(void);
void RollMotorBForward(void);
void RollMotorBBack(void);
void RollMotorBStop(void);
void SetPullMotorSpeed(u16 speed);
void SetMoveMotorSpeed(u16 speed);
void SetRollMotorSpeed(u16 speed);
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 



