#ifndef __M_74HC595_H
#define __M_74HC595_H

#include "bsp_include.h"

#define M_74HC595_CONTROL_BASE      GPIO_PORTE_BASE
#define M_74HC595_CONTROL_PERIPH    SYSCTL_PERIPH_GPIOE

#define SI_PIN        GPIO_PIN_0  	  //LDSI,串行数据输入口
#define STR_PIN       GPIO_PIN_1	    //LDSTR,并行数据输出控制端口
#define SCK_R_PIN     GPIO_PIN_2	    //LDSCK,串行时钟信号端口
//#define LDEN            //LDEN,芯片使能管脚,为高时：所有并行输出口为高阻态。
						              //为低时：芯片使能。也可以把该管脚直接接地或者焊接电阻R1。
/* 定义口线置0和置1的宏 */
#define SI_L		      GPIOPinWrite( M_74HC595_CONTROL_BASE, SI_PIN,0x00)
#define SI_H			    GPIOPinWrite( M_74HC595_CONTROL_BASE, SI_PIN,SI_PIN)

#define STR_L		      GPIOPinWrite( M_74HC595_CONTROL_BASE, STR_PIN,0x00)
#define STR_H			    GPIOPinWrite( M_74HC595_CONTROL_BASE, STR_PIN,STR_PIN)

#define SCK_R_L		    GPIOPinWrite( M_74HC595_CONTROL_BASE, SCK_R_PIN,0x00)
#define SCK_R_H			  GPIOPinWrite( M_74HC595_CONTROL_BASE, SCK_R_PIN,SCK_R_PIN)
							
void SendData_74HC595(uint32_t data);
void Init_74HC595(void);

#endif /* __M_74HC595_H */
