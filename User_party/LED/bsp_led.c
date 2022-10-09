#include	"bsp_led.h"



void LED_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	//PF0 解锁
	
		HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0xFF;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0; 
		
	//初始化LED
	
	GPIOPinTypeGPIOOutput( LED1_PORT , LED1_PIN );
	GPIOPinTypeGPIOOutput( LED2_PORT , LED2_PIN );
	GPIOPinTypeGPIOOutput( LED3_PORT , LED3_PIN );

	//LED1 置高位
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	
}

