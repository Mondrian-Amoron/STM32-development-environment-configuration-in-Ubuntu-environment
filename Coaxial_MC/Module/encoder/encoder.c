#include "encoder.h"
#include "stdint.h"
#include "robot_def.h"

void EncoderInit(void)
{
    //开启电机1的编码器通道
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_2);
    
    //开启电机2的编码器通道
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);

    //开启电机3的编码器通道
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_2);

    //开启电机4的编码器通道
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_2);
}

short EncoderRead(uint8_t encoder)
{
    switch(encoder)
    {
        case MOTOR_LEFT_MID:
            return (short)__HAL_TIM_GET_COUNTER(&htim1);
        case MOTOR_RIGHT_MID:
            return (short)__HAL_TIM_GET_COUNTER(&htim2);
        case MOTOR_RIGHT:
            return (short)__HAL_TIM_GET_COUNTER(&htim3);
        case MOTOR_LEFT:
            return (short)__HAL_TIM_GET_COUNTER(&htim4);
        default: return 0;
    }
}