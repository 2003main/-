#include "IM948_TurnAngle.h"
#include "time_go.h"
#include "gray_go.h"
#include "TB6612.h"
#include "delay.h"
#include "im948_CMD.h"
extern float Yaw; 
uint8_t angle_now=0;
void IM948_init()
{
	// ���Ѵ������������úô���������������Ȼ���������ϱ�---------------

    Cmd_03();// 2 ���Ѵ�����
		Cmd_05();//���Z��Ƕ�
    /**
       * �����豸����
     * @param accStill    �ߵ�-��ֹ״̬���ٶȷ�ֵ ��λdm/s?
     * @param stillToZero �ߵ�-��ֹ�����ٶ�(��λcm/s) 0:������ 255:��������
     * @param moveToZero  �ߵ�-��̬�����ٶ�(��λcm/s) 0:������
     * @param isCompassOn 1=�迪���ų� 0=��رմų�
     * @param barometerFilter ��ѹ�Ƶ��˲��ȼ�[ȡֵ0-3],��ֵԽ��Խƽ�ȵ�ʵʱ��Խ��
     * @param reportHz ���������ϱ��Ĵ���֡��[ȡֵ0-250HZ], 0��ʾ0.5HZ
     * @param gyroFilter    �������˲�ϵ��[ȡֵ0-2],��ֵԽ��Խƽ�ȵ�ʵʱ��Խ��
     * @param accFilter     ���ټ��˲�ϵ��[ȡֵ0-4],��ֵԽ��Խƽ�ȵ�ʵʱ��Խ��
     * @param compassFilter �������˲�ϵ��[ȡֵ0-9],��ֵԽ��Խƽ�ȵ�ʵʱ��Խ��
     * @param Cmd_ReportTag ���ܶ��ı�ʶ
     */
    Cmd_12(5, 255, 0,  1, 0, 50, 1, 2, 5, 0x40);// 7 �����豸����(����1)
    Cmd_19();// 4 �������������ϱ�
}
/****************************************************************************
������			������ת�亯��
����				�����α���angle				
����				��void
����				�������ʼ���󣬸�������Ҫ��ת���ض��Ƕ�
������				����÷��
��������			��2024��1��26��14:07:41
���¸���ʱ��	��2024��1��30��14:38:50
****************************************************************************/

void ToAngle(int angle)        //��ʱδʹ��PID
{
	if((angle-angle_now)==180)
	{
		ToAngle(angle_now+90);
		Time_go(anti_LIAP,300);
		ToAngle(angle);
	}
	else if((angle-angle_now)==-180)
	{
		ToAngle(angle_now-90);
		Time_go(anti_LIAP,300);
		ToAngle(angle);
	}
	else
	{
			 while(Yaw>angle)             			//��ת
				 { 
					   Set_Motor(35,-35);
				 }
			 while(Yaw<angle)             			//��ת
				 { 
					   Set_Motor(-35,35);
				 }
				 if(angle>0){	Set_Motor(35,-35);delay_ms(50);Set_Motor(0,0);}
				 else {Set_Motor(-35,35);delay_ms(50);Set_Motor(0,0);}
				 angle_now=angle;
	}
}
