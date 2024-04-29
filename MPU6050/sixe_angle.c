#include "sixe_angle.h"
#include "TB6612.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "delay.h"

short myaw;
extern float pitch,roll,yaw; 
extern int yaw_count;
/****************************************************************************
������			��DMP�����õ����ݺ���
����				��void				
����				��void
����				���ж������Ƿ���յ����ݣ�����Yaw��������
������				����÷��
��������			��2024��1��26��14:07:41
���¸���ʱ��	��2024��1��30��14:38:50
****************************************************************************/
void Scan_MpuVal(void)
{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)			//dmp�����õ�����
			{ 	
				if(yaw_count==120000)yaw_count=0;
				
				myaw=yaw;
				myaw=myaw-0.0001*yaw_count-0.49;
				
			}
	
 }

 
/***************************************************************
 *  ����MPU6050�������� ����С��������̬ 
 *  ������				����÷��
 *  ��������			��2024��1��26��14:07:41
 **************************************************************/
 
/****************************************************************************
������			������ת�亯��
����				�����α���angle				
����				��void
����				�������ʼ���󣬸�������Ҫ��ת���ض��Ƕ�
������				����÷��
��������			��2024��1��26��14:07:41
���¸���ʱ��	��2024��1��30��14:38:50
****************************************************************************/

void MPUyaw_Car(int angle)        //��ʱδʹ��PID
 {
	 //int erro=2;
	 //angle-=erro;
	   //delay_ms(1000);			
					Scan_MpuVal();
	   while(myaw>angle)               			//��ת
				 {	
					 Scan_MpuVal();
					 Set_Motor(35,-35);
				 }
				 Scan_MpuVal();
    	 while(myaw<angle)               			//��ת
				 {	
					 Scan_MpuVal();
					 Set_Motor(-35,35);
				 }
			 
					Set_Motor(0,0);delay_ms(50);		
}
 /****************************����������MPUyaw_Car�ȣ�Ч������****************************/
/****************************************************************************
������			������ת�亯��
����				�����α���angle				
����				��void
����				�������ʼ���󣬸�������Ҫ��ת���ض��Ƕ�
������				����÷��
��������			��2024��1��26��14:07:41
���¸���ʱ��	��2024��1��30��14:38:50
****************************************************************************/

void Car_TurnToAngle4(int angle)        //��ʱδʹ��PID
{
	if(angle ==180||angle==-180)
	{
	  if(angle==180)
		{
		  Car_TurnToAngle4(90);
			Car_TurnToAngle4(178);
		}
		if(angle==-180)
		{
		  Car_TurnToAngle4(-90);
			Car_TurnToAngle4(-178);
		}
	}
	else
		{
	   int erro=1;
	   if(angle>0)
	   {
	     angle-=erro;
	   }
	   else angle+=erro;
	   Scan_MpuVal();
			 while(myaw>angle)             			//��ת
				 { 
						Scan_MpuVal();
					   Set_Motor(35,-35);
				 }
			 while(myaw<angle)             			//��ת
				 { 
						Scan_MpuVal();
					   Set_Motor(-35,35);
				 }
				 Scan_MpuVal();
				
			Set_Motor(0,0);delay_ms(50);	
    }
}