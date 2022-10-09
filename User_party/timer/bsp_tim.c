#include "bsp_tim.h"
#define LOAD  65535
uint32_t TIMER_TICK[4],time=0,hightime=0;
double rate=0.0;
uint32_t freq=0;
uint16_t t=0;
uint16_t overflow=0;
int k=0,m=2;

void Timer0AIntHandler(void)
{
	TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);

}

void Timer1A_Int_Handler(void)
{
	TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	
}

void Timer0A_Congfig(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	//周期循环模式
	TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC);
	//计时时间配置
	TimerLoadSet(TIMER0_BASE,TIMER_A,SysCtlClockGet()-1);
	
	TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0AIntHandler);
	IntPrioritySet(INT_TIMER0A, 0);
	IntEnable(INT_TIMER0A);
	//配置为超时中断
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
}
//ADC采样速率配置,既可以用来触发ADC采样也可以触发FFT采样（本质上是一样的）
void FFT_Timer1_Congfig(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	TimerConfigure(TIMER1_BASE,TIMER_CFG_A_PERIODIC);
	TimerClockSourceSet(TIMER1_BASE,TIMER_CLOCK_SYSTEM);
	TimerControlTrigger(TIMER1_BASE,TIMER_A,true);
	TimerLoadSet(TIMER1_BASE,TIMER_A,SysCtlClockGet()/256000-1);
	TimerEnable(TIMER1_BASE,TIMER_A);
}
/*频率及占空比测量中断函数，用于捕获上升沿下降沿及数据计算，频率上限440K，占空比全程*/
void Frequent_Duty_M_INT_Handler(void)//捕获时间
{
	TimerIntClear(TIMER0_BASE,TIMER_CAPA_EVENT);
	switch (k)
	{
		case 0:
			TIMER_TICK[0]=TimerValueGet(TIMER0_BASE,TIMER_A);
			TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_NEG_EDGE);//下降沿捕获
			k=1;break;
		case 1:
			TIMER_TICK[1]=TimerValueGet(TIMER0_BASE,TIMER_A);
			TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_POS_EDGE);//上升沿捕获
			k=2;break;
		case 2:
			TIMER_TICK[2]=TimerValueGet(TIMER0_BASE,TIMER_A);
			TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_NEG_EDGE);//下降沿捕获
			k=3;break;
		case 3:
			if(TIMER_TICK[2]>TIMER_TICK[0])
		{
			time=TIMER_TICK[2]-TIMER_TICK[0];
		}
		if(TIMER_TICK[1]>TIMER_TICK[0])
		{
			hightime=TIMER_TICK[1]-TIMER_TICK[0];
		}
			TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_POS_EDGE);//上升沿捕获
			k=0;
	}
}
/*频率占空比测量结果的输出*/
void Fre_Duty_Output_INT_Handler(void)//定时一秒将数据传输到串口，优先级最高
{
	TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	rate=hightime*1.0/time;
	freq=SysCtlClockGet()/time;
	printf("f=%d hz\n",freq);
	printf("f=%.2f khz\n",freq/1000.0);
	printf("rate=%f\n",rate);
	printf("hightime=%d\n",hightime);
	printf("time=%d\n\r",time);
	hightime=0,freq=0,time=0,rate=0;
}
/*频率占空比配置函数*/
void Frequent_Duty_M_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	GPIOPinConfigure(GPIO_PB6_T0CCP0);
	GPIOPinTypeTimer(TIMER0A_PORT,TIMER0A_PIN);//引脚复用
	GPIOPadConfigSet(TIMER0A_PORT,TIMER0A_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//弱上拉
	
	TimerConfigure(TIMER0_BASE,TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME_UP);//捕获模式
	TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_POS_EDGE);//上升沿捕获
	TimerLoadSet(TIMER0_BASE,TIMER_A,0xFFFF);//装载值
	TimerIntRegister(TIMER0_BASE,TIMER_A,Frequent_Duty_M_INT_Handler);
	IntPrioritySet(INT_TIMER0A,1);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE,TIMER_CAPA_EVENT);//捕获中断
	IntMasterEnable();
	TimerEnable(TIMER0_BASE,TIMER_A);
	
}
/*频率占空比控制一秒输出函数(其他需要控制一秒输出数据的也可使用)*/
void Fre_Duty_Output_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	
	TimerConfigure(TIMER1_BASE,TIMER_CFG_A_PERIODIC);
	
	TimerLoadSet(TIMER1_BASE,TIMER_A,SysCtlClockGet()-1);

	TimerIntRegister(TIMER1_BASE,TIMER_A,Fre_Duty_Output_INT_Handler);
	IntPrioritySet(INT_TIMER1A, 0);
	IntEnable(INT_TIMER1A);
	TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	
	IntMasterEnable();
	TimerEnable(TIMER1_BASE,TIMER_A);
}





void FRE_H_Measure_Int_Handler(void)//溢出次数加1
{
	TimerIntClear(TIMER1_BASE,TIMER_CAPA_MATCH);
	overflow++;
	TimerEnable(TIMER1_BASE,TIMER_A);
}

void FRE_H_Output_Int_Handler(void)//每1秒输出一次频率
{
	TimerIntClear(TIMER2_BASE,TIMER_TIMA_TIMEOUT);
	t=TimerValueGet(TIMER1_BASE,TIMER_A);
	freq=(overflow*LOAD+LOAD-t);
	overflow=0;
	printf("%d hz\n",freq);
	printf("%.2f khz\n",freq/1000.0);
	printf("%.2f Mhz\n",freq/1000000.0);
	TimerLoadSet(TIMER1_BASE,TIMER_A,LOAD);
}
void Frequent_H_Config(void)
{
	//TIMER1A，用于采样计算频率
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinConfigure(GPIO_PF2_T1CCP0);
	GPIOPinTypeTimer(TIMER1A_PORT,TIMER1A_PIN);//引脚复用
	GPIOPadConfigSet(TIMER1A_PORT,TIMER1A_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//弱上拉
	
	TimerConfigure(TIMER1_BASE,TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_CAP_COUNT);//向上计数
	TimerControlEvent(TIMER1_BASE,TIMER_A,TIMER_EVENT_POS_EDGE);//上升沿捕获

	TimerLoadSet(TIMER1_BASE,TIMER_A,LOAD);
	TimerMatchSet(TIMER1_BASE,TIMER_A,0);

	TimerIntRegister(TIMER1_BASE,TIMER_A,FRE_H_Measure_Int_Handler);
	IntPrioritySet(INT_TIMER1A,0);
	IntEnable(INT_TIMER1A);
	TimerIntEnable(TIMER1_BASE,TIMER_CAPA_MATCH);

	IntMasterEnable();
	TimerEnable(TIMER1_BASE,TIMER_A);
	//TIMER2A,用于一秒输出数据
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
	
	TimerConfigure(TIMER2_BASE,TIMER_CFG_A_PERIODIC);
	
	TimerLoadSet(TIMER2_BASE,TIMER_A,SysCtlClockGet());
	
	TimerIntRegister(TIMER2_BASE,TIMER_A,FRE_H_Output_Int_Handler);
	IntEnable(INT_TIMER2A);
	TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);
	
	IntMasterEnable();
	TimerEnable(TIMER2_BASE,TIMER_A);
}



