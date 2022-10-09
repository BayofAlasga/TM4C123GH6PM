#ifndef INCLUDE_H_
#define INCLUDE_H_
//基础部分
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "inc/hw_sysctl.h"


//有关80Mhz的部分
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

//io操作
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"

//有关中断
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

//有关串口
#include "driverlib/uart.h"
#include "utils/uartstdio.h"//需要导入这个的c和h文件

//有关定时器和pwm波
#include "driverlib/pwm.h"
#include "driverlib/timer.h"
#include "inc/hw_timer.h"

//有关浮点运算
#include "driverlib/fpu.h"

//有关i2c和ssi
#include "driverlib/i2c.h"
#include "inc/hw_i2c.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"

//有关qei和adc
#include "driverlib/qei.h"
#include "driverlib/adc.h"

//dma
#include "driverlib/udma.h"

//other
#include "uc1701.h"
#include "hw_uc1701.h"
#include "ps2_driver_tm4c.h"
#include "ps2_keyboardtable.h"
#include "ps2_LCD.h"

//bsp
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_tim.h"
#include "bsp_adc.h"
#include "bsp_usart.h"
#include "bsp_dma.h"
#include "bsp_dac.h"
#include "bsp_ads1256.h"
#include "bsp_ad9854.h"
#include "bsp_ad9959.h"
#include "bsp_pcf8574.h"
#include "bsp_74hc595.h"
#include "bsp_x9c104.h"


void bsp_Delay_ms(uint32_t ms);
void bsp_Delay_us(uint32_t us);
#endif /* INCLUDE_H_ */
