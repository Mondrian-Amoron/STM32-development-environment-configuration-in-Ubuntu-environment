#ifndef __ALLDATA_H
#define __ALLDATA_H

typedef   signed          char my_int8_t;
typedef   signed short     int my_int16_t;
typedef   signed           int my_int32_t;
typedef   signed       long long my_int64_t;

/* exact-width unsigned integer types */
typedef unsigned          char my_uint8_t;
typedef unsigned short     int my_uint16_t;
typedef unsigned           int my_uint32_t;
typedef unsigned       long long my_uint64_t;

//#define NULL 0
extern volatile my_uint32_t SysTick_count;

typedef struct{
	my_int16_t accX;
	my_int16_t accY;
	my_int16_t accZ;
	my_int16_t gyroX;
	my_int16_t gyroY;
	my_int16_t gyroZ;
}_st_Mpu;

typedef struct{
	float roll;
	float pitch;
	float yaw;
}_st_AngE;

typedef struct
{
	my_uint16_t roll;
	my_uint16_t pitch;
	my_uint16_t thr;
	my_uint16_t yaw;
	my_uint16_t AUX1;
	my_uint16_t AUX2;
	my_uint16_t AUX3;
	my_uint16_t AUX4;	
}_st_Remote;

typedef volatile struct
{
	float desired;     			//< set point
	float offset;      			//< offset
	float prevError;    		//< previous error
	float integ;        		//< integral
	float kp;           		//< proportional gain
	float ki;           		//< integral gain
	float kd;           		//< derivative gain
	float IntegLimitHigh;   //< integral limit
	float IntegLimitLow;
	float measured;
	float out;
	float OutLimitHigh;
	float OutLimitLow;
}PidObject;


typedef volatile struct
{
	my_uint8_t unlock;
	

}_st_ALL_flag;

extern _st_Remote Remote;
extern _st_Mpu MPU6050;
extern _st_AngE Angle;

extern _st_ALL_flag ALL_flag;

extern	PidObject pidRateX;
extern	PidObject pidRateY;
extern	PidObject pidRateZ;

extern	PidObject pidPitch;
extern	PidObject pidRoll;
extern	PidObject pidYaw;

extern my_int16_t motor_PWM_Value[4];

#endif