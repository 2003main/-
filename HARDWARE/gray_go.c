#include "gray_go.h"
#include "delay.h"
#include "TB6612.h"
/*新八路灰度*/
/**************************前进巡线**************************/
void SearchRun(void)
{
	if(F2==1&&F3==1&&F4==0&&F5==0&&F6==1&&F7==1)   Set_Motor(28,28);
	  //右偏   新八路灰度  黑 0 白 1  F7左F2右
  else if(F7==1&&F6==1&&F5==0&&F4==1&&F3==1&&F2==1)   {Set_Motor(18,38);delay_ms(5);}
  else if(F7==1&&F6==0&&F5==0&&F4==1&&F3==1&&F2==1)   Set_Motor(14,42);
  else if(F7==1&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(12,44);
  else if(F7==0&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(6,50);
  else if(F7==0&&F6==1&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-35,35);
	  //左偏
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==1&&F2==1)   {Set_Motor(38,18);delay_ms(5);}
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==0&&F2==1)   Set_Motor(42,14);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==1)   Set_Motor(44,12);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==0)   Set_Motor(50,6);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==1&&F2==0)   Set_Motor(35,-35);

  else                                                              Set_Motor(28,28);
}

/**************************后退巡线**************************/
void anti_SearchRun(void)
{
	//车正
  if(D1==1&&D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1&&D8==1)        Set_Motor(-28,-28);
//右偏
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-18,-38);delay_ms(5);}
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   Set_Motor(-14,-42);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-12,-44);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(-6,-50);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(35,-35);
//左偏
  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-38,-18);delay_ms(5);}
  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   Set_Motor(-42,-14);
  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-44,-12);
  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-50,-6);
  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-35,35);
  else                                                              Set_Motor(-28,-28);
	

}

///**************************后退巡线**************************/
//void anti_SearchRun(void)
//{
//	//车正
//  if(D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1)   Set_Motor(-22,-22);
////右偏
//  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-45,-22);delay_ms(10);}
//  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-47,-22);delay_ms(5);}
//  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-49,-22);
//  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-51,-22);
//  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-24,24);

//	
////左偏
//  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-22,-45);delay_ms(10);}//53
//  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   {Set_Motor(-22,-47);delay_ms(5);}//58
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-22,-49);//59
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(-22,-51); //65
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(24,-24); 	
//  else                                  Set_Motor(-25,-25);
//	
//	
//}
void LIAP(void)//前进巡线放置
{
	if(F2==1&&F3==1&&F4==0&&F5==0&&F6==1&&F7==1)   Set_Motor(18,18);
	  //右偏   新八路灰度  黑 0 白 1  F7左F2右
  else if(F7==1&&F6==1&&F5==0&&F4==1&&F3==1&&F2==1)   {Set_Motor(8,28);delay_ms(5);}
  else if(F7==1&&F6==0&&F5==0&&F4==1&&F3==1&&F2==1)   Set_Motor(4,32);
  else if(F7==1&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(2,34);
  else if(F7==0&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-4,40);
  else if(F7==0&&F6==1&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-25,25);
	  //左偏
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==1&&F2==1)   {Set_Motor(28,8);delay_ms(5);}
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==0&&F2==1)   Set_Motor(32,4);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==1)   Set_Motor(34,2);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==0)   Set_Motor(40,-4);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==1&&F2==0)   Set_Motor(25,-25);

  else                                                              Set_Motor(18,18);
}
void anti_LIAP(void)//后腿巡线放置
{
	//车正
  if(D1==1&&D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1&&D8==1)        Set_Motor(-18,-18);
//右偏
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-8,-28);delay_ms(5);}
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   Set_Motor(-4,-32);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-2,-34);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(4,-40);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(25,-25);
//左偏
  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-28,-8);delay_ms(5);}
  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   Set_Motor(-32,-4);
  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-34,-2);
  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-40,4);
  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-25,25);
  else                                                              Set_Motor(-18,-18);
	
}
