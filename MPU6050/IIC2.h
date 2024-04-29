#ifndef __IIC2_H
#define __IIC2_H
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//IIC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
   	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=0<<11*2;}	//PB11输入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<(11*2));GPIOB->MODER|=1<<11*2;} //PB11输出模式
//IO操作函数	 
#define IIC2_SCL    PBout(10) //SCL
#define IIC2_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11)  //输入SDA 

//IIC所有操作函数
void IIC2_Init(void);                //初始化IIC的IO口				 
void IIC2_Start(void);				//发送IIC开始信号
void IIC2_Stop(void);	  			//发送IIC停止信号
void IIC2_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC2_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC2_Wait_Ack(void); 				//IIC等待ACK信号
void IIC2_Ack(void);					//IIC发送ACK信号
void IIC2_NAck(void);				//IIC不发送ACK信号

void IIC2_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC2_Read_One_Byte(u8 daddr,u8 addr);	  
#endif


