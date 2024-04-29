#include "stm32f4xx.h"                  // Device header
#include "grayscale.h"
#include "delay.h"
#include "TB6612.h"
//���⴫����
void HDIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOCʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//HDIO1,2,3,4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOC, &GPIO_InitStructure);                   //��ʼ��GPIO
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOBʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//HDIO5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOF, &GPIO_InitStructure);                   //��ʼ��GPIO

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//HDIO6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);                   //��ʼ��GPIO

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;//HDIO7,8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOA, &GPIO_InitStructure);                   //��ʼ��GPIO
}
//��·�Ҷ�1
void eight_gray1(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;//��·�Ҷ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOF, &GPIO_InitStructure);                   //��ʼ��GPIO

}
void eight_gray2(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;//��·�Ҷ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOE, &GPIO_InitStructure);                   //��ʼ��GPIO
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOFʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;//��·�Ҷ�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;             //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;           //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;       //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;             //����
  GPIO_Init(GPIOB, &GPIO_InitStructure);                   //��ʼ��GPIO

}
void Grayscale_Init(void)
{
	HDIO_Init();
	eight_gray1();
	eight_gray2();
}
/*****************************************
*****����Ϊ�Ҷ��������Ѳ�ߺ���(��Ҫ����Ѳ�ߴ������������)
******************************************/

/**********������һ·***************/
void RL_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(16);
				if(L_Centre!= a)
				{
					i++;
					a = L_Centre;
				}
			}
			
				if(R_Centre!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(16);
				if(R_Centre != b)
				{
					k++;
					b = R_Centre;
				}
			}
		if(i>=ti&&k>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
/************���Һ�һ·�Ҷ�****************/
void RL_Back_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_back!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_back!= a)
				{
					i++;
					a = L_back;
				}
			}
			
				if(R_back!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_back != b)
				{
					k++;
					b = R_back;
				}
			}
		if(i>=ti&&k>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
///****************����ǰ��·�Ҷ����************/
void RL_Front_Count(void (*d)(void),int ti)
{
	int a = 1,b=1,i = 0,k=0;
	while(1)
   {
		(*d)();
		if(L_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_front!= a)
				{
					i++;
					a = L_front;
				}
			}
			
				if(R_front!= b)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_front != b)
				{
					k++;
					b = R_front;
				}
			}
		if(i>=ti&&k>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}

///**************����Ϊ����Ҷȼ���*********/

/*****************��ǰ�Ҷ����***************/
void R_Front_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_front!= a)
				{
					i++;
					a = R_front;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}

//��ǰ�Ҷ�
void L_Front_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_front!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_front!= a)
				{
					i++;
					a = L_front;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
/*****************����һ·�Ҷ�**************/
void R_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(R_Centre!= a)
				{
					i++;
					a = R_Centre;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
///*****************����һ·�Ҷ�**************/
void L_Centre_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_Centre!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_Centre!= a)
				{
					i++;
					a = L_Centre;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
///****************�Һ�һ·�Ҷ�******************/
void R_Back_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(R_back!=a)                     //��¼���������ɿ�λ
			{
				 delay_ms(20);
				if(R_back!= a)
				{
					i++;
					a = R_back;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
///****************���һ·�Ҷ�******************/
void L_Back_Count(void (*d)(void),int ti)
{
	int a = 1,i = 0;
	while(1)
   {
		(*d)();
		if(L_back!=a)                     //��¼���������ɿ�λ
			{
				delay_ms(20);
				if(L_back!= a)
				{
					i++;
					a = L_back;
				}
			}
			
		if(i>=ti)
		{
			break;
		}
	}
	 Set_Motor(0,0);
}
