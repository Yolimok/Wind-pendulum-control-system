#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include <math.h>
#include "sys.h"

typedef struct
{
  float kp;                       //����ϵ��Proportional
  float ki;                       //����ϵ��Integral
  float kd;                       //΢��ϵ��Derivative
//	float ti;                       //����ʱ�䳣��
//  float td;                       //΢��ʱ�䳣��
//	float period;										//��������
  float ek;                       //��ǰ���
  float ek1;                      //ǰһ�����e(k-1)
  float ek2;                      //��ǰһ�����e(k-2)
  float location_sum;             //�ۼƻ���λ��
	float out;											//PID���ֵ
}PID_LocTypeDef;
float PID_location(float setvalue, float actualvalue, PID_LocTypeDef *PID);
float PID_increment(float setvalue, float actualvalue, PID_LocTypeDef *PID);
#endif









