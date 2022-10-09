#include "bsp_interrupt.h"

/*所有GPIO中断初始化*/
void Interrupt_config(void)
{
	Key1_Interrupt_Config();
	Key2_Interrupt_Config();
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
/*key2*/
void Key2_Interrupt_Config (void)
{

	GPIOIntTypeSet( KEY2_PORT,KEY2_PIN,GPIO_FALLING_EDGE );
	GPIOIntRegister( KEY2_PORT,Key2_Interrupt_Handler );
	GPIOIntEnable( KEY2_PORT,GPIO_INT_PIN_4 );
	IntEnable(INT_GPIOF);
	IntMasterEnable();
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

/*通用GPIO中断初始化
void GPIO_Interrupt_Config (uint32_t GPIOX_PORT,uint32_t GPIOX_PIN,uint32_t GPIO_INT_PIN_X,uint32_t INT_GPIOX,void (*pfnIntHandler)(void))
{
	GPIOIntTypeSet( GPIOX_PORT,GPIOX_PIN,GPIO_FALLING_EDGE );
	GPIOIntRegister( GPIOX_PORT,pfnIntHandler );
	GPIOIntEnable( GPIOX_PORT,GPIO_INT_PIN_X );
	IntEnable(INT_GPIOX);
	IntMasterEnable();
}
*/

/*中断函数模板
void pfnIntHandler(void)
{
	GPIOIntClear(GPIOX_PORT,GPIO_INT_PIN_X);
}
*/
