#ifndef ROBOT_H
#define ROBOT_H

#include "motor.h"

extern motoInformation leftMotor;
extern motoInformation leftMidMotor;
extern motoInformation rightMidMotor;
extern motoInformation rightMotor;

/**
 * @brief 机器人初始化,在开启rtos之前调用
 * 
 */
void RobotInit();

/**
 * @brief 机器人各模块执行任务,在开启rtos之后调用
 */
void ImuTask();
void ChassisTask();
void GimbalTask();

#endif