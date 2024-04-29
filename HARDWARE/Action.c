#include "Action.h"
#include "delay.h"
#include "PCA9685.h"
void sleeve_open(void)
{
  crazyMe(1,90,90,6,120);
	crazyMe(4,90,90,6,120);
}
void sleeve_close(void)
{
  crazyMe(1,30,30,6,120);
	crazyMe(4,30,30,6,120);
}
	
void sleeve_rise(void)
{
  crazyMe(5,140,70,8,120);
}
void sleeve_decline(void)
{
  crazyMe(5,70,140,8,120);
}
	

