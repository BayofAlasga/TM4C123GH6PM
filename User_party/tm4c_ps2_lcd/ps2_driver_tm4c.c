/**
  ******************************************************************************
  * @file    ps2_driver_tm4c.c
  * @brief   PS2 KEYBORD DRIVERS FOR TM4C
  * @author  Liyuepeng(Flozfx) from ICEC-SAST of HEU
  * @version V0.1
  * @date    2014-6-7
  0 48
  1 49
  2 50 
  3 51
  4 52
  5 53
  6 54
  7 55
  8 56
  9 57 
  back 88
  del 44
  + 43
  - 45
  / 47
  * 42
  enter 13   unsigned int 
  ******************************************************************************
  */
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"


#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"

#include "ps2_driver_tm4c.h"
#include "ps2_keyboardtable.h" 



void ps2_rccgpio_init(void)
{
	SysCtlPeripheralEnable(PS2_SYSCTL_PERIPH);		
	UNLOCK_PF0;
	GPIOPadConfigSet(PS2_GPIO_BASE,PS2_CLK_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	GPIODirModeSet(PS2_GPIO_BASE,PS2_CLK_PIN,GPIO_DIR_MODE_IN);
	GPIOIntTypeSet(PS2_GPIO_BASE,PS2_CLK_PIN,GPIO_FALLING_EDGE);

	GPIOPinTypeGPIOInput(PS2_GPIO_BASE,PS2_DATA_PIN);
	
	IntPrioritySet(PS2_INT_GPIO, 0x00);
	IntEnable(PS2_INT_GPIO);
	GPIOIntRegister(PS2_GPIO_BASE,PS2_IntHandler);
	GPIOIntEnable(PS2_GPIO_BASE,PS2_GPIO_INT_PIN);
	IntMasterEnable();
}


uint32_t readbuf = 0;
uint8_t readtimes = 0;
uint8_t oddtimes = 0;
enum {CORRECT,NOTCORRECT} oddcheckreault = CORRECT;
//uint8_t getbuftime = 0;



void PS2_IntHandler(void)
{
	uint32_t Intstatus;
	Intstatus = GPIOIntStatus(PS2_GPIO_BASE,true);
	GPIOIntClear(PS2_GPIO_BASE,Intstatus);
	if (Intstatus & PS2_CLK_PIN){
		readtimes++;
		if(readtimes <= 9)
		{
				readbuf >>= 1;
				if(GPIOPinRead(PS2_GPIO_BASE ,PS2_DATA_PIN))
		  {
				readbuf |= 0x80;
				oddtimes++;
			}
		}
		
		else if(readtimes == 10)
		{
			 if(GPIOPinRead(PS2_GPIO_BASE,PS2_DATA_PIN)!=0)
			 {
				oddtimes++;
			 }
		
		}
		
		else if(readtimes >= 11)
			{
			
			if(oddtimes%2!=1)
			{
				oddcheckreault = NOTCORRECT;
			}
			
			if(oddcheckreault == CORRECT)
			{
				ps2_handle_code_value(readbuf);
		
			}
			oddcheckreault = CORRECT;
			
			oddtimes = 0;
			readbuf = 0;
			readtimes = 0;
		}
	}
}


#ifdef USE_KEYBOARD
static struct{
	unsigned char value;
	unsigned char ifupdate;
}ps2keyvalue = {' ',0};




  /**
  * @brief  Get the keyvalue
  * @param  None.
  * @retval char keyvalue.
	* @note   Blocking IO
  */unsigned char ps2key_getchar(void)
{
	while (ps2keyvalue.ifupdate == 0)
	{
		;
	};
	ps2keyvalue.ifupdate = 0;
	return ps2keyvalue.value;
}
 

  /**
  * @brief  Get the keyvalue
  * @param  None.
  * @retval char keyvalue. or 0: no key
	* @note   Nonblocking IO
  */


unsigned char ps2key_getchar_nonblock(void)
{
	if (ps2keyvalue.ifupdate == 0) 
		return 0;
	else{
		ps2keyvalue.ifupdate = 0;
		return ps2keyvalue.value;
	    }
}
//只能对基本按键（即键被按下时产生三个字节的扫描码的按键）做出解码，
//包括所有的可显示字符键和Table，Back Space和Ente三个特殊功能键
enum {NOSHIFT,SHIFTED} shiftstate = NOSHIFT;
enum {THROUGH,BREAK} breakstate = THROUGH;


void ps2_handle_code_value(uint32_t codevalue_8bit)
{
	int i;
	codevalue_8bit &= 0xff;
	if(breakstate == THROUGH) 
		{
		  if(codevalue_8bit == 0xF0) 
			breakstate = BREAK;
		  else
				{
			    if(codevalue_8bit == 0x12) 
				  shiftstate = SHIFTED;
			    else
						{
				       if(shiftstate == NOSHIFT)
								 {
					         for(i = 0;unshifted_ps2_keytab[i][0] != 0;i++)
									 {
						         if (unshifted_ps2_keytab[i][0] == codevalue_8bit)  
									  {
						         ps2keyvalue.value = unshifted_ps2_keytab[i][1];   
							       ps2keyvalue.ifupdate = 1;     
						         break;
						        }
					        }
				         }
			         else
				      	{
					        for(i = 0;shifted_ps2_keytab[i][0] != 0;i++)
									{
											if (shifted_ps2_keytab[i][0] == codevalue_8bit) 
										 {
											ps2keyvalue.value = shifted_ps2_keytab[i][1];   
											ps2keyvalue.ifupdate = 1;   
											break;
						         }	
					        }
								}
						}
		   }
	  }
	else
		{
		if(codevalue_8bit == 0x12) shiftstate = NOSHIFT;
		//else直接丢弃
		//ps2keyvalue.ifupdate = 1; 
		breakstate = THROUGH;
	  }
}
#endif
