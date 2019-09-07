#include "stm32f10x.h"
#include <math.h>
#include "sys.h"
#include "pid.h"
#define PID_LIMIT_MIN -10000		//PID������ֵ
#define PID_LIMIT_MAX 10000	//PID������ֵ
//ע�⣺PID�ṹ����붨��Ϊȫ�ֱ�����̬������Ȼ���ں����и�KP,KI,KD��ֵ
/************************��������δ֪�Ҳ���************************************/
//λ��ʽPID
//pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
//setvalue : ����ֵ������ֵ��
//actualvalue: ʵ��ֵ
//����ȫ�������ÿ����������ȥ״̬�йأ�����ʱҪ��ek�ۼӣ���������
float PID_location(float setvalue, float actualvalue, PID_LocTypeDef *PID)
{ 
	PID->ek =setvalue-actualvalue;
	PID->location_sum += PID->ek;                         //�����ۼ����ֵ
	if((PID->ki!=0)&&(PID->location_sum>(PID_LIMIT_MAX/PID->ki))) PID->location_sum=PID_LIMIT_MAX/PID->ki;
	if((PID->ki!=0)&&(PID->location_sum<(PID_LIMIT_MIN/PID->ki))) PID->location_sum=PID_LIMIT_MIN/PID->ki;//�����޷�
	
  PID->out=PID->kp*PID->ek+(PID->ki*PID->location_sum)+PID->kd*(PID->ek-PID->ek1);
  PID->ek1 = PID->ek;  
	if(PID->out<PID_LIMIT_MIN)	PID->out=PID_LIMIT_MIN;
	if(PID->out>PID_LIMIT_MAX)	PID->out=PID_LIMIT_MAX;//PID->out�޷�
	
	return PID->out;
}
//����ʽPID
//pidout+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
//setvalue : ����ֵ������ֵ��
//actualvalue: ʵ��ֵ
float PID_increment(float setvalue, float actualvalue, PID_LocTypeDef *PID)
{                                
	PID->ek =setvalue-actualvalue;
  PID->out+=PID->kp*(PID->ek-PID->ek1)+PID->ki*PID->ek+PID->kd*(PID->ek-2*PID->ek1+PID->ek2);
//	PID->out+=PID->kp*PID->ek-PID->ki*PID->ek1+PID->kd*PID->ek2;
  PID->ek2 = PID->ek1;
  PID->ek1 = PID->ek;  
		
	if(PID->out<PID_LIMIT_MIN)	PID->out=PID_LIMIT_MIN;
	if(PID->out>PID_LIMIT_MAX)	PID->out=PID_LIMIT_MAX;//�޷�
	
	return PID->out;
}










