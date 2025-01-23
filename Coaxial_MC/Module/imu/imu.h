#ifndef __IMU_H
#define	__IMU_H

#include "alldata.h"

#define squa( Sq )        (((float)Sq)*((float)Sq))

extern void GetAngle(const _st_Mpu *pMpu,_st_AngE *pAngE, float dt);
extern void imu_rest(void);

#endif