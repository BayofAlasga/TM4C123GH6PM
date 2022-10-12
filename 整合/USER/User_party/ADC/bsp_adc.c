#include "bsp_adc.h"
#include "arm_math.h"
#include "arm_const_structs.h"
#include "math.h"

#define SAMPLE_N    256
int i=0,j=0;
uint32_t value=0;
uint32_t value1=0;
uint16_t save[10000];
uint16_t save_FFT[SAMPLE_N];
float32_t datahandle[SAMPLE_N*2];
float32_t FFT_Output[SAMPLE_N];
float32_t FFT[SAMPLE_N];
void FFT_ADC1_Int_Handler(void)//ADC1的FFT算法中断处理函数
{
	ADCIntClear(ADC1_BASE,3);
	ADCSequenceDataGet(ADC1_BASE,3,&value1);
	save_FFT[i++]=value1;
	if(i==SAMPLE_N)
	{
		for(j=0;j<SAMPLE_N;j++)
		{
			datahandle[2*j]=save_FFT[j]*3.3/4096;
			datahandle[2*j+1]=0;
		}
		arm_cfft_f32(&arm_cfft_sR_f32_len256,datahandle, 0, 1);
		arm_cmplx_mag_f32(datahandle, FFT_Output, SAMPLE_N);
		FFT[0]=FFT_Output[0]/SAMPLE_N;
		printf("0,%.2f \n",FFT_Output[0]/SAMPLE_N);
		for(j=1;j<SAMPLE_N/2;j++)
		{
			FFT[j]=FFT_Output[j]/(SAMPLE_N/2);
		printf("%d,%.2f\n",j,FFT[j]);
		}
		for(j=SAMPLE_N/2;j<SAMPLE_N-1;j++)
		{
			FFT[j]=FFT_Output[SAMPLE_N-1-j]/(SAMPLE_N/2);
			printf("%d,%.2f\n",j,FFT[j]);
		}
		FFT[255]=FFT_Output[0]/SAMPLE_N;
		//printf("512 %.2f \n",FFT[SAMPLE_N-1]);
		i=0;
//下一行失能启动FFT的定时器，只采样一次
//		TimerDisable(TIMER1_BASE,TIMER_A);
//到这里FFT的处理基本完成，接下来是数据处理部分——频谱分析

		int f=0;
		float U0=0,U1=0,U2=0,U3=0,U4=0;
		double THD=0;
		for(j=1;j<(SAMPLE_N/2);j++)
		{
			if(FFT[j]>f)
			{
				f=j;
				U0=FFT[j];
			}
		}
		U1=FFT[2*f];
		U2=FFT[3*f];
		U3=FFT[4*f];
		U4=FFT[5*f];
		THD=sqrt(U1*U1+U2*U2+U3*U3+U4*U4)/U0;
		char str[100];
		ILI9341_draw_rectangle(40,50,250,180,WHITE);
		sprintf(str,"f0=%d khz",f);
		ILI9341_draw_string(60,60,str,WHITE);
		sprintf(str,"V0=%.4f v",U0);
		ILI9341_draw_string(60,90,str,WHITE);
		sprintf(str,"Deviation=%.4f v",FFT[0]);
		ILI9341_draw_string(60,120,str,WHITE);
		sprintf(str,"THD=%.4f",THD);
		ILI9341_draw_string(60,150,str,WHITE);
	}
}
void ADC0_Int_Handler(void)
{
	ADCIntClear(ADC0_BASE,2);
	ADCSequenceDataGet(ADC0_BASE,2,&value);
//单次触发把下一行的注释取消
	
//	printf("%.4f\n",value*3.3/4096);
	
//高采样速率把下面的注释取消
	
	save[i++]=value;
	if(i== 10000 )
	{
		for(j=0;j<10000;j++)
		{
			printf("%.4f\n",save[j]*3.3/4096);
		}
		i=0;
	}
	
}

void ADC0_Config(void)//单片机内置采样
{
//初始化
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_0);
	
//配置采样序列
	
	//普通ADC采样采用定时器或always触发
	ADCSequenceConfigure(ADC0_BASE,2,ADC_TRIGGER_TIMER, 0);//ADC_TRIGGER_TIMER、ADC_TRIGGER_ALWAYS、ADC_TRIGGER_PROCESSOR
	ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH3|ADC_CTL_IE| ADC_CTL_END);//PE0
	ADCIntRegister(ADC0_BASE,2,ADC0_Int_Handler);
//启用ADC中断
	IntPrioritySet(INT_ADC0SS2,0);
	ADCIntEnable(ADC0_BASE,2);
	IntEnable(INT_ADC0SS2);
	IntMasterEnable();
  ADCSequenceEnable(ADC0_BASE,2);
}
/*FFT配置的初始化*/
void FFT_ADC1_Config(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);
//配置采样序列
	ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_TIMER, 0);//ADC_TRIGGER_TIMER ADC_TRIGGER_ALWAYS
	ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH0|ADC_CTL_IE| ADC_CTL_END);//PE3
	ADCIntRegister(ADC1_BASE,3,FFT_ADC1_Int_Handler);
//启用ADC中断
	IntPrioritySet(INT_ADC1SS3, 0);
	ADCIntEnable(ADC1_BASE,3);
	IntEnable(INT_ADC1SS3);
	IntMasterEnable();
  ADCSequenceEnable(ADC1_BASE, 3);
}
/*单独获取一次ADC采样数据，注意ADC在中断中也会输出电压值，但那个无法进行处理，需要返回值就用这个，
然后注释掉中断函数中的输出*/
double ADCValueGet(void)
{
	double v=0;
	ADCProcessorTrigger(ADC0_BASE,2);
	v=value*3.3/4096;
	return v;
} 
