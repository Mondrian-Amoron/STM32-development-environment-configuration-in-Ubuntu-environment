#include "motor.h"
#include "robot_def.h"

motoInformation leftMotor;
motoInformation leftMidMotor;
motoInformation rightMidMotor;
motoInformation rightMotor;

/**
 *@brief 底盘电机初始化，启用各个接口以及设置默认状态为停止
 *@param None 
 *@retval None 
 */
void MotorInit(void)
{
    /**
     * 电机启停控制，初始化时，将四个电机都设置为停止状态
     * 更新电机结构体的启动状态为停止
     */
    MotorStop(MOTOR_LEFT);
    MotorStop(MOTOR_LEFT_MID);
    MotorStop(MOTOR_RIGHT);
    MotorStop(MOTOR_LEFT);

    leftMotor.state = MOTOR_STOP;
    leftMidMotor.state = MOTOR_STOP;
    rightMidMotor.state = MOTOR_STOP;
    rightMotor.state = MOTOR_STOP;

    /**
     *按照从左往右的顺序来数（从开关方向看去）
     *不用保证四个电机的方向一致，通过电机速度的正负来判断方向
     */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);// CW_CCW4 电机4方向控制位
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);// CW_CCW1 电机1方向控制位 
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);// CW_CCW2 电机2方向控制位
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);// CW_CCW3 电机3方向控制位

    /**
     * 电机PID参数初始化
     * 速度环
     * 角度环（直立环）
     */
    pidInit(&leftMotor.speedPID, 2, 0.001, 1, 500, 4999);
    pidInit(&leftMotor.anglePID, 0.5, 0, 0, 1000, 9999);

    pidInit(&leftMidMotor.speedPID, 0.5, 0, 0, 1000, 0);
    pidInit(&leftMidMotor.anglePID, 0.5, 0, 0, 1000, 0);

    pidInit(&rightMidMotor.anglePID, 0.5, 0, 0, 1000, 0);
    pidInit(&rightMidMotor.speedPID, 0.5, 0, 0, 1000, 0);

    pidInit(&rightMotor.speedPID, 0.5, 0, 0, 1000, 0);
    pidInit(&rightMotor.anglePID, 0.5, 0, 0, 1000, 0);
    
    /**
     *电机启动
     *开启PWM的通道，并在默认情况下无输出
     */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);// 电机1
    HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);// 电机2
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);// 电机3
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);// 电机4
}

/**
 *@brief 控制电机停止，在正反转切换时，务必先停止电机
 *@param motor 指定需要控制的目标电机，取值范围为 MOTOR_LEFT_MID、MOTOR_RIGHT_MID、MOTOR_LEFT、MOTOR_RIGHT 四种，对应于底盘的四个电机
 *@retval None 
 */
void MotorStop(uint8_t motor)
{
    switch(motor)
    {
        case MOTOR_LEFT_MID:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);// BRK1 电机1启动控制位
        case MOTOR_RIGHT_MID:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);// BRK2 电机2启动控制位
        case MOTOR_RIGHT:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);// BRK3 电机3启动控制位
        case MOTOR_LEFT:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);// BRK4 电机4启动控制位
    }
}

/**
 *@brief 控制电机启动
 *@param motor 指定需要控制的目标电机，取值范围为 MOTOR_LEFT_MID、MOTOR_RIGHT_MID、MOTOR_LEFT、MOTOR_RIGHT 四种，对应于底盘的四个电机
 *@retval None 
 */
void MotorRun(uint8_t motor)
{
    switch(motor)
    {
        case MOTOR_LEFT_MID:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
        case MOTOR_RIGHT_MID:
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
        case MOTOR_RIGHT:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
        case MOTOR_LEFT:
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
    }
}

/**
 *@brief 控制电机正反转
 *@param motor 指定需要控制的目标电机，取值范围为 MOTOR_LEFT_MID、MOTOR_RIGHT_MID、MOTOR_LEFT、MOTOR_RIGHT 四种，对应于底盘的四个电机
 *@param cwccw 指定电机转动方向，取值范围为 MOTOR_CW（顺时针）或 MOTOR_CCW（逆时针）
 *@retval None 
 */
void MotorControlCwCCw(uint8_t motor,uint8_t cwccw)
{
    switch(motor)
    {
        case MOTOR_LEFT_MID:
            {
                if(cwccw == MOTOR_CW)
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
                }
            }break;
        case MOTOR_RIGHT_MID:
            {
                if(cwccw == MOTOR_CW)
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
                }
            }break;
        case MOTOR_RIGHT:
            {
                if(cwccw == MOTOR_CW)
                {
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
                }
            }break;
        case MOTOR_LEFT:
            {
                if(cwccw == MOTOR_CW)
                {
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
                }
                else
                {
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
                }
            }break;
    }
}