#include "bsp_x9c104.h"
void X9c104_Init(void)
{
	SysCtlPeripheralEnable(X9c104_PERIPH);
	GPIOPinTypeGPIOOutput(X9c104_BASE,X9c104_INC_PIN|X9c104_UD_PIN|X9c104_CS_PIN);
}

void X9c104_SetR(uint8_t value)
{
	int i=0;
	X9c104_INC_H;
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	X9c104_CS_L;//启用模块
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	X9c104_UD_L;//设置电阻值改变方向为减小
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	for(i=0;i<100;i++)//电阻值清空
	{
		X9c104_INC_H;
		bsp_Delay_us(100);
		X9c104_INC_L;
		bsp_Delay_us(100);
	}
	X9c104_UD_H;//设置电阻值改变方向为增大
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	for(i=0;i<value;i++)//设置电阻值
	{
		X9c104_INC_H;
		bsp_Delay_us(100);
		X9c104_INC_L;
		bsp_Delay_us(100);
	}
	X9c104_INC_H;//储存电阻值固定住
	bsp_Delay_us(100);
	X9c104_CS_H;
	bsp_Delay_ms(20);
	bsp_Delay_us(100);
	X9c104_UD_L;
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	X9c104_INC_H;
}
void X9c104_ChangeR(uint8_t dir,uint8_t value)//dir0 R减少 dir1 R增加
{
	int i=0;
	X9c104_INC_H;
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	X9c104_CS_L;//启用模块
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	if(dir==0)
	{
		X9c104_UD_L;//设置电阻值改变方向为减小
		bsp_Delay_us(100);
		bsp_Delay_us(100);
	}
	if(dir==1)
	{
		X9c104_UD_H;//设置电阻值改变方向为增大
		bsp_Delay_us(100);
		bsp_Delay_us(100);
	}
	for(i=0;i<value;i++)
	{
		X9c104_INC_H;
		bsp_Delay_us(1);
		X9c104_INC_L;
		bsp_Delay_us(1);
	}
	X9c104_INC_H;//储存电阻值固定住
	bsp_Delay_us(100);
	X9c104_CS_H;
	bsp_Delay_ms(20);
	bsp_Delay_us(100);
	X9c104_UD_L;
	bsp_Delay_us(100);
	bsp_Delay_us(100);
	X9c104_INC_H;
}




























