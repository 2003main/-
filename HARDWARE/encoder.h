#ifndef __ENCODER_H
#define __ENCODER_H 			   
#include "sys.h"	 

/*--------Motor_A control pins--------*/
#define PWM_PORTA1 GPIOC			 //PWMA
#define PWM_PIN_A1 GPIO_Pin_6 //PWMA
#define PWMA1 	  TIM8->CCR1	 //PWMA

#define PWM_PORTA2 GPIOC			 //PWMA
#define PWM_PIN_A2 GPIO_Pin_7 //PWMA
#define PWMA2 	  TIM8->CCR4	 //PWMA
/*------------------------------------*/

/*--------Motor_B control pins--------*/
#define PWM_PORTB1 GPIOD			 //PWMB
#define PWM_PIN_B1 GPIO_Pin_12 //PWMB
#define PWMB1 	  TIM4->CCR1	 //PWMB

#define PWM_PORTB2 GPIOD			 //PWMB
#define PWM_PIN_B2 GPIO_Pin_13 //PWMB
#define PWMB2 	  TIM4->CCR2	 //PWMB

/*------------------------------------*/

/*--------Motor_C control pins--------*/
#define PWM_PORTC1 GPIOA			 //PWMC
#define PWM_PIN_C1 GPIO_Pin_7 //PWMC
#define PWMC1 	  TIM3->CCR2	 //PWMC

#define PWM_PORTC2 GPIOA			 //PWMC
#define PWM_PIN_C2 GPIO_Pin_6 //PWMC
#define PWMC2 	  TIM3->CCR1	 //PWMC

/*------------------------------------*/

/*--------Motor_D control pins--------*/
#define PWM_PORTD1 GPIOE			 //PWMD
#define PWM_PIN_D1 GPIO_Pin_9 //PWMD
#define PWMD1 	  TIM1->CCR2	 //PWMD

#define PWM_PORTD2 GPIOE			 //PWMD
#define PWM_PIN_D2 GPIO_Pin_11 //PWMD
#define PWMD2 	  TIM1->CCR1	 //PWMD

/*------------------------------------*/

// No larger than 65535, because the timer of STM32F103 is 16 bit
//不可大于65535，因为STM32F103的定时器是16位的
#define ENCODER_TIM_PERIOD (u16)(65535)   

void Encoder_Init_TIM8(void);
void Encoder_Init_TIM4(void);
void Encoder_Init_TIM3(void);
void Encoder_Init_TIM1(void);

//u8 EN=1;

int Read_Encoder(u8 TIMX);

void TIM8_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM1_IRQHandler(void);

void TIM8_BRK_TIM12_IRQHandler(void);

#endif


