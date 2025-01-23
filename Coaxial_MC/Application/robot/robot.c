#include "stdio.h"

#include "robot.h"
#include "robot_task.h"
#include "robot_def.h"

#include "mpu6050.h"
#include "imu.h"
#include "motor.h"
#include "encoder.h"
#include "oled.h"

float LEFT_Speed = -4000;
int cw_test;
int state_test;
int test_flag=1;

float alpha = 0.5;
float filter = 0;
float last_filter = 0;

char yawStr[20];  // 用于存储转换后的字符串

void RobotInit()
{
    MPU_Init(); //初始化MPU
    EncoderInit(); //初始化编码器
    MotorInit(); //初始化电机
    OSTaskInit(); //初始化任务

    OLED_Init();
	OLED_CLS();
}

void ImuTask()
{
    MpuGetData(); //获取MPU数据
	GetAngle(&MPU6050,&Angle,0.001f); //获取并解算角度，包括滤波
}

void ChassisTask()
{
    cw_test = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
    state_test = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
    /*读取电机的编码值，用于后续转速计算*/
    leftMotor.encoder = EncoderRead(MOTOR_LEFT); //读取左电机编码器数据
    leftMidMotor.encoder = EncoderRead(MOTOR_LEFT_MID); //读取左中电机编码器数据
    rightMidMotor.encoder = EncoderRead(MOTOR_RIGHT_MID); //读取右中电机编码器数据
    rightMotor.encoder = EncoderRead(MOTOR_RIGHT); //读取右电机编码器数据

    if(leftMotor.encoder > 2500) leftMotor.encoder -= 5000;
    if(leftMidMotor.encoder > 2500) leftMidMotor.encoder -= 5000;
    if(rightMidMotor.encoder > 2500) rightMidMotor.encoder -= 5000;
    if(rightMotor.encoder > 2500) rightMotor.encoder -= 5000;

    __HAL_TIM_SET_COUNTER(&htim1,0);
    __HAL_TIM_SET_COUNTER(&htim2,0);
    __HAL_TIM_SET_COUNTER(&htim3,0);
    __HAL_TIM_SET_COUNTER(&htim4,0);

    /*计算电机的角速度  为保证控制精度，末尾除以20，最后可控范围为0~270*/
    leftMotor.angleSpeed = leftMotor.encoder * 1000 / 400 * 60; //计算左电机角速度
    leftMidMotor.angleSpeed = leftMidMotor.encoder * 1000 / 400 * 60; //计算左中电机角速度
    rightMidMotor.angleSpeed = rightMidMotor.encoder * 1000 / 400 * 60; //计算右中电机角速度
    rightMotor.angleSpeed = rightMotor.encoder * 1000 / 400 * 60; //计算右电机角速度

    // leftMotor.angleSpeed = leftMotor.encoder; //计算左电机角速度
    // leftMidMotor.angleSpeed = leftMidMotor.encoder; //计算左中电机角速度
    // rightMidMotor.angleSpeed = rightMidMotor.encoder; //计算右中电机角速度
    // rightMotor.angleSpeed = rightMotor.encoder; //计算右电机角速度

    leftMotor.angleSpeed = alpha * leftMotor.angleSpeed + (1 - alpha) * last_filter;
    last_filter = leftMotor.angleSpeed;

    leftMotor.speedPID.output = pidCalculate(&leftMotor.speedPID, LEFT_Speed, leftMotor.angleSpeed); //计算左电机的PWM值
    if(leftMotor.speedPID.output < -1) 
    {
        leftMotor.Pwm = (int16_t)(4999 + leftMotor.speedPID.output);
        
        //MotorStop(MOTOR_LEFT);
        MotorRun(MOTOR_LEFT);
        MotorControlCwCCw(MOTOR_LEFT, MOTOR_CCW);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, leftMotor.Pwm);
        
    }
    else if(leftMotor.speedPID.output > 1)
    {
        leftMotor.Pwm = (int16_t)(4999 - leftMotor.speedPID.output);
        
        //MotorStop(MOTOR_LEFT);
        MotorRun(MOTOR_LEFT);
        MotorControlCwCCw(MOTOR_LEFT, MOTOR_CW);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, leftMotor.Pwm);
        
    }
    else
    {
        leftMotor.Pwm = 4999;
        MotorStop(MOTOR_LEFT);
        MotorControlCwCCw(MOTOR_LEFT, MOTOR_CW);
        __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, leftMotor.Pwm);
    }
    
    //测试用

    // MotorRun(MOTOR_LEFT);
    // MotorControlCwCCw(MOTOR_LEFT, MOTOR_CCW);
    // __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 4999);


    //LEFT_Speed = Angle.roll * 300;
}

void GimbalTask()
{

}