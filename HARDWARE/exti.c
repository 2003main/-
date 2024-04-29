#include "exti.h"
#include "delay.h" 
#include "key.h"
#include "FreeRTOS.h"
#include "task.h"
#include "beep.h"
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init();
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource3);
	
	EXTI_InitStructure.EXTI_Line =  EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				
	EXTI_Init(&EXTI_InitStructure);							
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);							   
}

void EXTI4_IRQHandler(void)
{
	
	delay_xms(20);	
	if(EXTI_GetITStatus(EXTI_Line4)==SET)	 
	{	
		BEEP=~BEEP;
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line4);
}











