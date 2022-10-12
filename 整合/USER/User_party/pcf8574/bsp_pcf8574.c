#include "bsp_pcf8574.h"
/*低四位控制继电器，高四位控制模拟开关芯片*/


uint8_t DATA=0x0000;
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
/*继电器控制函数 PF0-PF3*/
void Relay_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0xFF;
  HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_0);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3);
}
void Relay_Control(char shift,uint8_t out)
{
	switch (shift)
	{
		case RELAY_A:
			if(out==RELAY_OUT2)
			{
				GPIOPinWrite(RELAYA_BASE,RELAYA_PIN,RELAYA_PIN);
			}else if(out==RELAY_OUT1)
			{
				GPIOPinWrite(RELAYA_BASE,RELAYA_PIN,0);
			}
			break;
		case RELAY_B:
			if(out==RELAY_OUT2)
			{
				GPIOPinWrite(RELAYB_BASE,RELAYB_PIN,RELAYB_PIN);
			}else if(out==RELAY_OUT1)
			{
				GPIOPinWrite(RELAYB_BASE,RELAYB_PIN,0);
			}
			break;
		case RELAY_C:
			if(out==RELAY_OUT2)
			{
				GPIOPinWrite(RELAYC_BASE,RELAYC_PIN,RELAYC_PIN);
			}else if(out==RELAY_OUT1)
			{
				GPIOPinWrite(RELAYC_BASE,RELAYC_PIN,0);
			}
			break;
		case RELAY_D:
			if(out==RELAY_OUT2)
			{
				GPIOPinWrite(RELAYD_BASE,RELAYD_PIN,RELAYD_PIN);
			}else if(out==RELAY_OUT1)
			{
				GPIOPinWrite(RELAYD_BASE,RELAYD_PIN,0);
			}
			break;
	}
}
/*P4-ADG419,P5-ADG409A0,P6-ADG409A1,P7-ADG411*/
void Analogue_Switch(uint32_t chip,uint8_t mode)
{
	switch (chip)
	{
		case ADG419:
			if(mode==MODE_ADG419_Switch1)
			{
				DATA = DATA&0xEF;
			}else if(mode==MODE_ADG419_Switch2)
			{
				DATA = DATA|0x10;
			}break;
		case ADG409:
			if(mode==MODE_ADG409_Switch1)
			{
				DATA = DATA&0x9F;
			}else if(mode==MODE_ADG409_Switch2)
			{
				DATA = DATA&0xBF;
				DATA = DATA|0x20;
			}else if(mode==MODE_ADG409_Switch3)
			{
				DATA = DATA&0xDF;
				DATA = DATA|0x40;
			}else if(mode==MODE_ADG409_Switch4)
			{
				DATA = DATA|0x60;
			}break;
		case ADG411:
			if(mode==MODE_ADG411_ON)
			{
				DATA = DATA&0x7F;
			}else if(mode==MODE_ADG411_OFF)
			{
				DATA = DATA|0x80;
			}
	}
	PCF8574_Write(DATA);
}

