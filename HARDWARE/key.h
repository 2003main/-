#ifndef __KEY_H
#define __KEY_H 			   
#include "sys.h"	 

/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/

#define KEY1 		PGin(15)   	
#define KEY2 		PBin(3)	
#define KEY3 		PGin(10)		
#define KEY4 		PGin(13)		

#define KEY1_PRES 	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY3_PRES   4

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif

