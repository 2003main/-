#ifndef __TIME_GO_H
#define __TIME_GO_H
#include "sys.h"
#define TIM_base_time (TIM3->CNT)

void Time_go(void (*a)(),u16 ms);
void Time_delay_ms(u16 tim);
void Stop_Time(int time);
void Time_Set(u16 ms);
void Creazy_B(void (*a)(),u16 ms);
void Creazy_T(void (*a)(void),u16 ms);
#endif
