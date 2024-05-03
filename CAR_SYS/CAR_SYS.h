#ifndef __CAR_SYS_H
#define __CAR_SYS_H

#include "sys.h"
#include "delay.h"
#include "Usart1.h"
#include "Usart3.h"
#include "led.h"
#include "TB6612.h"
#include "Usart6.h"
#include "LobotSerialServo.h"
#include "bool.h"
#include "Action.h"
#include "PCA9685.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "grayscale.h"
#include "key.h"
#include "exti.h"
#include "beep.h"
#include "Uart4.h"
#include "Uart5.h"
#include "Servo.h"
#include "oled.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "TCS34725.h"
#include "gray_go.h"
#include "work.h"
#include "bsys.h"
#include "im948_CMD.h"
#include "IM948_TurnAngle.h"

extern int32_t i;
extern int32_t now_color;                 //储存当前识别的颜色
extern int32_t last_color;                //储存上一次识别的颜色——现特用于任务一case_three
extern int32_t now_position;              //储存当前处于哪个路径，默认在红色路径上
extern int32_t last_position;
extern int8_t a[];        //任务一检测是否去过红绿蓝路径
extern int8_t wukuai[];    //任务一检测路径上是否有物块
extern int32_t color[]; //各颜色对应的角度
extern int32_t anti_color[]; //各颜色对应的反向角度
extern int32_t color_distribution[]; //任务二颜色发布
extern int32_t color_residuum[]; //任务二剩余未检测物块
extern int32_t hozhua[]; //各颜色对应的角度
extern uint32_t Remainder;
extern uint32_t Divisor;
extern uint8_t  Dis_Buf1[8];
extern uint8_t  Dis_Buf2[8];
extern uint8_t  Dis_Buf3[8];
		
void CAR_Init(void);
void CAR_Try(int Case);
void CAR_Main(void);


#endif

