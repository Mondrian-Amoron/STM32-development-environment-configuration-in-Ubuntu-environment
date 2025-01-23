#ifndef __KALMAN_H
#define __KALMAN_H

//卡尔曼滤波参数结构体
struct KalmanFilter{
	float LastP;		//上一次协方差
	float NewP;		//最新的协方差
	float Out;			//卡尔曼输出
	float Kg;				//卡尔曼增益
	float Q;				//过程噪声的协方差
	float R;				//观测噪声的协方差
};

extern void kalmanfiter(struct KalmanFilter *EKF,float input);		//一维卡尔曼滤波

#endif