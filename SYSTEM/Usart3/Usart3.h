#ifndef __USART3_H
#define __USART3_H
#include "sys.h"
#include "stm32f4xx.h"                  // Device heade

////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����


void USART3_Init(uint32_t bound);
int USART3_Write( const uint8_t *buf, int Len);
#endif
