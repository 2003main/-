#include "work.h"
#include "grayscale.h"
#include "TB6612.h"  
#include "gray_go.h"
#include "time_go.h"
#include "sixe_angle.h"
#include "PCA9685.h"
#include "TCS34725.h"
#include "bsys.h"//work.c����Ķ�������bsys.h��
#include "delay.h"
#include "beep.h"
#include "oled.h"
#include "IM948_TurnAngle.h"
int32_t i;
int32_t now_color;                 //���浱ǰʶ�����ɫ
int32_t last_color;                //������һ��ʶ�����ɫ����������������һcase_three
int32_t now_position=0;              //���浱ǰ�����ĸ�·����Ĭ���ں�ɫ·����
int32_t last_position;
uint8_t a[]={1,1,1};        //����һ����Ƿ�ȥ��������·��
uint8_t wukuai[]={1,0,1,0,1};    //����һ���·�����Ƿ������
int32_t color[]={0,45,90,-45,-90}; //����ɫ��Ӧ�ĽǶ�
int32_t anti_color[]={175,-135,-90,135,90}; //����ɫ��Ӧ�ķ���Ƕ�
int32_t color_distribution[]={5,5,5,5,5}; //�������ɫ����
int32_t color_residuum[]={0,0,0,0,0}; //�����ʣ��δ������
int32_t hozhua[]={hozhua_A,hozhua_B,hozhua_C,hozhua_D,hozhua_E}; //����ɫ��Ӧ�ĽǶ�



