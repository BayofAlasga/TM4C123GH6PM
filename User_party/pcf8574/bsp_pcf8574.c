#include "bsp_pcf8574.h"


static void PCF8574_Start(void)
{
	SDA_OUT;
	SCL_H;bsp_Delay_us(1);
	SDA_H;bsp_Delay_us(1);
	bsp_Delay_us(5);
	SDA_L;bsp_Delay_us(1);
	bsp_Delay_us(5);
	SCL_L;bsp_Delay_us(1);
}

static void PCF8574_Stop(void)
{
	SDA_OUT;
	SCL_H;bsp_Delay_us(1);
	SDA_L;bsp_Delay_us(1);
	bsp_Delay_us(5);
	SDA_H;bsp_Delay_us(1);
	bsp_Delay_us(5);
}
static void PCF8574_SendData(uint8_t data)
{
	SDA_OUT;
	SCL_L;bsp_Delay_us(1);
	int i;
	for(i=0;i<8;i++)
	{
			if((data&0x80))
		{
			SDA_H;bsp_Delay_us(1);
		}else
		{
			SDA_L;bsp_Delay_us(1);
		}
		data=data<<1;
		bsp_Delay_us(5);
		SCL_H;bsp_Delay_us(1);
		bsp_Delay_us(5);
		SCL_L;bsp_Delay_us(1);
	}
}

static void PCF8574_RecData(void)
{
	SCL_L;bsp_Delay_us(1);
	SDA_H;bsp_Delay_us(1);
	SDA_IN;
	bsp_Delay_us(5);
	SCL_H;
	while(GPIOPinRead(PCF8574_BASE,SDA_PIN)!=0)
	{
		;;
	}
}

void PCF8574_Init(void)
{
	SysCtlPeripheralEnable(PCF8574_PERIPH);
	GPIOPinTypeGPIOOutput(PCF8574_BASE,SCL_PIN|SDA_PIN);
}
//PCF8574输出八位数据 最低位P0，最高位P7
void PCF8574_Write(uint8_t data)
{
	PCF8574_Start();
	PCF8574_SendData(PCF8574_Address);
	PCF8574_RecData();
	PCF8574_SendData(data);
	PCF8574_RecData();
	PCF8574_Stop();
}
