#include "bsp_dac.h"
void DAC_Config(void)//SSI0Clk PA2 /SSI0Fss PA3 /load PA4 /SSI0Tx PA5
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(GPIO_PA2_SSI0CLK); //分别开启GPIO引脚对应的功能
  GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_4);
  GPIOPinConfigure(GPIO_PA5_SSI0TX);
	GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5);
	SSIConfigSetExpClk(SSI0_BASE,SysCtlClockGet(),SSI_FRF_MOTO_MODE_3,SSI_MODE_MASTER , 2000000,16);
	SSIEnable(SSI0_BASE);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_PIN_3);
	
	SysCtlDelay(SysCtlClockGet()/300000);
}

void DAC_SendData(uint16_t n)
{
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
	SysCtlDelay(SysCtlClockGet()/300000);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0);
	SysCtlDelay(SysCtlClockGet()/300000);
	SSIDataPut(SSI0_BASE,0x3000+n);
	SysCtlDelay(SysCtlClockGet()/300000);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,GPIO_PIN_3);
	SysCtlDelay(SysCtlClockGet()/300000);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,0);
	SysCtlDelay(SysCtlClockGet()/300000);
}