/**************************************************************************
�������ܣ������ʼ������
��ڲ�������
�� �� ֵ����
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
�������ܣ���������
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void work(void)
{
	Go_Centre();
	task1();
  task2(); 	
}
/**************************************************************************
�������ܣ��ӿ�ʼ���ߵ����ĵ�
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void Go_Centre(void)
{
	L_Centre_Count(SearchRun,8);
}

/**************************************************************************
�������ܣ�����һ����
��ڲ�������
�� �� ֵ����
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
		Time_delay_ms(500);//ʱ����Լ�С
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
�������ܣ����������
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void task2(void)
{
	int32_t a[]={-45,42};//Ҫ�޸�
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
			//time_goǰ��һ�ξ���
			Car_TurnToAngle4(130);
			Time_go(Car_Advance30,600);
			//time_go����һ�ξ���
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
�������ܣ�����һ����ɫ���뵱ǰ��ʱ��Ӧ��ɫ��ͬʱ���õķ���
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void case_one(void)
{	
	//crazyMe(qianzhua_you,90,0,5,80);      //ץס���
	//crazyMe(qianzhua_zuo,90,180,5,80);
	L_Front_Count(LIAP,2);
	Time_go(Car_Retreat28,120);
//	crazyMe(qianzhua_you,0,90,5,80);      //�ſ����
//	crazyMe(qianzhua_zuo,180,90,5,80);
	wukuai[now_color]=0;
	L_Centre_Count(anti_SearchRun,6);    //�˻ص�����
	F_adjust_pose();                     //����λ��
}

/**************************************************************************
�������ܣ�����һ����ɫ���뵱ǰ��ʱ��Ӧ��ɫ����ͬʱ��û������赲ʱ���õķ���
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void case_two(void)
{
	catch_it();                         //�����
	L_Centre_Count(anti_SearchRun,4); //�˻ص�����
	F_adjust_pose();                     //����λ��
	Car_TurnToAngle4(color[now_color]);//ת��Ŀ��Ƕ�
	F_adjust_pose();                     //����λ��
	now_position=now_color;
	L_Back_Count(LIAP,2);       //����������
	L_Front_Count(LIAP,4);       //����������
	//��Time_go����
	Time_go(Car_Retreat28,180);
	crazyMe(daduoji,90,90,5,80);        //�½�
	crazyMe(taotong_1,90,90,5,80);      //�ſ����
	crazyMe(taotong_2,90,90,5,80);
	crazyMe(daduoji,90,40,5,80);        //����
	wukuai[now_color]=0;
	L_Centre_Count(anti_SearchRun,6); //�˻ص�����
	F_adjust_pose();                   //����λ��
}

/**************************************************************************
�������ܣ�����һ����ɫ���뵱ǰ��ʱ��Ӧ��ɫ����ͬʱ��������赲ʱ���õķ���
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void case_three(void)
{
	catch_it();                            //�����
	L_Centre_Count(anti_SearchRun,4);    //�˻ص�����
	Time_go(Car_Advance30,60);         //����λ��
	Car_TurnToAngle4(color[now_color]);   //ת��Ŀ��Ƕ�
	Time_go(Car_Advance30,60);                   //����λ��
	now_position=now_color;
	L_Front_Count(LIAP,2);          //�����谭���ǰ
	last_color=now_color;                 
	color_discrimination();               //ʶ���谭������ɫ��������now_color��ֵ
	color_distribution_one();
	if((last_color==green&&now_color==blue&&i==0)||(last_color==blue&&now_color==green&&i==0))
	{
		crazyMe(qianzhua_you,90,0,5,80);      //ץס�谭���
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Back_Count(anti_SearchRun,8); 
		crazyMe(hozhua_A,150,150,5,80);
		crazyMe(hozhua_B,30,30,5,80);
		L_Centre_Count(SearchRun,4);     //�˻ص�����
		B_adjust_pose();                  //����λ��
		Car_TurnToAngle4(color[now_color]);   //ת��Ŀ��Ƕȣ��谭����·���ϣ�
		B_adjust_pose();                           //����λ��
		last_position=now_color; 
		now_position=now_color;
		L_Back_Count(LIAP,2);           //����������
		L_Front_Count(LIAP,4);           //����������
		//��time_go ����
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);       //�ſ��谭���
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,6);     //�˻ص�����
		F_adjust_pose();                         //����λ��
		Car_TurnToAngle4(color[last_color]);   //ת��Ŀ��Ƕ�
		F_adjust_pose();                         //����λ��
		now_position=last_color;
		now_color=last_color;
		L_Back_Count(LIAP,2);           //����������
		L_Front_Count(LIAP,4);           //����������
		Time_go(Car_Retreat28,150);
		crazyMe(daduoji,40,90,5,80);            //�½�
		crazyMe(taotong_1,90,90,5,80);          //�ſ����
		crazyMe(taotong_2,90,90,5,80);
		crazyMe(daduoji,90,40,5,80);           //����
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,2);     //�˻�
		crazyMe(hozhua_A,90,90,5,80);
		crazyMe(hozhua_B,90,90,5,80);
		//Time_go����һ�ξ���
		Time_go(Car_Advance30,300);
		Car_TurnToAngle4(-color[now_position]);   //ת��Ŀ��Ƕ�
		L_Front_Count(SearchRun,2);
		color_discrimination();
		now_position=last_position;
		color_distribution_one(); 
		crazyMe(qianzhua_you,90,0,5,80);   //ץס�谭���   
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Centre_Count(SearchRun,4);
		B_adjust_pose();                       //����λ��
		Car_TurnToAngle4(color[now_color]);   //ת��Ŀ��Ƕ�
		B_adjust_pose();                       //����λ��
		now_position=now_color;
		L_Back_Count(LIAP,2);           //����������
		L_Front_Count(LIAP,4);           //����������
		//time_go����
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);     //�ſ��谭���  
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		L_Centre_Count(anti_SearchRun,6); //�˻ص�����
		F_adjust_pose();                 //����λ��
		i=i+2;
	}
	else
	{
		crazyMe(qianzhua_you,90,0,5,80);       //ץס�谭���
		crazyMe(qianzhua_zuo,90,180,5,80);
		L_Centre_Count(anti_SearchRun,4);     //�˻ص�����
		F_adjust_pose();                      //����λ��
		Car_TurnToAngle4(color[now_color]);    //ת��Ŀ��Ƕȣ��谭����·���ϣ�
	  F_adjust_pose();                         //����λ��
		now_position=now_color;
		L_Back_Count(LIAP,2);           //����������
		L_Front_Count(LIAP,4);           //����������
		//time_go����
		Time_go(Car_Retreat28,150);
		crazyMe(qianzhua_you,0,90,5,80);       //�ſ��谭���
		crazyMe(qianzhua_zuo,180,90,5,80);
		wukuai[now_color]=0;
		
		L_Centre_Count(anti_SearchRun,6);     //�˻ص�����
		F_adjust_pose();                         //����λ��
		Car_TurnToAngle4(color[last_color]);   //ת��Ŀ��Ƕ�
		F_adjust_pose();                        //����λ��
		now_position=now_color;
		L_Back_Count(LIAP,2);           //����������
		L_Front_Count(LIAP,4);           //����������
		Time_go(Car_Retreat28,150);
		crazyMe(daduoji,90,90,5,80);            //�½�
		crazyMe(taotong_1,90,90,5,80);          //�ſ����
		crazyMe(taotong_2,90,90,5,80);          //�ſ����
		crazyMe(daduoji,40,40,5,80);        
		wukuai[last_color]=0;
		L_Centre_Count(anti_SearchRun,6); //�˻ص�����
		F_adjust_pose();
		i++;
	}

}

/**************************************************************************
�������ܣ����Ĵ�������̬��ʹ���ں����ϣ���С��ʹС������
��ڲ�������
�� �� ֵ����
**************************************************************************/
void F_adjust_pose(void)
{
  Time_go(Car_Advance30,110);
}
/**************************************************************************
�������ܣ����Ĵ�������̬��ʹ���ں����ϣ���С��ʹС������
��ڲ�������
�� �� ֵ����
**************************************************************************/
void B_adjust_pose(void)
{
  Time_go(Car_Retreat30,110);
}

