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
#include "BMP.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "TCS34725.h"
#include "gray_go.h"
#include "work.h"
#include "bsys.h"
#include "im948_CMD.h"
#include "IM948_TurnAngle.h"
/**********************接线***************************/
/*前八路灰度->八路灰度1  后八路灰度->八路灰度2*/
/*前一路灰度->HDIO2   中一路灰度->HDIO3 后一路灰度->HDIO4*/
/*左前电机 电机1 左后电机 电机2 右前电机 电机3 右后电机 电机4*/
/*pca9685 IIC1 TCS34725 IIC3*/
/***********************舵机**************************/
/*pca9685 接线
#define daduoji    7              //大舵机  
#define taotong_1  5  
#define taotong_2  6
#define hozhua_A   1  
#define hozhua_B   4
#define hozhua_C   3
#define hozhua_D   2
#define hozhua_E   0
#define qianzhua_zuo 9
#define qianzhua_you 8
*/
extern uint32_t Remainder;
extern uint32_t Divisor;
extern uint8_t  Dis_Buf1[8];
extern uint8_t  Dis_Buf2[8];
extern uint8_t  Dis_Buf3[8];
void Init()
{
 	Stm32_Clock_Init(336,8,2,7);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //中断优先级分组
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //LED初始化
	MOTOR_Init();
	Usart1_Init(115200);//Openmv
	USART3_Init(115200);
	Uart4_Init(115200);//printf
	Uart5_Init(9600);//蓝牙
	Usart6_Init(115200);//串行舵机
	IIC3_Init();
	Grayscale_Init();
	EXTIX_Init();
	BEEP_Init();
	OLED_Init();
	MPU_Init();mpu_dmp_init();
	TCS34725_GPIO_Init();TCS34725_Init();integrationTime(33);//TCS34725初始化
	setPWMFreq(50);                //设置PCA9685频率为50HZ
	PCA9685_write(PCA9685_MODE1,0x0);//复位PCA9685	
	IM948_init();//IM948初始化
	duoji_Init();
	delay_ms(3000);
}
void Try()
{
	/***************测试代码**************/
  //Set_Motor(30,30);
	//delay_ms(500);
	//Set_Motor(0,0);
//	delay_ms(500);
//	Set_Motor(-30,30);
//	delay_ms(500);
//	Set_Motor(0,0);
//	Set_Motor(30,-30);
//	delay_ms(500);
//	Set_Motor(0,0);
//	delay_ms(500);
//	Set_Motor(-30,-30);
//	delay_ms(500);
//	Set_Motor(0,0);
//	delay_ms(500);
	/**************巡线测试****************/
	//SearchRun();
	//SearchRun_Two();
	/**************定时跑***************/
	//Time_go(SearchRun,1000);
/********************巡线计次*********/
   //L_Front_Count(Car_Advance35,10);
/******************转弯测试*******************/
 //Car_TurnToAngle4(45);
 //Car_TurnToAngle4(-45);
 //Car_TurnToAngle4(-135);
 //Car_TurnToAngle4(-180);
// Car_TurnToAngle4(180);
/******************PCA9685测试***************/
/*****************舵机初始化测试*********************/
  //crazyMe(daduoji,40,40,6,120); //���
  //crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	//crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 
//	crazyMe(taotong_1,90,90,5,80);      //dakaitaotong
//	crazyMe(taotong_2,90,90,5,80);
    //crazyMe(hozhua_A,30,30,5,80);
		//crazyMe(hozhua_B,150,150,5,80);
	/*******************颜色识别模块测试**********************************/
//	  OLED_Refresh();
//		rgb=TCS34725_Get_RGBData();
//		RGB888=TCS34725_GetRGB888(rgb);
//		RGB565=TCS34725_GetRGB565(rgb);
//		Dis_Temp();
//		delay_ms(500);
/*******************转弯测试***********************************/
 //   Car_TurnToAngle4(180);
 /*********************测试***********************************/
//      Car_TurnToAngle4(45);
//			L_Front_Count(anti_SearchRun,6);
//			crazyMe(1,90,90,5,80);
//			L_Centre_Count(SearchRun,6);
	}


int main(void)
{
	
  Init();
	Go_Centre();
	task1();
	
	
}