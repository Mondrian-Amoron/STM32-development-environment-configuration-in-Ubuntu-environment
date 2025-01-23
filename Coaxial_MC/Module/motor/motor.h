#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include "tim.h"
#include "gpio.h"

#include "pid.h"

typedef struct motoInformation
{
    //电机信息
    float angleSpeed; //电机角速度
    int encoder; //电机编码器值
    int angle; //电机此时角度，从编码器值反馈而来
    float nowSpeed; //电机此时转速
    float targetSpeed; //电机目标转速
    uint8_t state; //电机运行状态
    //电机控制
    uint16_t Pwm; //控制电机的占空比
    MotorPID speedPID; //电机速度环PID
    MotorPID anglePID; //电机角度环PID

}motoInformation;

void MotorInit(void);
void CalculateSpeed(short num);
void MotorControlCwCCw(uint8_t motor,uint8_t cwccw);
void MotorStop(uint8_t motor);
void MotorRun(uint8_t motor);
void MotorSetPWM(int16_t pwm);

#endif