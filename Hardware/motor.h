#ifndef __MOTOR_H
#define __MOTOR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "userconfig.h"
	 
void MotorConfig(void);	 
void MoveMotorForward(void); 
void MoveMotorBack(void);
void MoveMotorStop(void);
void PullMotorForward(void);
void PullMotorBack(void);
void PullMotorStop(void);
void SetPullMotorSpeed(u16 speed);
void SetMoveMotorSpeed(u16 speed);
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif 



