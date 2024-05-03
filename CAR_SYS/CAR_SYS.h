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
extern int32_t now_color;                 //���浱ǰʶ�����ɫ
extern int32_t last_color;                //������һ��ʶ�����ɫ����������������һcase_three
extern int32_t now_position;              //���浱ǰ�����ĸ�·����Ĭ���ں�ɫ·����
extern int32_t last_position;
extern int8_t a[];        //����һ����Ƿ�ȥ��������·��
extern int8_t wukuai[];    //����һ���·�����Ƿ������
extern int32_t color[]; //����ɫ��Ӧ�ĽǶ�
extern int32_t anti_color[]; //����ɫ��Ӧ�ķ���Ƕ�
extern int32_t color_distribution[]; //�������ɫ����
extern int32_t color_residuum[]; //�����ʣ��δ������
extern int32_t hozhua[]; //����ɫ��Ӧ�ĽǶ�
extern uint32_t Remainder;
extern uint32_t Divisor;
extern uint8_t  Dis_Buf1[8];
extern uint8_t  Dis_Buf2[8];
extern uint8_t  Dis_Buf3[8];
		
void CAR_Init(void);
void CAR_Try(int Case);
void CAR_Main(void);


#endif

