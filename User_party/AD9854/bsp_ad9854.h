#ifndef __AD9854_H__
#define __AD9854_H__
#include "bsp_include.h"
#define uint  unsigned int
#define uchar unsigned char
#define ulong unsigned long
	
//**********************以下为GPIO口设置********************************
//**********************以下为控制位GPIO口设置**************************
#define AD9854_CONTROL_BASE    GPIO_PORTD_BASE
#define AD9854_CONTROL_PERIPH  SYSCTL_PERIPH_GPIOD

#define AD9854_RESET_PIN     	 		GPIO_PIN_7   //AD9854复位端口
#define AD9854_UDCLK_PIN 	  			GPIO_PIN_0   //AD9854更新时钟
#define AD9854_WR_PIN     	  		GPIO_PIN_1   //AD9854写使能，低有效 
#define AD9854_RD_PIN     	  		GPIO_PIN_2  //AD9854读使能，低有效
#define AD9854_OSK_PIN        		GPIO_PIN_3   //AD9854 OSK控制端
#define AD9854_FSK_PIN      			GPIO_PIN_6  //AD9854 FSK,PSK控制
//**********************以下为数据位GPIO口设置**************************
#define AD9854_DATA_BASE    GPIO_PORTB_BASE
#define AD9854_DATA_PERIPH  SYSCTL_PERIPH_GPIOB

#define AD9854_D0_PIN    GPIO_PIN_0
#define AD9854_D1_PIN    GPIO_PIN_1
#define AD9854_D2_PIN    GPIO_PIN_2
#define AD9854_D3_PIN    GPIO_PIN_3
#define AD9854_D4_PIN    GPIO_PIN_4
#define AD9854_D5_PIN    GPIO_PIN_5
#define AD9854_D6_PIN    GPIO_PIN_6
#define AD9854_D7_PIN    GPIO_PIN_7
//**********************以下为地址位GPIO口设置**************************
#define AD9854_ADDR_BASE    			GPIO_PORTB_BASE
#define AD9854_ADDR_PERIPH  			SYSCTL_PERIPH_GPIOB

#define AD9854_A0_PIN											GPIO_PIN_0 //前三个用于单片机的输出
#define AD9854_A1_PIN											GPIO_PIN_1 //前三个用于单片机的输出
#define AD9854_A2_PIN											GPIO_PIN_2 //前三个用于单片机的输出
#define AD9854_A3_PIN											GPIO_PIN_3 //前三个用于单片机的输出
#define AD9854_A4_PIN											GPIO_PIN_4 //前三个用于单片机的输出
#define AD9854_A5_PIN											GPIO_PIN_5 //前三个用于单片机的输出
//**********************以下为GPIO口电平配置**************************
//**********************以下为控制位GPIO口电平配置**************************

//双向输入/输出更新时钟。
#define AD9854_UDCLK_H					GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_UDCLK_PIN,AD9854_UDCLK_PIN)
#define AD9854_UDCLK_L					GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_UDCLK_PIN,0x00)

//WR/SCLK 将并行数据写入I/O端口缓冲区 与SCLK共享函数。 WR
#define AD9854_WR_H							GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_WR_PIN,AD9854_WR_PIN)
#define AD9854_WR_L							GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_WR_PIN,0x00)

//RD/CS  从编程寄存器中读取并行数据。与控制系统共享函数。两者都是低电平活跃。
#define AD9854_RD_H							GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_RD_PIN,AD9854_RD_PIN)
#define AD9854_RD_L							GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_RD_PIN,0x00)

#define AD9854_RESET_H					GPIOPinWrite( AD9854_ADDR_BASE, AD9854_RESET_PIN,AD9854_RESET_PIN)
#define AD9854_RESET_L					GPIOPinWrite( AD9854_ADDR_BASE, AD9854_RESET_PIN,0x00)

//输出形状的键控功能
#define AD9854_OSK_H						GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_FSK_PIN,AD9854_FSK_PIN)
#define AD9854_OSK_L						GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_FSK_PIN,0x00)
//FSK/BPSK/HOLD 
#define AD9854_FSK_H						GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_OSK_PIN,AD9854_OSK_PIN)
#define AD9854_FSK_L						GPIOPinWrite( AD9854_CONTROL_BASE, AD9854_OSK_PIN,0x00)

//**********************以下为数据位GPIO口电平配置**************************
#define AD9854_D0_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D0_PIN,AD9854_D0_PIN)
#define AD9854_D0_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D0_PIN,0x00)
#define AD9854_D1_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D1_PIN,AD9854_D1_PIN)
#define AD9854_D1_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D1_PIN,0x00)
#define AD9854_D2_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D2_PIN,AD9854_D2_PIN)
#define AD9854_D2_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D2_PIN,0x00)
#define AD9854_D3_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D3_PIN,AD9854_D3_PIN)
#define AD9854_D3_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D3_PIN,0x00)
#define AD9854_D4_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D4_PIN,AD9854_D4_PIN)
#define AD9854_D4_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D4_PIN,0x00)
#define AD9854_D5_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D5_PIN,AD9854_D5_PIN)
#define AD9854_D5_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D5_PIN,0x00)
#define AD9854_D6_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D6_PIN,AD9854_D6_PIN)
#define AD9854_D6_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D6_PIN,0x00)
#define AD9854_D7_H			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D7_PIN,AD9854_D7_PIN)
#define AD9854_D7_L			GPIOPinWrite( AD9854_DATA_GPIO_BASE, AD9854_D7_PIN,0x00)

//**********************以下为地址GPIO口电平配置**************************
#define AD9854_A0_H						GPIOPinWrite( AD9854_ADDR_BASE,	AD9854_A0_PIN,AD9854_A0_PIN)
#define AD9854_A0_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A0_PIN,0x00)
#define AD9854_A1_H						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A1_PIN,AD9854_A1_PIN)
#define AD9854_A1_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A1_PIN,0x00)
#define AD9854_A2_H						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A2_PIN,AD9854_A2_PIN)
#define AD9854_A2_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A2_PIN,0x00)
#define AD9854_A3_H						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A3_PIN,AD9854_A3_PIN)
#define AD9854_A3_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A3_PIN,0x00)
#define AD9854_A4_H						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A4_PIN,AD9854_A4_PIN)
#define AD9854_A4_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A4_PIN,0x00)
#define AD9854_A5_H						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A5_PIN,AD9854_A5_PIN)
#define AD9854_A5_L						GPIOPinWrite( AD9854_ADDR_BASE, AD9854_A5_PIN,0x00)



void AD9854_IO_Init(void);
void AD9854_Init(void);
static void Freq_convert(long Freq);
void AD9854_SetSine(ulong Freq,uint Shape);
void AD9854_SetSine_double(double Freq,uint Shape);
void AD9854_InitRFSK(void);
void AD9854_SetRFSK(ulong Freq_Low,ulong Freq_High,ulong Freq_Up_Down,ulong FreRate);


#endif

