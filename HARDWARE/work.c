#include "work.h"
#include "grayscale.h"
#include "TB6612.h"  
#include "gray_go.h"
#include "time_go.h"
#include "sixe_angle.h"
#include "PCA9685.h"
#include "TCS34725.h"
#include "bsys.h"//work.c定义的东西放在bsys.h中
#include "delay.h"
#include "beep.h"
#include "oled.h"
#include "IM948_TurnAngle.h"
int32_t i;
int32_t now_color;                 //储存当前识别的颜色
int32_t last_color;                //储存上一次识别的颜色——现特用于任务一case_three
int32_t now_position=0;              //储存当前处于哪个路径，默认在红色路径上
int32_t last_position;
uint8_t a[]={1,1,1};        //任务一检测是否去过红绿蓝路径
uint8_t wukuai[]={1,0,1,0,1};    //任务一检测路径上是否有物块
int32_t color[]={0,45,90,-45,-90}; //各颜色对应的角度
int32_t anti_color[]={175,-135,-90,135,90}; //各颜色对应的反向角度
int32_t color_distribution[]={5,5,5,5,5}; //任务二颜色发布
int32_t color_residuum[]={0,0,0,0,0}; //任务二剩余未检测物块
int32_t hozhua[]={hozhua_A,hozhua_B,hozhua_C,hozhua_D,hozhua_E}; //各颜色对应的角度



/**************************************************************************
函数功能：舵机初始化函数
入口参数：无
返 回 值：无
**************************************************************************/ 
void duoji_Init(void)
{
	  crazyMe(qianzhua_you,90,90,5,80);    
	  crazyMe(qianzhua_zuo,90,90,5,80);
    crazyMe(hozhua_A,90,90,5,80);      
		crazyMe(hozhua_B,90,90,5,80);
		crazyMe(hozhua_C,90,90,5,80);      
		crazyMe(hozhua_D,90,90,5,80);
		crazyMe(hozhua_E,90,90,5,80);
	  crazyMe(daduoji,40,40,5,80);        
	  crazyMe(taotong_1,10,10,5,80);     
	  crazyMe(taotong_2,10,10,5,80);
}
/**************************************************************************
函数功能：总任务函数
入口参数：无
返 回 值：无
**************************************************************************/ 
void work(void)
{
	Go_Centre();
	task1();
  task2(); 	
}
/**************************************************************************
函数功能：从开始点走到中心点
入口参数：无
返 回 值：无
**************************************************************************/ 
void Go_Centre(void)
{
	L_Centre_Count(SearchRun,8);
}

/**************************************************************************
函数功能：任务一函数
入口参数：无
返 回 值：无
**************************************************************************/ 
void task1(void)
{
	int32_t count=0;
	for(i=0;i<3;i++)
	{
		switch(count)
		{
			case 0:L_Front_Count(LIAP,2);break;
			case 1:
			if(wukuai[green]!=0){now_position=green;Time_delay_ms(500);ToAngle(color[green]);F_adjust_pose();L_Front_Count(LIAP,2);}
			else {now_position=blue;Time_delay_ms(500);ToAngle(color[blue]);F_adjust_pose();L_Front_Count(LIAP,2);}
			break;
			case 2:{now_position=blue;Time_delay_ms(500);ToAngle(color[blue]);F_adjust_pose();L_Front_Count(LIAP,2);}break;			
		}
		Time_delay_ms(500);//时间可以减小
		color_discrimination();
		color_distribution_one();
		if(now_position==now_color)      case_one();
		else if(now_position!=now_color)
		{
			if(wukuai[now_color]==0)       case_two();
			else if(wukuai[now_color]==1)  case_three();
		}
		switch(count)
		{
			case 0:wukuai[red]=0;break;
			case 1:wukuai[green]=0;break;
			case 2:wukuai[blue]=0;break;			
		}
		count++;
	}
}

