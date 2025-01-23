

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

// #include "robot.h"
// #include "ins_task.h"
// #include "motor_task.h"
// #include "referee_task.h"
#include "mpu6050.h"
#include "init.h"

osThreadId imuTaskHandle;
osThreadId gimbalTaskHandle;
osThreadId chassisTaskHandle;

void StartIMUTASK(void const *argument);
void StartGIMBALTASK(void const *argument);
void StartCHASSISTASK(void const *argument);

/**
 * @brief 初始化机器人任务,所有持续运行的任务都在这里初始化
 *
 */
void OSTaskInit()
{
    osThreadDef(imutask, StartIMUTASK, osPriorityNormal, 0, 128);
    imuTaskHandle = osThreadCreate(osThread(imutask), NULL);

    osThreadDef(gimbaltask, StartGIMBALTASK, osPriorityNormal, 0, 128);
    gimbalTaskHandle = osThreadCreate(osThread(gimbaltask), NULL);

    osThreadDef(chassistask, StartCHASSISTASK, osPriorityNormal, 0, 256);
    chassisTaskHandle = osThreadCreate(osThread(chassistask), NULL);
}

/**
 *@brief IMU任务，读取陀螺仪数据，解算姿态角，更新姿态给机器人底盘使用
 *@retval None 
 *
 */ 
__attribute__((noreturn)) void StartIMUTASK(void const *argument)
{
    for (;;)
    {
        // 1kHz
        ImuTask();
        osDelay(1);
    }
}

/**
 *@brief 底盘任务，根据IMU反馈的数据控制底盘运动
 *@retval None 
 *
 */ 
__attribute__((noreturn)) void StartCHASSISTASK(void const *argument)
{
    for (;;)
    {
        // 1kHz
        ChassisTask();
        osDelay(1);
    }
}

__attribute__((noreturn)) void StartGIMBALTASK(void const *argument)
{
    for (;;)
    {   //500Hz
        GimbalTask();
        osDelay(1000);
    }
}

