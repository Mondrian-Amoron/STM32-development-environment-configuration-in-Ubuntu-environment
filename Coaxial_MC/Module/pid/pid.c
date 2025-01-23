#include "pid.h"

void pidInit(MotorPID *pid,float kp,float ki,float kd,float i_max,float out_max)
{
  pid->kp      = kp;
  pid->ki      = ki;
  pid->kd      = kd;
  pid->i_max   = i_max;
  pid->out_max = out_max;
}


float pidCalculate(MotorPID *pid, float target, float actual)
{
  pid->target = target;
  pid->actual = actual;
  pid->err[1] = pid->err[0];
  pid->err[0] = pid->target - pid->actual;

  pid->p_out  = pid->kp * pid->err[0];
  pid->i_out += pid->ki * pid->err[0];
  pid->d_out  = pid->kd * (pid->err[0] - pid->err[1]);
  pid->i_out=LIMIT_MIN_MAX(pid->i_out, -pid->i_max, pid->i_max);

  pid->output = pid->p_out + pid->i_out + pid->d_out;
  pid->output=LIMIT_MIN_MAX(pid->output, -pid->out_max, pid->out_max);
  return pid->output;
}

float LIMIT_MIN_MAX(float in,float min,float max)
{
	if(in<=min)
	{
		in=min;
	}
	else if(in>=max)
	{
		in=max;
	}
	return in;
}