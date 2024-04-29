#ifndef __UART4_H
#define __UART4_H
#include "sys.h"
#include "stm32f4xx.h"                  // Device heade

void Uart4_Init(u32 bound);

//下面为与MPU6050结合
void uart4_send_char(u8 c);
void uart4_niming_report(u8 fun,u8*data,u8 len);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void uart4_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);

#endif
