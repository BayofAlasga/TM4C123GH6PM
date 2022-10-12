#include "bsp_include.h"
// 重写fputc函数以支持printf功能
int fputc(int ch, FILE *f)
{
//    UARTCharPut(UART1_BASE,(unsigned char)ch);	//这里填写的基址(UART0_BASE)不同，则printf用的串口不同
		UARTCharPut(UART0_BASE,(unsigned char)ch);
    return ch;
}
int main()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	USART0_Config();
//	DAC_Config();
//	DAC_SendData(0x4D2);
//	USART1_Config();
	
//	X9c104_Init();
//	X9c104_SetR(30);
//	PCF8574_Init();
//	PCF8574_Write(0x01);

//	Relay_Init();
//	Relay_Control(RELAY_A,RELAY_OUT1);
//	Relay_Control(RELAY_B,RELAY_OUT1);
//	Relay_Control(RELAY_C,RELAY_OUT2);
//	Relay_Control(RELAY_D,RELAY_OUT2);

//	Analogue_Switch(ADG419,MODE_ADG419_Switch2);
//	bsp_InitADS1256();
//	ADS1256_CfgADC(ADS1256_GAIN_1,ADS1256_15000SPS);
	ILI9341_init(BLACK);
	FFT_ADC1_Config();
	FFT_Timer1_Congfig();
	while (1)
	{
//		ADCProcessorTrigger(ADC0_BASE,2);
//		printf("%.4f\n",ADS1256_ReadAdc(2));
//		bsp_Delay_ms(1000);
//			printf("%.4f\n",ADS1256_ReadAdc(0));
	}
}




