#include "bsp_74hc595.h"

#define num 3
//改变并行端口状态函数，入口参数为32位，一个字长度，有效值为0~bit23,共24位，对应24个扩展管脚的状态（1_Q0 ~ 3_Q7）。
void SendData_74HC595(uint32_t data)
 {
    uint8_t byte;
	 for(uint8_t j=0;j<num;j++)
	 {
		 byte=data<<(8*j);
			for(uint8_t i=0;i<8;i++)
			{
				SCK_R_L;
				if(byte&0x01)
				{
					SI_H;
				}
				else
				{
					SI_L;
				}
				byte = byte>>1;
				SCK_R_H;
			}
		}
    STR_L;
    bsp_Delay_ms(3);
    STR_H;				  
 }
 
//初始化控制端口，与MQ01A相连的管脚应该全部设置为输出。并输出为高。
 void Init_74HC595(void)
{
	SysCtlPeripheralEnable(M_74HC595_CONTROL_PERIPH);
	GPIOPinTypeGPIOOutput(M_74HC595_CONTROL_BASE, SI_PIN|STR_PIN|SCK_R_PIN);
  STR_H;
  SCK_R_H;
  SI_H;
}