/**************************************************************************
�������ܣ������е���Ͳ��
��ڲ�������
�� �� ֵ����
**************************************************************************/
void catch_it(void)
{
	//����һС�ξ��룬û��Time_go,��Ҫ����
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,90);
	crazyMe(taotong_1,90,90,5,80);      //dakaitaotong
	crazyMe(taotong_2,90,90,5,80);
	crazyMe(daduoji,40,90,5,80);        //�½�
	crazyMe(taotong_1,30,30,5,80);      //��ס���
	crazyMe(taotong_2,30,30,5,80);
	crazyMe(daduoji,90,40,5,80);        //����
}

/**************************************************************************
�������ܣ�����Ͳ����һ����������½���һ�����е���Ͳ��
��ڲ�������
�� �� ֵ����
**************************************************************************/
void catch_it2(void)
{
	//����һС�ξ��룬û��Time_go,��Ҫ����
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,80);
	crazyMe(daduoji,40,75,6,120);        //�½�                     ��Ϊû�н��ʵ�ʣ�Ҫ�Լ�д
	crazyMe(taotong_1,90,90,6,120);      //����Ͳ
	crazyMe(taotong_2,90,90,6,120);
	crazyMe(daduoji,75,90,6,120);        //�½�        
	crazyMe(taotong_1,30,30,5,80);      //��ס���
	crazyMe(taotong_2,30,30,5,80);
	crazyMe(daduoji,90,40,5,80);        //����
}

/**************************************************************************
�������ܣ���������Ͳ�Ϸ�����
��ڲ�������
�� �� ֵ����
**************************************************************************/
void release_it(void)
{
		//����һС�ξ��룬û��Time_go,��Ҫ����
	crazyMe(qianzhua_zuo,90,180,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,90,0,6,120);//YOUQIAN 

	//����һС�ξ��룬û��Time_go,��Ҫ����                        ��Ϊû�н��ʵ�ʣ�Ҫ�Լ�д
	Time_go(Car_Retreat28,100);
	crazyMe(qianzhua_zuo,180,90,6,120); //ZUOQIAN
	crazyMe(qianzhua_you,0,90,6,120);//YOUQIAN 
	Time_go(Car_Retreat28,80);
	crazyMe(daduoji,40,68,5,80);        //�½�
	crazyMe(taotong_1,90,90,5,80);      
	crazyMe(taotong_2,90,90,5,80);
	//����һС�ξ��룬û��Time_go,��Ҫ����
  Time_go(Car_Retreat28,10);
	crazyMe(daduoji,68,90,5,80);        //�½�
	crazyMe(taotong_1,20,20,5,80);      
	crazyMe(taotong_2,20,20,5,80);
	crazyMe(taotong_1,90,90,5,80);      
	crazyMe(taotong_2,90,90,5,80);
}


/**************************************************************************
�������ܣ�������У����ɫ����
��ڲ��������α���x
�� �� ֵ����
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
�������ܣ�ʶ����ɫ
��ڲ�������
�� �� ֵ����
**************************************************************************/ 
void color_discrimination(void)
{

	  rgb=TCS34725_Get_RGBData();
		RGB888=TCS34725_GetRGB888(rgb);
		RGB565=TCS34725_GetRGB565(rgb);
		Dis_Temp();
		if(R_Dat>200&&R_Dat>(G_Dat+B_Dat))                                                         {now_color=red;beep(3);}  //��
	  else if(2*G_Dat>(2*R_Dat+B_Dat)&&G_Dat>150)                                                {now_color=green;beep(1);}//��
    else if(B_Dat>160&&G_Dat<230&&2*B_Dat>(R_Dat+G_Dat))                                       {now_color=blue;beep(5);} //��
	  else if((G_Dat-R_Dat)>30&&(G_Dat-R_Dat)<60&&R_Dat>120&&G_Dat>150&&(R_Dat+B_Dat)>G_Dat)     {now_color=black;beep(4);}//��
    else if(R_Dat>200&&G_Dat>200&&G_Dat>R_Dat)             
                                 {now_color=white;beep(2);}//�� 
}
/**************************************************************************
�������ܣ�����һ��ȷ���������ɫ�������
��ڲ�������
�� �� ֵ����
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
�������ܣ��������ȷ���������ɫ�������
��ڲ�������
�� �� ֵ����
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
�������ܣ������ץ��麯��
��ڲ�������
�� �� ֵ����
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
�������ܣ����������麯��
��ڲ�����bΪ�ڼ���ѭ�� b=0~1 ,numberΪ���ĸ�λ�õ���� number={A B C D E};
�� �� ֵ����
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
�������ܣ�����������ŵ�Ŀ��λ��
��ڲ�����numberΪ���ĸ�λ�õ���� number={A B C D E};
�� �� ֵ����
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

/******************ת��ǰͣ�£�ʹС������***************/
void stop_time(int time)
{
   Time_go(Car_Stop,time);
}
