#include "USART3.h"
#include "im948_CMD.h"
u8 USART3_RX_BUF[USART_REC_LEN];
u16 USART3_RX_STA=0;       //����״̬���	
void USART3_Init(u32 bound)
{
   //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3); //GPIOD8����ΪUSART3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); //GPIOD9����ΪUSART3
	
	//USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //GPIOC10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PC10

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PC11

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3
	
	//USART_ClearFlag(UART5, USART_FLAG_TC);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}
void USART3_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		Res =USART_ReceiveData(USART3);//(USART1->DR);	//��ȡ���յ�������
		Cmd_GetPkt(Res); // ��ֲ ÿ�յ�1�ֽ����ݶ�����ú�������ץȡ����Ч�����ݰ��ͻ�ص����� Cmd_RxUnpack(U8 *buf, U8 DLen) ��������		
  } 
} 
int USART3_Write( const uint8_t *buf, int Len)
{
    int i;
 
        for (i = 0; i < Len; i++)
        {
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
            USART_SendData(USART3, buf[i]);
        }

    return Len;
}
