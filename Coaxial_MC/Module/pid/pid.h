#ifndef __PID_H
#define __PID_H

typedef struct PID
{
	float kp;           //比例
	float ki;           //积分
	float kd;           //微分
	float i_max;        //积分限幅
	float out_max;      //输出限幅

	float target;       //目标值
	float actual;       //实际值

	float err[2];          //误差

	float p_out;        //比例输出
	float i_out;        //积分输出
	float d_out;        //微分输出

	float output;          //输出
	float last_output;      //上一次输出
}MotorPID;

void pidInit(MotorPID *pid,
              float kp,
              float ki,
              float kd,
              float i_max,
              float out_max);

float pidCalculate(MotorPID *pid, float ref, float fdb);
float LIMIT_MIN_MAX(float in,float min,float max);

#endif