/**************************************************************************
函数功能：任务二函数
入口参数：无
返 回 值：无
**************************************************************************/ 
void task2(void)
{
	int32_t a[]={-45,42};//要修改
	for(int b=0;b<2;b++)
	{
		Car_TurnToAngle4(a[b]);
		B_adjust_pose();
		L_Centre_Count(anti_SearchRun,6);
		task_two_catch();
		if(b==0)
		{
			L_Centre_Count(SearchRun,4);
			crazyMe(hozhua_D,90,90,5,80);
			Time_go(Car_Advance30,300);
			//time_go前进一段距离
			Car_TurnToAngle4(130);
			Time_go(Car_Advance30,600);
			//time_go后退一段距离
			color_distribution_two();
			catch_it();
			L_Centre_Count(anti_SearchRun,6);	
			task_two_release(b,C);
		  task_two_release(b,E);
		  task_two_release(b,A);
		  task_two_release(b,B);
		  task_two_release(b,D);
		}
		else if(b==1)
		{
		  L_Centre_Count(SearchRun,8);
			task_two_release(b,D);
		  task_two_release(b,E);
		  task_two_release(b,C);
		  task_two_release(b,B);
		  task_two_release(b,A);
		}

		if(b==1)
		{	
			task_two_go_destination(D);			
			task_two_go_destination(C);	
			task_two_go_destination(E);
			task_two_go_destination(A);
			task_two_go_destination(B);
			Car_TurnToAngle4(0);
			L_Centre_Count(anti_SearchRun,8);
		}

	}
}

/**************************************************************************
函数功能：任务一遇到色块与当前此时对应颜色相同时采用的方案
入口参数：无
返 回 值：无
**************************************************************************/ 
void case_one(void)
{	
	//crazyMe(qianzhua_you,90,0,5,80);      //抓住物块
	//crazyMe(qianzhua_zuo,90,180,5,80);
	L_Front_Count(LIAP,2);
	Time_go(Car_Retreat28,120);
//	crazyMe(qianzhua_you,0,90,5,80);      //放开物块
//	crazyMe(qianzhua_zuo,180,90,5,80);
	wukuai[now_color]=0;
	L_Centre_Count(anti_SearchRun,6);    //退回到中心
	F_adjust_pose();                     //调整位置
}

/**************************************************************************
函数功能：任务一遇到色块与当前此时对应颜色不相同时且没有物块阻挡时采用的方案
入口参数：无
返 回 值：无
**************************************************************************/ 
void case_two(void)
{
	catch_it();                         //夹物块
	L_Centre_Count(anti_SearchRun,4); //退回到中心
	F_adjust_pose();                     //调整位置
	Car_TurnToAngle4(color[now_color]);//转到目标角度
	F_adjust_pose();                     //调整位置
	now_position=now_color;
	L_Back_Count(LIAP,2);       //到达放物块区
	L_Front_Count(LIAP,4);       //到达放物块区
	//加Time_go后退
	Time_go(Car_Retreat28,180);
	crazyMe(daduoji,90,90,5,80);        //下降
	crazyMe(taotong_1,90,90,5,80);      //放开物块
	crazyMe(taotong_2,90,90,5,80);
	crazyMe(daduoji,90,40,5,80);        //上升
	wukuai[now_color]=0;
	L_Centre_Count(anti_SearchRun,6); //退回到中心
	F_adjust_pose();                   //调整位置
}

