/**
  ******************************************************************************
  * @file    ps2_driver_tm4c.h
  * @brief   PS2 KEYBORD DRIVERS FOR TM4C
  * @author  Liyuepeng(Flozfx) from ICEC-SAST of HEU
  * @version V0.1
  * @date    2014-6-7
  ******************************************************************************
  */
	
#ifndef __PS2_DRIVER_TM4C_H__
#define __PS2_DRIVER_TM4C_H__



/*----------------------configure----------------------*/

//#define USE_MOUSE
#define USE_KEYBOARD

#define PS2_GPIO_BASE GPIO_PORTA_BASE
#define PS2_SYSCTL_PERIPH SYSCTL_PERIPH_GPIOA
#define PS2_DATA_PIN GPIO_PIN_7
#define PS2_CLK_PIN GPIO_PIN_6
//A 6 7

#define  PS2_INT_GPIO                  INT_GPIOA
#define  PS2_GPIO_INT_PIN              GPIO_INT_PIN_6

#define UNLOCK_PF0 \
	{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); \
	HWREG(GPIO_PORTA_BASE + 0x520) = 0x4C4F434B; \
	HWREG(GPIO_PORTA_BASE + 0x524)  = 0x01;}


/*------------------------------------------------------*/
void ps2_rccgpio_init(void);

#ifdef USE_KEYBOARD
unsigned char ps2key_getchar(void);
unsigned char ps2key_getchar_nonblock(void);
#endif
#endif
    

void ps2_handle_code_value(uint32_t codevalue_8bit);
void PS2_IntHandler(void);

    
