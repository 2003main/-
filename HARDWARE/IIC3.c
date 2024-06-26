#include "stm32f4xx.h"                  // Device header
#include "IIC3.h"
#include "delay.h"

//初始化IIC
void IIC3_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_I2C3); //GPIOA9复用为USART1
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_I2C3); //GPIOA10复用为USART1

  //GPIOA8,C9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

	IIC3_SCL=1;
	IIC3_SDA=1;
}
//产生IIC起始信号
void IIC3_Start(void)
{
	IIC3_SDA_OUT();     //sda线输出
	IIC3_SDA=1;	  	  
	IIC3_SCL=1;
	delay_us(4);
 	IIC3_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC3_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC3_Stop(void)
{
	IIC3_SDA_OUT();//sda线输出
	IIC3_SCL=0;
	IIC3_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC3_SCL=1; 
	IIC3_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC3_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC3_SDA_IN();      //SDA设置为输入  
	IIC3_SDA=1;delay_us(1);	   
	IIC3_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC3_Stop();
			return 1;
		}
	}
	IIC3_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC3_Ack(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();
	IIC3_SDA=0;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}
//不产生ACK应答		    
void IIC3_NAck(void)
{
	IIC3_SCL=0;
	IIC3_SDA_OUT();
	IIC3_SDA=1;
	delay_us(2);
	IIC3_SCL=1;
	delay_us(2);
	IIC3_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC3_Send_Byte(u8 txd)
{                        
    u8 t;   
	IIC3_SDA_OUT(); 	    
    IIC3_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC3_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC3_SCL=1;
		delay_us(2); 
		IIC3_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC3_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC3_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC3_SCL=0; 
        delay_us(2);
		IIC3_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC3_NAck();//发送nACK
    else
        IIC3_Ack(); //发送ACK   
    return receive;
}



