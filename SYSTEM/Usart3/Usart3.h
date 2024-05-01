#ifndef __USART3_H
#define __USART3_H
#include "sys.h"
#include "stm32f4xx.h"                  // Device heade

////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收


void USART3_Init(uint32_t bound);
int USART3_Write( const uint8_t *buf, int Len);
#endif