/**************************************************************************
函数功能：任务一遇到色块与当前此时对应颜色不相同时且有物块阻挡时采用的方案
入口参数：无
返 回 值：无
**************************************************************************/ 
void case_three(void)
{
	catch_it();                            //夹物块
	L_Centre_Count(anti_SearchRun,4);    //退回到中心
	Time_go(Car_Advance30,60);         //调整位置
	Car_TurnToAngle4(color[now_color]);   //转到目标角度
	Time_go(Car_Advance30,60);                   //调整位置
	now_position=now_color;
	L_Front_Count(LIAP,2);          //到达阻碍物块前
	last_color=now_color;                 
	color_discrimination();               //识别阻碍物块的颜色，并更改now_color的值
	color_distribution_one();
	if((last_color==green&&now_color==blue&&i==0)||(last_color==blue&&now_color==green&&i==0))
	{
		crazyMe(qianzhua_you,90,0,5,80);      //抓住阻碍物块
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Back_Count(anti_SearchRun,8); 
		crazyMe(hozhua_A,150,150,5,80);
		crazyMe(hozhua_B,30,30,5,80);
		L_Centre_Count(SearchRun,4);     //退回到中心
		B_adjust_pose();                  //调整位置
		Car_TurnToAngle4(color[now_color]);   //转到目标角度（阻碍物块的路径上）
		B_adjust_pose();                           //调整位置
		last_position=now_color; 
		now_position=now_color;
		L_Back_Count(LIAP,2);           //到达放物块区
		L_Front_Count(LIAP,4);           //到达放物块区
		//加time_go 后退
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);       //放开阻碍物块
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,6);     //退回到中心
		F_adjust_pose();                         //调整位置
		Car_TurnToAngle4(color[last_color]);   //转到目标角度
		F_adjust_pose();                         //调整位置
		now_position=last_color;
		now_color=last_color;
		L_Back_Count(LIAP,2);           //到达放物块区
		L_Front_Count(LIAP,4);           //到达放物块区
		Time_go(Car_Retreat28,150);
		crazyMe(daduoji,40,90,5,80);            //下降
		crazyMe(taotong_1,90,90,5,80);          //放开物块
		crazyMe(taotong_2,90,90,5,80);
		crazyMe(daduoji,90,40,5,80);           //上升
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,2);     //退回
		crazyMe(hozhua_A,90,90,5,80);
		crazyMe(hozhua_B,90,90,5,80);
		//Time_go后退一段距离
		Time_go(Car_Advance30,300);
		Car_TurnToAngle4(-color[now_position]);   //转到目标角度
		L_Front_Count(SearchRun,2);
		color_discrimination();
		now_position=last_position;
		color_distribution_one(); 
		crazyMe(qianzhua_you,90,0,5,80);   //抓住阻碍物块   
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Centre_Count(SearchRun,4);
		B_adjust_pose();                       //调整位置
		Car_TurnToAngle4(color[now_color]);   //转到目标角度
		B_adjust_pose();                       //调整位置
		now_position=now_color;
		L_Back_Count(LIAP,2);           //到达放物块区
		L_Front_Count(LIAP,4);           //到达放物块区
		//time_go后退
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);     //放开阻碍物块  
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,6); //退回到中心
		F_adjust_pose();                 //调整位置
		i=i+2;
	}
	else
	{
		crazyMe(qianzhua_you,90,0,5,80);       //抓住阻碍物块
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Centre_Count(anti_SearchRun,4);     //退回到中心
		F_adjust_pose();                      //调整位置
		Car_TurnToAngle4(color[now_color]);    //转到目标角度（阻碍物块的路径上）
	  F_adjust_pose();                         //调整位置
		now_position=now_color;
		L_Back_Count(LIAP,2);           //到达放物块区
		L_Front_Count(LIAP,4);           //到达放物块区
		//time_go后退
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);       //放开阻碍物块
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		
		L_Centre_Count(anti_SearchRun,6);     //退回到中心
		F_adjust_pose();                         //调整位置
		Car_TurnToAngle4(color[last_color]);   //转到目标角度
		F_adjust_pose();                        //调整位置
		now_position=now_color;
		L_Back_Count(LIAP,2);           //到达放物块区
		L_Front_Count(LIAP,4);           //到达放物块区
		Time_go(Car_Retreat28,150);
		crazyMe(daduoji,90,90,5,80);            //下降
		crazyMe(taotong_1,90,90,5,80);          //放开物块
		crazyMe(taotong_2,90,90,5,80);          //放开物块
		crazyMe(daduoji,40,40,5,80);        
		wukuai[last_color]=0;
		L_Centre_Count(anti_SearchRun,6); //退回到中心
		F_adjust_pose();
		i++;
	}

}

/**************************************************************************
函数功能：中心处调整姿态，使其在黑线上，减小误差，使小车更稳
入口参数：无
返 回 值：无
**************************************************************************/
void F_adjust_pose(void)
{
  Time_go(Car_Advance30,110);
}
/**************************************************************************
函数功能：中心处调整姿态，使其在黑线上，减小误差，使小车更稳
入口参数：无
返 回 值：无
**************************************************************************/
void B_adjust_pose(void)
{
  Time_go(Car_Retreat30,110);
}

/**************************************************************************
函数功能：将物块夹到套筒上
入口参数：无
返 回 值：无
**************************************************************************/
void catch_it(void)
{
	//后退一小段距离，没有Time_go,需要补上
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,90);
	crazyMe(taotong_1,90,90,5,80);      //dakaitaotong
	crazyMe(taotong_2,90,90,5,80);
	crazyMe(daduoji,40,90,5,80);        //下降
	crazyMe(taotong_1,30,30,5,80);      //夹住物块
	crazyMe(taotong_2,30,30,5,80);
	crazyMe(daduoji,90,40,5,80);        //上升
}

