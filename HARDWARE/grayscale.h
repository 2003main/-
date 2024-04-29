#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H
#include "sys.h"

/*************新一路灰度****************/
/********1是灰度灯亮,检测到白色  0是灰度灯暗,检测到黑色*********/
#define L_front         PCin(1)          //HDIO2 
#define R_front         PCin(0)           //HDIO1 

#define L_Centre        PCin(2)            //HDIO3
#define R_Centre        PFin(11)            //HDIO5  

#define L_back          PCin(3)            //HDIO4  
#define R_back          PBin(1)           //HDIO6 

//1路激光传感器模块
#define HDIO1 PCin(0)
#define HDIO2 PCin(1)
#define HDIO3 PCin(2)
#define HDIO4 PCin(3)
#define HDIO5 PFin(11)
#define HDIO6 PBin(1)
#define HDIO7 PAin(4)
#define HDIO8 PAin(5)
//8路灰度1
#define EDIO1 PFin(0)
#define EDIO2 PFin(1)
#define EDIO3 PFin(2)
#define EDIO4 PFin(4)
#define EDIO5 PFin(5)
#define EDIO6 PFin(6)
#define EDIO7 PFin(7)
#define EDIO8 PFin(8)
//8路灰度2
#define EDIO9 PEin(1)
#define EDIO10 PEin(0)
#define EDIO11 PBin(9)
#define EDIO12 PBin(8)
#define EDIO13 PBin(7)
#define EDIO14 PBin(6)
#define EDIO15 PBin(5)
#define EDIO16 PBin(4)

void HDIO_Init(void);
void eight_gray1(void);
void eight_gray2(void);
void Grayscale_Init(void);
/*****************************************
*****以下为灰度跳变计数巡线函数(需要传入巡线代码与计数次数)
******************************************/

/**********左右中一路***************/
void RL_Centre_Count(void (*d)(void),int ti);

/************左右后一路灰度****************/
void RL_Back_Count(void (*d)(void),int ti);

///****************左右前二路灰度外侧************/
void RL_Front_Count(void (*d)(void),int ti);


///**************以下为单侧灰度计数*********/

/*****************右前灰度外侧***************/
void R_Front_Count(void (*d)(void),int ti);


//左前灰度
void L_Front_Count(void (*d)(void),int ti);

/*****************右中一路灰度**************/
void R_Centre_Count(void (*d)(void),int ti);

///*****************左中一路灰度**************/
void L_Centre_Count(void (*d)(void),int ti);

void R_Back_Count(void (*d)(void),int ti);

void L_Back_Count(void (*d)(void),int ti);
	
#endif




