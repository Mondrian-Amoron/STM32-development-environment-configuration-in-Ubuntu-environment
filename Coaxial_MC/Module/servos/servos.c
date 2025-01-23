#include "servos.h"

void ServoInit(void)
{
    HAL_TIM_PWM_Start(&htim20, TIM_CHANNEL_1);//右
    HAL_TIM_PWM_Start(&htim20, TIM_CHANNEL_2);//中
    HAL_TIM_PWM_Start(&htim20, TIM_CHANNEL_3);//左

    ServoSetAngle(SERVO_RIGHT, 90);
    ServoSetAngle(SERVO_MIDDLE, 90);
    ServoSetAngle(SERVO_LEFT, 90);
}

void ServoSetAngle(uint8_t servo, uint16_t angle)
{
    //500~2500，0~180
    uint16_t pulse = 0;
    if (servo == SERVO_RIGHT)
    {
        pulse = 500 + angle * 11.11;
        __HAL_TIM_SET_COMPARE(&htim20, TIM_CHANNEL_1, pulse);
    }
    else if (servo == SERVO_MIDDLE)
    {
        pulse = 500 + angle * 11.11;
        __HAL_TIM_SET_COMPARE(&htim20, TIM_CHANNEL_2, pulse);
    }
    else if (servo == SERVO_LEFT)
    {
        pulse = 500 + angle * 11.11;
        __HAL_TIM_SET_COMPARE(&htim20, TIM_CHANNEL_3, pulse);
    }
}