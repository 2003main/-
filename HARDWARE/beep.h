#ifndef __BEEP_H
#define __BEEP_H 			   
#include "sys.h"	 

#define BEEP PGout(11)	// ����������IOλ��������
#define Beep Beep_one
void BEEP_Init(void);//��ʼ��		
void Beep_one(void);
#endif