/**************************************************************************
函数功能：在套筒中有一个物块的情况下将另一个物块夹到套筒上
入口参数：无
返 回 值：无
**************************************************************************/
void catch_it2(void)
{
	//后退一小段距离，没有Time_go,需要补上
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,80);
	crazyMe(daduoji,40,75,6,120);        //下降                     因为没有结合实际，要自己写
	crazyMe(taotong_1,90,90,6,120);      //打开套筒
	crazyMe(taotong_2,90,90,6,120);
	crazyMe(daduoji,75,90,6,120);        //下降        
	crazyMe(taotong_1,30,30,5,80);      //夹住物块
	crazyMe(taotong_2,30,30,5,80);
	crazyMe(daduoji,90,40,5,80);        //上升
}

/**************************************************************************
函数功能：将物块从套筒上放下来
入口参数：无
返 回 值：无
**************************************************************************/
void release_it(void)
{
		//后退一小段距离，没有Time_go,需要补上
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 

	//后退一小段距离，没有Time_go,需要补上                        因为没有结合实际，要自己写
	Time_go(Car_Retreat28,100);
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,80);
	crazyMe(daduoji,40,68,5,80);        //下降
	crazyMe(taotong_1,90,90,5,80);      
	crazyMe(taotong_2,90,90,5,80);
	//后退一小段距离，没有Time_go,需要补上
  Time_go(Car_Retreat28,10);
	crazyMe(daduoji,68,90,5,80);        //下降
	crazyMe(taotong_1,20,20,5,80);      
	crazyMe(taotong_2,20,20,5,80);
	crazyMe(taotong_1,90,90,5,80);      
	crazyMe(taotong_2,90,90,5,80);
}


/**************************************************************************
函数功能：蜂鸣器校验颜色函数
入口参数：整形变量x
返 回 值：无
**************************************************************************/ 
void beep(int x)
{
	int i;
	for( i=0;i<x;i++)
			{
				 BEEP=!BEEP;
				 delay_ms(200);
				 BEEP=!BEEP;
				delay_ms(50);
			}
}
/**************************************************************************
函数功能：识别颜色
入口参数：无
返 回 值：无
**************************************************************************/ 
void color_discrimination(void)
{

	  rgb=TCS34725_Get_RGBData();
		RGB888=TCS34725_GetRGB888(rgb);
		RGB565=TCS34725_GetRGB565(rgb);
		Dis_Temp();
		if(R_Dat>200&&R_Dat>(G_Dat+B_Dat))                                                         {now_color=red;beep(3);}  //红
	  else if(2*G_Dat>(2*R_Dat+B_Dat)&&G_Dat>150)                                                {now_color=green;beep(1);}//绿
    else if(B_Dat>160&&G_Dat<230&&2*B_Dat>(R_Dat+G_Dat))                                       {now_color=blue;beep(5);} //蓝
	  else if((G_Dat-R_Dat)>30&&(G_Dat-R_Dat)<60&&R_Dat>120&&G_Dat>150&&(R_Dat+B_Dat)>G_Dat)     {now_color=black;beep(4);}//黑
    else if(R_Dat>200&&G_Dat>200&&G_Dat>R_Dat)             
                                 {now_color=white;beep(2);}//白 
}
/**************************************************************************
函数功能：任务一中确认任务二颜色发布情况
入口参数：无
返 回 值：无
**************************************************************************/ 
void color_distribution_one(void)
{
	switch(now_position)
	{
		case red:color_distribution[C]=now_color;color_residuum[now_color]=1;break;
		case green:color_distribution[A]=now_color;color_residuum[now_color]=1;break;
		case blue:color_distribution[E]=now_color;color_residuum[now_color]=1;break;
	}
}

/**************************************************************************
函数功能：任务二中确认任务二颜色发布情况
入口参数：无
返 回 值：无
**************************************************************************/ 
void color_distribution_two(void)
{
	color_discrimination();
	color_distribution[D]=now_color;
	color_residuum[now_color]=1;
	if(color_residuum[red]==0)
	{
	color_distribution[B]=red;
	}
		if(color_residuum[white]==0)
	{
	color_distribution[B]=white;
	}
		if(color_residuum[green]==0)
	{
	color_distribution[B]=green;
	}
		if(color_residuum[black]==0)
	{
	color_distribution[B]=black;
	}
		if(color_residuum[blue]==0)
	{
	color_distribution[B]=blue;
	}
}

