#include "IIC1.h"
#include "delay.h"

#define IIC_D     6
void TCS34725_GPIO_Init(void)	
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOGʱ��

  GPIO_PinAFConfig(GPIOG,GPIO_PinSource2,GPIO_AF_I2C1);//SCL
  GPIO_PinAFConfig(GPIOG,GPIO_PinSource3,GPIO_AF_I2C1);//SDA

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
}

void SDA_Pin_IN(void)  //SDA����
{
	GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=0<<3*2;
}

void SDA_Pin_Output(void) //
{
	GPIOG->MODER&=~(3<<(3*2));GPIOG->MODER|=1<<3*2;
}
void TCS34725_IIC_Delay()
{
		delay_us(IIC_D);
}
/*
 *@brief 		IIC���߳�ʼ������
 *@param[in]	NULL
 *@author		MrWeng
 *@date			2020-8-10
 */
void TCS34725_IIC_Init(void)	
{
		IIC_SDA_H;//�ͷ�IIC���ߵ������ߡ�
		IIC_SCL_H;//�ͷ�IIC���ߵ�ʱ���ߡ�
		TCS34725_IIC_Delay();
}
/****************************************************************
ͨѶ��ʼ�źţ��� SCL ���Ǹߵ�ƽʱ SDA �ߴӸߵ�ƽ��͵�ƽ�л�����ʾͨѶ�Ŀ�ʼ��
*****************************************************************/

void TCS34725_IIC_start(void)  
{

		IIC_SDA_H;//����
		IIC_SCL_H;
		TCS34725_IIC_Delay();
		IIC_SDA_L;
		IIC_SCL_L;		//����ʱ���ߣ�׼����ʼʱ��
		TCS34725_IIC_Delay();
}
/****************************************************************
ͨѶֹͣ�źţ��� SCL �Ǹߵ�ƽʱ SDA���ɵ͵�ƽ��ߵ�ƽ�л�����ʾͨѶ��ֹͣ��
*****************************************************************/

void TCS34725_IIC_stop(void) 
{

		IIC_SCL_H;
		IIC_SDA_L;
		TCS34725_IIC_Delay();
		IIC_SDA_H;	//ͨѶֹͣ
		IIC_SCL_L;
		TCS34725_IIC_Delay();
}
/****************************************************************
//����Ӧ���źź���
*****************************************************************/

uint8_t TCS34725_IIC_Get_ack(void)
{
		uint16_t CNT;
		SDA_Pin_IN();
		IIC_SCL_L;		//����ʱ���ߡ�
		IIC_SCL_H;		//����ʱ���ߡ�
		TCS34725_IIC_Delay();
		while((IIC_SDA_Read)  && (CNT < 100) )
		{
				CNT++;
				if(CNT == 100)
				{
						return 0;
				}
		}

		IIC_SCL_L;		//����ʱ���ߡ�
		TCS34725_IIC_Delay();
		SDA_Pin_Output();
		return 1;

}
/****************************************************************
//����Ӧ���źź���
*****************************************************************/

void TCS34725_IIC_ACK(void)	
{ 

		IIC_SDA_L;	//���������ߣ�Ӧ��
		IIC_SCL_H;	//�����ھŸ�ʱ���źš�
		TCS34725_IIC_Delay();
		IIC_SCL_L;	
		TCS34725_IIC_Delay();
}
//��Ӧ��

void TCS34725_IIC_NACK(void)
{ 

		IIC_SDA_H;	//���������ߣ���Ӧ��
		IIC_SCL_H;	//�����ھŸ�ʱ���źš�
		TCS34725_IIC_Delay();
		IIC_SCL_L;	

}

/****************************************************************
//��IIC����д��һ���ֽڵ�����
*****************************************************************/

void TCS34725_IIC_write_byte(uint8_t Data)
{

		uint8_t i;
		for(i=0;i<8;i++)//��λ����
		{
				if((Data & 0x80) == 0x80)
				{
						IIC_SDA_H;
						
				}
				else
				{
						IIC_SDA_L;
						
				}
				
				IIC_SCL_H; //һ��ʱ���ź���������
				TCS34725_IIC_Delay();
				IIC_SCL_L;
				TCS34725_IIC_Delay();
				Data = Data << 1;//��������һλ���Ѵθ�λ�������λ,Ϊд��θ�λ��׼��
				
		}
		IIC_SDA_L;		//Ӧ����ǰ���ͣ�����Ӧ��

}
/****************************************************************
//��IIC���߶�ȡһ���ֽڵ����ݺ���
*****************************************************************/

uint8_t TCS34725_IIC_read_byte(void)
{

		uint8_t i;
		uint8_t Data = 0;       //����һ������Ĵ�����
		SDA_Pin_IN();
		IIC_SCL_L;	//������ʱ����
		IIC_SDA_H;	//������������
		TCS34725_IIC_Delay();
		for(i = 0;i < 8;i++)
		{
				Data = Data<<1;		//�������ֽڵ���������һλ��׼����ȡ���ݡ�
				
				IIC_SCL_H;				//����ʱ���ߣ���ʼ��ȡ��һλ����
				TCS34725_IIC_Delay();
				if(IIC_SDA_Read)		//���������Ϊ��ƽ��ƽ��
				{
						Data = Data|0x01;	//��������ֽڵ����λд1��
				}
				IIC_SCL_L;				//����ʱ���ߣ�һλ��ȡ���
				TCS34725_IIC_Delay();
		}
		SDA_Pin_Output();
		return Data;					//���ض�ȡ��һ���ֽ����ݡ�



}





