#include "bsp_key.h"


void KEY_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
	/* PD7解锁 */
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR)  |= GPIO_PIN_7;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x00;
	
	//初始化按键k1
	GPIOPinTypeGPIOInput( KEY1_PORT , KEY1_PIN );
	//初始化按键k2
	GPIOPinTypeGPIOInput( KEY2_PORT , KEY2_PIN );
	//初始化按键k3
	GPIOPinTypeGPIOInput( KEY3_PORT , KEY3_PIN );
	//初始化按键k4
	GPIOPinTypeGPIOInput( KEY4_PORT , KEY4_PIN );
}
//按键中断处理函数
void Key1_Interrupt_Handler(void)
{
	if(GPIOPinRead(KEY1_PORT,KEY1_PIN)==0)
	{
		SysCtlDelay(20*SysCtlClockGet()/3000);
		if(GPIOPinRead(KEY1_PORT,KEY1_PIN)==0)
		{
			
		}
	}
}
void Key2_Interrupt_Handler(void)
{
		if(GPIOPinRead(KEY2_PORT,KEY2_PIN)==0)
	{
		SysCtlDelay(20*SysCtlClockGet()/3000);
		if(GPIOPinRead(KEY2_PORT,KEY2_PIN)==0)
		{
			
		}
	}
}
/*key1*/
void Key1_Interrupt_Config (void)
{
	GPIOIntTypeSet( KEY1_PORT,KEY1_PIN,GPIO_FALLING_EDGE );
	GPIOIntRegister( KEY1_PORT,Key1_Interrupt_Handler );
	GPIOIntEnable( KEY1_PORT,GPIO_INT_PIN_7 );
	IntEnable(INT_GPIOD);
	IntMasterEnable();
}


/*key2*/
void Key2_Interrupt_Config (void)
{
	GPIOIntTypeSet( KEY2_PORT,KEY2_PIN,GPIO_FALLING_EDGE );
	GPIOIntRegister( KEY2_PORT,Key2_Interrupt_Handler );
	GPIOIntEnable( KEY2_PORT,GPIO_INT_PIN_4 );
	IntEnable(INT_GPIOF);
	IntMasterEnable();
}

