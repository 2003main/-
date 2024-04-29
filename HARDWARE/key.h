#ifndef __KEY_H
#define __KEY_H 			   
#include "sys.h"	 

/*下面方式是通过位带操作方式读取IO*/

#define KEY1 		PGin(15)   	
#define KEY2 		PBin(3)	
#define KEY3 		PGin(10)		
#define KEY4 		PGin(13)		

#define KEY1_PRES 	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY3_PRES   4

void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	

#endif

