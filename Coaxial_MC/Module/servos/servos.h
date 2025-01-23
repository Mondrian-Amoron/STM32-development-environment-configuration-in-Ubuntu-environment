#ifndef SERVOS_H
#define SERVOS_H

#include "main.h"
#include "tim.h"

#define SERVO_RIGHT  1
#define SERVO_MIDDLE 2
#define SERVO_LEFT   3


void ServoInit(void);
void ServoSetAngle(uint8_t servo, uint16_t angle);

#endif