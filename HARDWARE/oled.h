#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------测试LED端口定义---------------- 

#define LED_ON GPIO_ResetBits(GPIOC,GPIO_Pin_12)
#define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_12)

//-----------------OLED端口定义---------------- 

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_7)//SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOG,GPIO_Pin_7)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_6)//SDA
#define OLED_SDA_Set() GPIO_SetBits(GPIOG,GPIO_Pin_6)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_5)//RES
#define OLED_RES_Set() GPIO_SetBits(GPIOG,GPIO_Pin_5)

#define OLED_DC_Clr()  GPIO_ResetBits(GPIOG,GPIO_Pin_4)//DC
#define OLED_DC_Set()  GPIO_SetBits(GPIOG,GPIO_Pin_4)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_1)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_1)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_printf( uint8_t *P_data,uint8_t Location,uint16_t temp_data,uint8_t Length);
void Dis_Temp(void);
void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_ShowChar6x8(u8 x,u8 y,u8 chr,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_ScrollDisplay(u8 num,u8 space,u8 mode);

void OLED_Init(void);

#endif

