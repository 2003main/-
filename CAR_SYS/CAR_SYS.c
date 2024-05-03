#include "CAR_SYS.h"




void CAR_Main(void)//系统调用逻辑函数
{
	Go_Centre();
	task1();
	
}



void CAR_Try(int Case)//调试历程
{
	#if 1
	switch(Case)
	{
		case 0://颜色识别测试    0
		{
			CAR_Init();
			color_distribution_two();
		}break;
		case 1://转角测试    1
		{
			ToAngle(90);
		}break;
	
	
	}
	#endif

}


void CAR_Init(void)
{
 	Stm32_Clock_Init(336,8,2,7);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //中断优先级分组
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //LED初始化
	MOTOR_Init();
	Usart1_Init(115200);//Openmv
	USART3_Init(115200);
	Uart4_Init(115200);//printf
	Uart5_Init(9600);//蓝牙
	Usart6_Init(115200);//串行舵机
	IIC3_Init();
	Grayscale_Init();
	EXTIX_Init();
	BEEP_Init();
	OLED_Init();
	MPU_Init();mpu_dmp_init();
	TCS34725_GPIO_Init();
	TCS34725_Init();
	integrationTime(33);//TCS34725初始化
	setPWMFreq(50);                //设置PCA9685频率为50HZ
	PCA9685_write(PCA9685_MODE1,0x0);//复位PCA9685	
	IM948_init();//IM948初始化
	duoji_Init();
}
