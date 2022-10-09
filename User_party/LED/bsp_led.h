#ifndef	__BSP_LED_H__
#define	__BSP_LED_H__
#include "bsp_include.h"


#define LED1_PORT	GPIO_PORTA_BASE
#define LED1_PIN	GPIO_PIN_4

#define LED2_PORT	GPIO_PORTF_BASE
#define LED2_PIN	GPIO_PIN_0

#define LED3_PORT	GPIO_PORTD_BASE
#define LED3_PIN	GPIO_PIN_6

#define LED1_ON     GPIOPinWrite(LED1_PORT,LED1_PIN,0)
#define LED1_OFF		GPIOPinWrite(LED1_PORT,LED1_PIN,LED1_PIN)

#define LED2_ON			GPIOPinWrite(LED2_PORT,LED2_PIN,0)
#define LED2_OFF		GPIOPinWrite(LED2_PORT,LED2_PIN,LED2_PIN)

#define LED3_ON			GPIOPinWrite(LED3_PORT,LED3_PIN,0)
#define LED3_OFF		GPIOPinWrite(LED3_PORT,LED3_PIN,LED3_PIN)







void LED_Config(void);


#endif	/* __BSP_LED_H__ */
