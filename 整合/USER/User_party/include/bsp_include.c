#include "bsp_include.h"


void bsp_Delay_us(uint32_t us)
{
	SysCtlDelay(us*SysCtlClockGet()/3000000);
}
void bsp_Delay_ms(uint32_t ms)
{
	SysCtlDelay(SysCtlClockGet()/3000*ms);
}
