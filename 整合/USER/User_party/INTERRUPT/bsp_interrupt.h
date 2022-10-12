#ifndef __BSP_INTERRUPT_H__
#define __BSP_INTERRUPT_H__

#include "bsp_include.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_adc.h"
#include "uc1701.h"
#include "bsp_ads1256.h"

void Interrupt_config(void);
void Key1_Interrupt_Config (void);
void Key1_Interrupt_Handler(void);
void Key2_Interrupt_Config (void);
void Key2_Interrupt_Handler(void);





#endif /* __BSP_INTERRUPT_H__ */
