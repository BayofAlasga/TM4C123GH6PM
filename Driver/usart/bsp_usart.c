#include "bsp_usart.h"

void Int_Usart0_Handle(void)
{
	while(!UARTIntStatus(UART0_BASE,1));
	uint8_t data;
	UARTIntClear(UART0_BASE, UART_INT_RX);
	while(!UARTCharsAvail(UART0_BASE));
	data=UARTCharGet(UART0_BASE);
	UARTCharPut(UART0_BASE,data);
}
void USART0_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
//	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);	// ±÷”16MHZ
//	UARTStdioConfig(0,115200,UART_CLOCK_SYSTEM);
	UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),115200,UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
	UARTIntRegister(UART0_BASE,Int_Usart0_Handle);
	IntPrioritySet(INT_UART0,0);
	UARTIntEnable(UART0_BASE, UART_INT_RX);
	UARTEnable(UART0_BASE);
}

void Int_Usart1_Handle(void)
{
	while(!UARTIntStatus(UART1_BASE,1));
	uint8_t data;
	UARTIntClear(UART1_BASE, UART_INT_RX);
	while(!UARTCharsAvail(UART1_BASE));
	data=UARTCharGet(UART1_BASE);
	UARTCharPut(UART1_BASE,data);
}
void USART1_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	
	GPIOPinConfigure(GPIO_PC4_U1RX);
  GPIOPinConfigure(GPIO_PC5_U1TX);
  GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	
//	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);	// ±÷”16MHZ
//	UARTStdioConfig(0,115200,UART_CLOCK_SYSTEM);
	UARTConfigSetExpClk(UART1_BASE,SysCtlClockGet(),115200,UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
	UARTIntRegister(UART1_BASE,Int_Usart1_Handle);
	IntPrioritySet(INT_UART1,0);
	UARTIntEnable(UART1_BASE, UART_INT_RX);
	UARTEnable(UART1_BASE);
}
