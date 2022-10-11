#ifndef 	__BSP_X9C104_H__
#define  	__BSP_X9C104_H__
#include "bsp_include.h"

#define X9c104_BASE						GPIO_PORTE_BASE
#define X9c104_PERIPH					SYSCTL_PERIPH_GPIOE

#define	X9c104_INC_PIN				GPIO_PIN_0
#define	X9c104_UD_PIN					GPIO_PIN_1
#define	X9c104_CS_PIN					GPIO_PIN_2

#define X9c104_INC_H					GPIOPinWrite( X9c104_BASE,X9c104_INC_PIN,X9c104_INC_PIN)
#define X9c104_INC_L					GPIOPinWrite( X9c104_BASE,X9c104_INC_PIN,0)
#define X9c104_UD_H						GPIOPinWrite( X9c104_BASE,X9c104_UD_PIN,X9c104_UD_PIN)
#define X9c104_UD_L						GPIOPinWrite( X9c104_BASE,X9c104_UD_PIN,0)
#define X9c104_CS_H						GPIOPinWrite( X9c104_BASE,X9c104_CS_PIN,X9c104_CS_PIN)
#define X9c104_CS_L						GPIOPinWrite( X9c104_BASE,X9c104_CS_PIN,0)

void X9c104_Init(void);
void X9c104_SetR(uint8_t value);
void X9c104_ChangeR(uint8_t dir,uint8_t value);
#endif
