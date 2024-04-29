#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H
#include "sys.h"

/*************��һ·�Ҷ�****************/
/********1�ǻҶȵ���,��⵽��ɫ  0�ǻҶȵư�,��⵽��ɫ*********/
#define L_front         PCin(1)          //HDIO2 
#define R_front         PCin(0)           //HDIO1 

#define L_Centre        PCin(2)            //HDIO3
#define R_Centre        PFin(11)            //HDIO5  

#define L_back          PCin(3)            //HDIO4  
#define R_back          PBin(1)           //HDIO6 

//1·���⴫����ģ��
#define HDIO1 PCin(0)
#define HDIO2 PCin(1)
#define HDIO3 PCin(2)
#define HDIO4 PCin(3)
#define HDIO5 PFin(11)
#define HDIO6 PBin(1)
#define HDIO7 PAin(4)
#define HDIO8 PAin(5)
//8·�Ҷ�1
#define EDIO1 PFin(0)
#define EDIO2 PFin(1)
#define EDIO3 PFin(2)
#define EDIO4 PFin(4)
#define EDIO5 PFin(5)
#define EDIO6 PFin(6)
#define EDIO7 PFin(7)
#define EDIO8 PFin(8)
//8·�Ҷ�2
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
*****����Ϊ�Ҷ��������Ѳ�ߺ���(��Ҫ����Ѳ�ߴ������������)
******************************************/

/**********������һ·***************/
void RL_Centre_Count(void (*d)(void),int ti);

/************���Һ�һ·�Ҷ�****************/
void RL_Back_Count(void (*d)(void),int ti);

///****************����ǰ��·�Ҷ����************/
void RL_Front_Count(void (*d)(void),int ti);


///**************����Ϊ����Ҷȼ���*********/

/*****************��ǰ�Ҷ����***************/
void R_Front_Count(void (*d)(void),int ti);


//��ǰ�Ҷ�
void L_Front_Count(void (*d)(void),int ti);

/*****************����һ·�Ҷ�**************/
void R_Centre_Count(void (*d)(void),int ti);

///*****************����һ·�Ҷ�**************/
void L_Centre_Count(void (*d)(void),int ti);

void R_Back_Count(void (*d)(void),int ti);

void L_Back_Count(void (*d)(void),int ti);
	
#endif




