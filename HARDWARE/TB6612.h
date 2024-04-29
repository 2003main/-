#ifndef __TB6612_H 
#define __TB6612_H 
#include "sys.h"
#define M1 PFout(15)
#define M2 PFout(14)
#define M3 PGout(1)
#define M4 PGout(0)
#define M5 PCout(5)
#define M6 PCout(4)
#define M7 PEout(7)
#define M8 PEout(8)

void MOTOR_Init(void);

void TB6612_Init(int arr, int psc);
void SetPWM(int pwm);
void motor_mode(void);
void Set_Motor(s32 leftspeed,s32 rightseepd);
void Move_stop(void);

void Car_Advance35(void);
void Car_Advance30(void);
void Car_Advance35pian(void);
void Car_Advance28(void);
void Car_Advance20(void);
void Car_Advance17(void);
void Car_Retreat35(void);
void Car_Retreat35_two(void);
void Car_Retreat28(void);
void Car_Retreat20(void);
void Car_Retreat30(void);
void Car_Stop(void);
#endif //定义完毕，或者引用过头文件到达这一步
