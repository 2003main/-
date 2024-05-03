#include "CAR_SYS.h"




void CAR_Main(void)//ϵͳ�����߼�����
{
	Go_Centre();
	task1();
	
}



void CAR_Try(int Case)//��������
{
	#if 1
	switch(Case)
	{
		case 0://��ɫʶ�����    0
		{
			CAR_Init();
			color_distribution_two();
		}break;
		case 1://ת�ǲ���    1
		{
			ToAngle(90);
		}break;
	
	
	}
	#endif

}


void CAR_Init(void)
{
 	Stm32_Clock_Init(336,8,2,7);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //�ж����ȼ�����
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //LED��ʼ��
	MOTOR_Init();
	Usart1_Init(115200);//Openmv
	USART3_Init(115200);
	Uart4_Init(115200);//printf
	Uart5_Init(9600);//����
	Usart6_Init(115200);//���ж��
	IIC3_Init();
	Grayscale_Init();
	EXTIX_Init();
	BEEP_Init();
	OLED_Init();
	MPU_Init();mpu_dmp_init();
	TCS34725_GPIO_Init();
	TCS34725_Init();
	integrationTime(33);//TCS34725��ʼ��
	setPWMFreq(50);                //����PCA9685Ƶ��Ϊ50HZ
	PCA9685_write(PCA9685_MODE1,0x0);//��λPCA9685	
	IM948_init();//IM948��ʼ��
	duoji_Init();
}