/**************************************************************************
函数功能：任务二抓物块函数
入口参数：无
返 回 值：无
**************************************************************************/ 
void task_two_catch(void)
{
		crazyMe(hozhua_A,160,160,5,80);      
		crazyMe(hozhua_B,20,20,5,80);
		crazyMe(hozhua_C,160,160,5,80);      
		crazyMe(hozhua_D,30,30,5,80);
		crazyMe(hozhua_E,40,40,5,80);
}

/**************************************************************************
函数功能：任务二放物块函数
入口参数：b为第几次循环 b=0~1 ,number为放哪个位置的物块 number={A B C D E};
返 回 值：无
**************************************************************************/ 
void task_two_release(int32_t b,int32_t number)
{
	if(b==0)
	{
		if(number==D)
		{
			Time_go(Car_Advance30,60);
			Car_TurnToAngle4(color[color_distribution[number]]);
			Time_go(Car_Advance30,110);
			L_Centre_Count(SearchRun,2);
			L_Centre_Count(SearchRun,2);
			release_it();
			L_Centre_Count(anti_SearchRun,4);		
      F_adjust_pose();			
		}
		else
		{ 
			Time_go(Car_Advance30,60);
			Car_TurnToAngle4(anti_color[color_distribution[number]]);
			Time_go(Car_Advance30,110);
			L_Front_Count(anti_SearchRun,6);
			L_Centre_Count(anti_SearchRun,2);	
			crazyMe(hozhua[number],90,90,5,80);
			L_Centre_Count(SearchRun,6);		
			B_adjust_pose();
		}

	}
	else if(b==1)
	{ 
		if(number==A)
		{
		  Time_go(Car_Retreat30,60);
		  Car_TurnToAngle4(anti_color[color_distribution[number]]);
		  Time_go(Car_Retreat30,110);
		  L_Front_Count(anti_SearchRun,4);
		  crazyMe(hozhua[B],90,90,5,80);
		  L_Centre_Count(SearchRun,4);
		  B_adjust_pose();
		}
		if(number==B)
		{
		  Time_go(Car_Retreat30,60);
		  Car_TurnToAngle4(anti_color[color_distribution[number]]);
		  Time_go(Car_Retreat30,110);
		  L_Front_Count(anti_SearchRun,4);
		  crazyMe(hozhua[A],90,90,5,80);
		  L_Centre_Count(SearchRun,4);
		  B_adjust_pose();
		}
		if(number==C)
		{
		  Time_go(Car_Retreat30,60);
		  Car_TurnToAngle4(anti_color[color_distribution[number]]);
		  Time_go(Car_Retreat30,110);
		  L_Front_Count(anti_SearchRun,4);
		  crazyMe(hozhua[E],90,90,5,80);
		  L_Centre_Count(SearchRun,4);
		  B_adjust_pose();
		}
		if(number==D)
		{
		  Time_go(Car_Retreat30,60);
		  Car_TurnToAngle4(anti_color[color_distribution[number]]);
		  Time_go(Car_Retreat30,110);
		  L_Front_Count(anti_SearchRun,4);
		  crazyMe(hozhua[D],90,90,5,80);
		  L_Centre_Count(SearchRun,4);
		  B_adjust_pose();
		}
		if(number==E)
		{
		  Time_go(Car_Retreat30,60);
		  Car_TurnToAngle4(anti_color[color_distribution[number]]);
		  Time_go(Car_Retreat30,110);
		  L_Front_Count(anti_SearchRun,4);
		  crazyMe(hozhua[C],90,90,5,80);
		  L_Centre_Count(SearchRun,4);
		  B_adjust_pose();
		}
	}
}

/**************************************************************************
函数功能：任务二将物块放到目的位置
入口参数：number为放哪个位置的物块 number={A B C D E};
返 回 值：无
**************************************************************************/ 
void task_two_go_destination(int32_t number)
{
	Time_go(Car_Advance30,60);
	Car_TurnToAngle4(color[color_distribution[number]]);
	Time_go(Car_Advance30,110);
	L_Back_Count(SearchRun,6);
	catch_it();
	L_Centre_Count(SearchRun,2);	
	catch_it2();
	L_Front_Count(SearchRun,2);	
	release_it();
	L_Centre_Count(anti_SearchRun,6);
}

/******************转弯前停下，使小车更稳***************/
void stop_time(int time)
{
   Time_go(Car_Stop,time);
}
