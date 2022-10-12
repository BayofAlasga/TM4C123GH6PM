#ifndef __BSP_TIM_H__
#define __BSP_TIM_H__

#include "bsp_include.h"

#define TIMER0A_PORT 				GPIO_PORTB_BASE
#define TIMER0A_PIN 				GPIO_PIN_6

#define TIMER1A_PORT 				GPIO_PORTF_BASE
#define TIMER1A_PIN 				GPIO_PIN_2

#define TIMER2A_PORT 				GPIO_PORTF_BASE
#define TIMER2A_PIN 				GPIO_PIN_4

void Timer0A_Congfig(void);
void FFT_Timer1_Congfig(void);
void Frequent_Duty_M_Config(void);
void Fre_Duty_Output_Config(void);
void Frequent_H_Config(void);

#endif /*__BSP_TIM_H__*/
