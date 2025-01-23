#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"
#include "tim.h"
#include "gpio.h"

void EncoderInit(void);
short EncoderRead(uint8_t encoder);
#endif