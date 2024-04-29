#include "timer.h"
#include "led.h"
#include "time_go.h"

void TIM3_Init(u16 arr,u16 psc)
{
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能TIM3时钟
	  
	  TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	  TIM_TimeBaseInitStructure.TIM_Period=arr;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	  
	  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//使能定时器3的更新中断
	
	  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	
    TIM_Cmd(TIM3,ENABLE);//使能定时器3
}
