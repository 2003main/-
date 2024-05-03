#include "IM948_TurnAngle.h"
#include "TB6612.h"
#include "delay.h"
#include "im948_CMD.h"
extern float Yaw; 
void IM948_init()
{
	// 唤醒传感器，并配置好传感器工作参数，然后开启主动上报---------------

    Cmd_03();// 2 唤醒传感器
		Cmd_05();
    /**
       * 设置设备参数
     * @param accStill    惯导-静止状态加速度阀值 单位dm/s?
     * @param stillToZero 惯导-静止归零速度(单位cm/s) 0:不归零 255:立即归零
     * @param moveToZero  惯导-动态归零速度(单位cm/s) 0:不归零
     * @param isCompassOn 1=需开启磁场 0=需关闭磁场
     * @param barometerFilter 气压计的滤波等级[取值0-3],数值越大越平稳但实时性越差
     * @param reportHz 数据主动上报的传输帧率[取值0-250HZ], 0表示0.5HZ
     * @param gyroFilter    陀螺仪滤波系数[取值0-2],数值越大越平稳但实时性越差
     * @param accFilter     加速计滤波系数[取值0-4],数值越大越平稳但实时性越差
     * @param compassFilter 磁力计滤波系数[取值0-9],数值越大越平稳但实时性越差
     * @param Cmd_ReportTag 功能订阅标识
     */
    Cmd_12(5, 255, 0,  1, 0, 50, 1, 2, 5, 0x40);// 7 设置设备参数(内容1)
    Cmd_19();// 4 开启数据主动上报
}
/****************************************************************************
函数名			：六轴转弯函数
参数				：整形变量angle				
返回				：void
描述				：六轴初始化后，根据所需要求转到特定角度
创建人				：陈梅庆
创建日期			：2024年1月26日14:07:41
最新更改时间	：2024年1月30日14:38:50
****************************************************************************/

void ToAngle(int angle)        //暂时未使用PID
{

		if(angle ==180||angle==-180)
	{
	  if(angle==180)
		{
		  ToAngle(90);
			ToAngle(178);
		}
		if(angle==-180)
		{
		  ToAngle(-90);
			ToAngle(-178);
		}
	}
	else
	{
			 while(Yaw>angle)             			//右转
				 { 
					   Set_Motor(35,-35);
				 }
			 while(Yaw<angle)             			//左转
				 { 
					   Set_Motor(-35,35);
				 }
				 if(angle>0){	Set_Motor(35,-35);delay_ms(70);Set_Motor(0,0);}
				 else {Set_Motor(-35,35);delay_ms(70);Set_Motor(0,0);}
	}
}
