#ifndef __BSP_PCF8574_H__
#define __BSP_PCF8574_H__

#include "bsp_include.h"

#define PCF8574_BASE			GPIO_PORTC_BASE
#define PCF8574_PERIPH		SYSCTL_PERIPH_GPIOC
#define SCL_PIN						GPIO_PIN_4
#define SDA_PIN						GPIO_PIN_5

#define SCL_H							GPIOPinWrite( PCF8574_BASE,SCL_PIN,SCL_PIN)
#define SCL_L							GPIOPinWrite( PCF8574_BASE,SCL_PIN,0)
#define SDA_H							GPIOPinWrite( PCF8574_BASE,SDA_PIN,SDA_PIN)
#define SDA_L							GPIOPinWrite( PCF8574_BASE,SDA_PIN,0)

#define SDA_OUT						GPIOPinTypeGPIOOutput(PCF8574_BASE,SDA_PIN);
#define SDA_IN						GPIOPinTypeGPIOInput(PCF8574_BASE,SDA_PIN);
#define PCF8574_Address			0x40


void PCF8574_Init(void);
void PCF8574_Write(uint8_t data);


#endif
