#include "TCS34725.h"
#include "delay.h"

float INTEGRATION_CYCLES_MIN = 1.0f;
float INTEGRATION_CYCLES_MAX = 256.0f;
float INTEGRATION_TIME_MS_MIN= 2.4f;
float INTEGRATION_TIME_MS_MAX =2.4 * 256.0f;


uint8_t C_Dat[8]={0};

uint32_t RGB888=0;
uint16_t RGB565=0;
uint8_t R_Dat=0,G_Dat=0,B_Dat=0;
RGB rgb;	


//读指定地址数据
uint8_t TCS34725_ReadWord(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{  
	TCS34725_IIC_start();
	TCS34725_IIC_write_byte(TCS34725_ADDRESS);
	TCS34725_IIC_Get_ack();				//接收应答	
	TCS34725_IIC_write_byte(TCS34725_CMD_BIT|ReadAddr);
	TCS34725_IIC_Get_ack();				//接收应答	
	
	TCS34725_IIC_start();
	TCS34725_IIC_write_byte(TCS34725_ADDRESS+1);
	TCS34725_IIC_Get_ack();				//接收应答	
	while(NumByteToRead)  
  {
		*pBuffer = TCS34725_IIC_read_byte();
		if(NumByteToRead == 1)
    {
				/* Disable Acknowledgement */
				TCS34725_IIC_NACK();

				/* Send STOP Condition */
				TCS34725_IIC_stop();


		}
		else
		{
			TCS34725_IIC_ACK();
		}
		 pBuffer++; 
		 NumByteToRead--; 
	}
	return 0;
}
uint8_t TCS34725_WriteByte(uint8_t addr,uint8_t data) 
{
		TCS34725_IIC_start();
		TCS34725_IIC_write_byte(TCS34725_ADDRESS);
		TCS34725_IIC_Get_ack();				//接收应答	
		TCS34725_IIC_write_byte(TCS34725_CMD_BIT|addr);
		TCS34725_IIC_Get_ack();				//接收应答	
		
		TCS34725_IIC_write_byte(data);
		TCS34725_IIC_Get_ack();				//接收应答		
		return 0;
}
//初始化
uint8_t TCS34725_Init(void)  
{
		uint8_t ID = 0;
		TCS34725_ReadWord(&ID, TCS34725_ID, 1);
		if(ID != 0x44 && ID != 0x4D)
		{
				return 1;
		}
		TCS34725_WriteByte(TCS34725_CMD_Read_Byte,TCS34725_ENABLE_AIEN|TCS34725_ENABLE_AEN|TCS34725_ENABLE_PON);
		TCS34725_WriteByte(TCS34725_PERS,TCS34725_PERS_NONE);
		TCS34725_WriteByte(TCS34725_CONTROL,TCS34725_GAIN_60X);
		return 0;
}

void integrationTime(float ms) // 2.4 - 614.4 ms
{
		uint8_t data;
		if (ms < INTEGRATION_TIME_MS_MIN) ms = INTEGRATION_TIME_MS_MIN;
		if (ms > INTEGRATION_TIME_MS_MAX) ms = INTEGRATION_TIME_MS_MAX;
		 data = (uint8_t)(256.f - ms / INTEGRATION_TIME_MS_MIN);
		TCS34725_WriteByte(TCS34725_ATIME,data);	

}

RGB TCS34725_Get_RGBData(void)
{
	  RGB temp;
		uint8_t STATUS_AINT=0;

		while(STATUS_AINT!=(TCS34725_STATUS_AINT|TCS34725_STATUS_AVALID))
		{
				TCS34725_ReadWord(&STATUS_AINT,TCS34725_STATUS,1);
		}

		TCS34725_ReadWord(C_Dat,TCS34725_CDATAL | TCS34725_CMD_Read_Word,8);

	
		temp.C = (uint16_t)C_Dat[1]<<8|C_Dat[0];
		temp.R = (uint16_t)C_Dat[3]<<8|C_Dat[2];
		temp.G = (uint16_t)C_Dat[5]<<8|C_Dat[4];
		temp.B = (uint16_t)C_Dat[7]<<8|C_Dat[6];

		return temp;
}
/******************************************************************************
function:   Convert raw RGB values to RGB888 format
parameter	:
     rgb    : RGBC Numerical value
******************************************************************************/

uint32_t TCS34725_GetRGB888(RGB rgb)
{
    float i=1;
    //Limit data range
    if(rgb.R >= rgb.G && rgb.R >= rgb.B){ 
        i = rgb.R / 255 + 1;
    }
    else if(rgb.G >= rgb.R && rgb.G >= rgb.B){ 
        i = rgb.G / 255 + 1;
    }
    else if(rgb.B >=  rgb.G && rgb.B >= rgb.R){ 
        i = rgb.B / 255 + 1;  
    }
    if(i!=0)
    {
        rgb.R = (rgb.R) / i;
        rgb.G = (rgb.G) / i;
        rgb.B = (rgb.B) / i;
    }
    //Amplify data differences
    /*Please don't try to make the data negative, 
        unless you don't change the data type*/
    if(rgb.R > 30)
        rgb.R = rgb.R - 30;
    if(rgb.G > 30)
        rgb.G = rgb.G - 30;
    if(rgb.B > 30)
        rgb.B = rgb.B - 30;
    rgb.R = rgb.R * 255 / 225;
    rgb.G = rgb.G * 255 / 225;
    rgb.B = rgb.B * 255 / 225;
    
    if(rgb.R>255)
           rgb.R = 255; 
    if(rgb.G>255)
           rgb.G = 255; 
    if(rgb.B>255)
           rgb.B = 255; 
    return (rgb.R << 16) | (rgb.G << 8) | (rgb.B);
}
/******************************************************************************
function:   Convert raw RGB values to RGB565 format
parameter	:
     rgb    : RGBC Numerical value
******************************************************************************/
uint16_t TCS34725_GetRGB565(RGB rgb)
{
    float i=1;
    //Limit data range
    if(rgb.R >= rgb.G && rgb.R >= rgb.B){ 
        i = rgb.R / 255 + 1;
    }
    else if(rgb.G >= rgb.R && rgb.G >= rgb.B){ 
        i = rgb.G / 255 + 1;
    }
    else if(rgb.B >=  rgb.G && rgb.B >= rgb.R){ 
        i = rgb.B / 255 + 1;  
    }
    if(i!=0){
        rgb.R = (rgb.R) / i;
        rgb.G = (rgb.G) / i;
        rgb.B = (rgb.B) / i;
    }
    if(rgb.R > 30)
        rgb.R = rgb.R - 30;
    if(rgb.G > 30)
        rgb.G = rgb.G - 30;
    if(rgb.B > 30)
        rgb.B = rgb.B - 30;
    rgb.R = rgb.R * 255 / 225;
    rgb.G = rgb.G * 255 / 225;
    rgb.B = rgb.B * 255 / 225;
    
    if(rgb.R>255)
           rgb.R = 255; 
    if(rgb.G>255)
           rgb.G = 255; 
    if(rgb.B>255)
           rgb.B = 255; 
    return (rgb.R << 11) | (rgb.G << 5) | (rgb.B);
}
void Data_Processing(void)
{
	R_Dat=(RGB888>>16);
	G_Dat=(RGB888>>8) & 0xff;
	B_Dat=(RGB888) & 0xff;
}


