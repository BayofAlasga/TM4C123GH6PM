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

#define RELAYA_BASE					GPIO_PORTF_BASE
#define RELAYA_PIN					GPIO_PIN_0
#define RELAYB_BASE					GPIO_PORTF_BASE
#define RELAYB_PIN					GPIO_PIN_1
#define RELAYC_BASE					GPIO_PORTF_BASE
#define RELAYC_PIN					GPIO_PIN_2
#define RELAYD_BASE					GPIO_PORTF_BASE
#define RELAYD_PIN					GPIO_PIN_3

#define RELAY_A							0
#define RELAY_B							1
#define RELAY_C							2
#define RELAY_D							3

#define RELAY_OUT1					1
#define RELAY_OUT2					2

#define ADG419 							0
#define ADG409 							1
#define ADG411	 						2

#define MODE_ADG419_Switch1	0
#define MODE_ADG419_Switch2	1

#define MODE_ADG409_Switch1 0
#define MODE_ADG409_Switch2 1
#define MODE_ADG409_Switch3 2
#define MODE_ADG409_Switch4 3

#define MODE_ADG411_ON			0
#define MODE_ADG411_OFF			1

void PCF8574_Init(void);
void PCF8574_Write(uint8_t data);
void Relay_Init(void);
void Relay_Control(char shift,uint8_t out);
void Analogue_Switch(uint32_t chip,uint8_t mode);

#endif
