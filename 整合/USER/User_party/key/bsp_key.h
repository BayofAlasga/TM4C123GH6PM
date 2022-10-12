#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__
#include "bsp_include.h"

//k1
#define KEY1_PORT			GPIO_PORTD_BASE
#define KEY1_PIN			GPIO_PIN_7

//k2
#define KEY2_PORT			GPIO_PORTF_BASE
#define KEY2_PIN			GPIO_PIN_4

//k3
#define KEY3_PORT			GPIO_PORTA_BASE
#define KEY3_PIN			GPIO_PIN_3

//k4
#define KEY4_PORT			GPIO_PORTA_BASE
#define KEY4_PIN			GPIO_PIN_2


void KEY_Config(void);
void Key1_Interrupt_Config (void);
void Key2_Interrupt_Config (void);




#endif /*__BSP_KEY_H__*/
