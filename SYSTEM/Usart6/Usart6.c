#include "stm32f4xx.h"                  // Device header
#include "string.h"
#include "Usart6.h"
#include "bool.h"
#include "LobotSerialServo.h"

u8 UART_RX_BUF[16];
bool isUartRxCompleted = false;

//int fputc(int ch, FILE *f)
//{
//        if(ch =='\n')  
//        {  
//            USART_SendData(USART6, 0x0D);  
//            while (!(USART6->SR & USART_FLAG_TXE)); 
//            USART_SendData(USART6, 0x0A);  
//            while (!(USART6->SR & USART_FLAG_TXE));  
//        }  
//        else  
//        {  
//            USART_SendData(USART6, (unsigned char)ch);  
//            while (!(USART6->SR & USART_FLAG_TXE));   
//        }  
//	return ch;
//}

void Usart6NVICInit(void) {
		//Usart6 NVIC
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

void Usart6_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG ,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART1时钟
	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);

	//USART6_TX   PG14
	//USART6_RX	  PG9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_9; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOG,&GPIO_InitStructure); //初始化PA9，PA10
	

	//USART ??
	USART_InitStructure.USART_BaudRate = bound;//???
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //???
	USART_InitStructure.USART_StopBits = USART_StopBits_1; //???
	USART_InitStructure.USART_Parity = USART_Parity_No; //???
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //???
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //????

	USART_Init(USART6, &USART_InitStructure);
	Usart6NVICInit();
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART6, ENABLE);
}

void Usart6WriteBuf(uint8_t *buf, uint8_t len)
{
	while (len--) {
		while ((USART6->SR & 0x40) == 0);
		USART_SendData(USART6,*buf++);
	}
}



void USART6_IRQHandler(void)
{
	uint8_t Res;
	static bool isGotFrameHeader = false;
	static uint8_t frameHeaderCount = 0;
	static uint8_t dataLength = 2;
	static uint8_t dataCount = 0;
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) { //??????
		Res = USART_ReceiveData(USART6);//(USART1->DR);	//?????????
		if (!isGotFrameHeader) {  //????
			if (Res == 0x55) {
				frameHeaderCount++;
				if (frameHeaderCount == 2) {
					frameHeaderCount = 0;
					isGotFrameHeader = true;
					dataCount = 1;
				}
			} else {
				isGotFrameHeader = false;
				dataCount = 0;
				frameHeaderCount = 0;
			}
		}
		if (isGotFrameHeader) { //????????
			UART_RX_BUF[dataCount] = Res;
			if (dataCount == 3) {
				dataLength = UART_RX_BUF[dataCount];
				if (dataLength < 3 || dataLength > 7) {
					dataLength = 3;
					isGotFrameHeader = false;
				}
			}
			dataCount++;
			if (dataCount == dataLength + 3) {
				if (isUartRxCompleted == false) {
					isUartRxCompleted = true;
					memcpy(LobotRxBuf, UART_RX_BUF, dataCount+2);	
				}
				isGotFrameHeader = false;
			}
		}
	}
}

bool isRxCompleted(void)
{
	if(isUartRxCompleted == true){
		isUartRxCompleted = false;
		return true;
	}else{
		return false;
	}
}

