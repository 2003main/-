#include "gray_go.h"
#include "delay.h"
#include "TB6612.h"
/*�°�·�Ҷ�*/
/**************************ǰ��Ѳ��**************************/
void SearchRun(void)
{
	if(F2==1&&F3==1&&F4==0&&F5==0&&F6==1&&F7==1)   Set_Motor(28,28);
	  //��ƫ   �°�·�Ҷ�  �� 0 �� 1  F7��F2��
  else if(F7==1&&F6==1&&F5==0&&F4==1&&F3==1&&F2==1)   {Set_Motor(18,38);delay_ms(5);}
  else if(F7==1&&F6==0&&F5==0&&F4==1&&F3==1&&F2==1)   Set_Motor(14,42);
  else if(F7==1&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(12,44);
  else if(F7==0&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(6,50);
  else if(F7==0&&F6==1&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-35,35);
	  //��ƫ
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==1&&F2==1)   {Set_Motor(38,18);delay_ms(5);}
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==0&&F2==1)   Set_Motor(42,14);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==1)   Set_Motor(44,12);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==0)   Set_Motor(50,6);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==1&&F2==0)   Set_Motor(35,-35);

  else                                                              Set_Motor(28,28);
}

/**************************����Ѳ��**************************/
void anti_SearchRun(void)
{
	//����
  if(D1==1&&D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1&&D8==1)        Set_Motor(-28,-28);
//��ƫ
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-18,-38);delay_ms(5);}
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   Set_Motor(-14,-42);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-12,-44);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(-6,-50);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(35,-35);
//��ƫ
  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-38,-18);delay_ms(5);}
  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   Set_Motor(-42,-14);
  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-44,-12);
  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-50,-6);
  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-35,35);
  else                                                              Set_Motor(-28,-28);
	

}

///**************************����Ѳ��**************************/
//void anti_SearchRun(void)
//{
//	//����
//  if(D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1)   Set_Motor(-22,-22);
////��ƫ
//  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-45,-22);delay_ms(10);}
//  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-47,-22);delay_ms(5);}
//  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-49,-22);
//  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-51,-22);
//  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-24,24);

//	
////��ƫ
//  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-22,-45);delay_ms(10);}//53
//  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   {Set_Motor(-22,-47);delay_ms(5);}//58
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-22,-49);//59
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(-22,-51); //65
//  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(24,-24); 	
//  else                                  Set_Motor(-25,-25);
//	
//	
//}
void LIAP(void)//ǰ��Ѳ�߷���
{
	if(F2==1&&F3==1&&F4==0&&F5==0&&F6==1&&F7==1)   Set_Motor(18,18);
	  //��ƫ   �°�·�Ҷ�  �� 0 �� 1  F7��F2��
  else if(F7==1&&F6==1&&F5==0&&F4==1&&F3==1&&F2==1)   {Set_Motor(8,28);delay_ms(5);}
  else if(F7==1&&F6==0&&F5==0&&F4==1&&F3==1&&F2==1)   Set_Motor(4,32);
  else if(F7==1&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(2,34);
  else if(F7==0&&F6==0&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-4,40);
  else if(F7==0&&F6==1&&F5==1&&F4==1&&F3==1&&F2==1)   Set_Motor(-25,25);
	  //��ƫ
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==1&&F2==1)   {Set_Motor(28,8);delay_ms(5);}
  else if(F7==1&&F6==1&&F5==1&&F4==0&&F3==0&&F2==1)   Set_Motor(32,4);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==1)   Set_Motor(34,2);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==0&&F2==0)   Set_Motor(40,-4);
  else if(F7==1&&F6==1&&F5==1&&F4==1&&F3==1&&F2==0)   Set_Motor(25,-25);

  else                                                              Set_Motor(18,18);
}
void anti_LIAP(void)//����Ѳ�߷���
{
	//����
  if(D1==1&&D2==1&&D3==1&&D4==0&&D5==0&&D6==1&&D7==1&&D8==1)        Set_Motor(-18,-18);
//��ƫ
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==1&&D7==1)   {Set_Motor(-8,-28);delay_ms(5);}
  else if(D2==1&&D3==1&&D4==1&&D5==0&&D6==0&&D7==1)   Set_Motor(-4,-32);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==1)   Set_Motor(-2,-34);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==0&&D7==0)   Set_Motor(4,-40);
  else if(D2==1&&D3==1&&D4==1&&D5==1&&D6==1&&D7==0)   Set_Motor(25,-25);
//��ƫ
  else if(D2==1&&D3==1&&D4==0&&D5==1&&D6==1&&D7==1)   {Set_Motor(-28,-8);delay_ms(5);}
  else if(D2==1&&D3==0&&D4==0&&D5==1&&D6==1&&D7==1)   Set_Motor(-32,-4);
  else if(D2==1&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-34,-2);
  else if(D2==0&&D3==0&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-40,4);
  else if(D2==0&&D3==1&&D4==1&&D5==1&&D6==1&&D7==1)   Set_Motor(-25,25);
  else                                                              Set_Motor(-18,-18);
	
}
