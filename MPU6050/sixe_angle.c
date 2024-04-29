#include "sixe_angle.h"
#include "TB6612.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "delay.h"

short myaw;
extern float pitch,roll,yaw; 
extern int yaw_count;
/****************************************************************************
函数名			：DMP处理得到数据函数
参数				：void				
返回				：void
描述				：判断六轴是否接收到数据，并将Yaw储存下来
创建人				：陈梅庆
创建日期			：2024年1月26日14:07:41
最新更改时间	：2024年1月30日14:38:50
****************************************************************************/
void Scan_MpuVal(void)
{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)			//dmp处理得到数据
			{ 	
				if(yaw_count==120000)yaw_count=0;
				
				myaw=yaw;
				myaw=myaw-0.0001*yaw_count-0.49;
				
			}
	
 }

 
/***************************************************************
 *  调用MPU6050计算数据 控制小车方向姿态 
 *  创建人				：陈梅庆
 *  创建日期			：2024年1月26日14:07:41
 **************************************************************/
 
/****************************************************************************
函数名			：六轴转弯函数
参数				：整形变量angle				
返回				：void
描述				：六轴初始化后，根据所需要求转到特定角度
创建人				：陈梅庆
创建日期			：2024年1月26日14:07:41
最新更改时间	：2024年1月30日14:38:50
****************************************************************************/

void MPUyaw_Car(int angle)        //暂时未使用PID
 {
	 //int erro=2;
	 //angle-=erro;
	   //delay_ms(1000);			
					Scan_MpuVal();
	   while(myaw>angle)               			//右转
				 {	
					 Scan_MpuVal();
					 Set_Motor(35,-35);
				 }
				 Scan_MpuVal();
    	 while(myaw<angle)               			//左转
				 {	
					 Scan_MpuVal();
					 Set_Motor(-35,35);
				 }
			 
					Set_Motor(0,0);delay_ms(50);		
}
 /****************************经调整，比MPUyaw_Car稳，效果更好****************************/
/****************************************************************************
函数名			：六轴转弯函数
参数				：整形变量angle				
返回				：void
描述				：六轴初始化后，根据所需要求转到特定角度
创建人				：陈梅庆
创建日期			：2024年1月26日14:07:41
最新更改时间	：2024年1月30日14:38:50
****************************************************************************/

void Car_TurnToAngle4(int angle)        //暂时未使用PID
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
			 while(myaw>angle)             			//右转
				 { 
						Scan_MpuVal();
					   Set_Motor(35,-35);
				 }
			 while(myaw<angle)             			//左转
				 { 
						Scan_MpuVal();
					   Set_Motor(-35,35);
				 }
				 Scan_MpuVal();
				
			Set_Motor(0,0);delay_ms(50);	
    }
}