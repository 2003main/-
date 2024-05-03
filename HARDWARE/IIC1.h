#ifndef __IIC1_H_
#define __IIC1_H_


/**********************************
包含头文件
**********************************/
#include "stm32f4xx.h"                  // Device header

/**********************************
PIN口定义
**********************************/
#define IIC_SDA_PIN   				GPIO_Pin_3  //								
#define IIC_SCL_PIN    				GPIO_Pin_2			// 

#define  IIC_SDA_H   			GPIO_SetBits(GPIOG,IIC_SDA_PIN)
#define  IIC_SDA_L   			GPIO_ResetBits(GPIOG,IIC_SDA_PIN)

#define  IIC_SCL_H   			GPIO_SetBits(GPIOG,IIC_SCL_PIN)
#define  IIC_SCL_L   			GPIO_ResetBits(GPIOG,IIC_SCL_PIN)

#define  IIC_SDA_Read   GPIO_ReadInputDataBit(GPIOG, IIC_SDA_PIN)

/**********************************
函数声明
**********************************/
void IIC1_Init(void);
void SDA_Pin_IN(void);
void SDA_Pin_Output(void);
	

void TCS34725_IIC_Init(void);
void TCS34725_IIC_start(void); 
void TCS34725_IIC_stop(void);
uint8_t TCS34725_IIC_Get_ack(void);
void TCS34725_IIC_ACK(void);
void TCS34725_IIC_NACK(void);
void TCS34725_IIC_write_byte(uint8_t Data);
uint8_t TCS34725_IIC_read_byte(void);
void TCS34725_GPIO_Init(void)	;
#endif


