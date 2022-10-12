#include "bsp_ad9854.h"
//说明：本程序基于硬件的外接晶振为20MHZ

//**********************以下为系统时钟以及其相关变量设置**************************
/* 
  此处根据自己的需要设置系统时钟以及与其相关的因子，一次需且只需开启一个   
  CLK_Set为时钟倍频设置，可设置4~20倍倍频，但最大不能超过300MHZ
  Freq_mult_ulong和Freq_mult_doulle均为2的48次方除以系统时钟——(2^(48)/SysCtlClk)，
  一个为长整形，一个为双精度型
*/
/*
#define      CLK_Set            4
const ulong  Freq_mult_ulong  = 3518437;
const double Freq_mult_doulle = 3518437.2088832;
*/
/*
#define      CLK_Set            5
const ulong  Freq_mult_ulong  = 2814750;
const double Freq_mult_doulle = 2814749.76710656;
*/
 
//#define      CLK_Set            6
//const ulong  Freq_mult_ulong  = 2345625;
//const double Freq_mult_doulle = 2345624.80592213;
// 
/*
#define      CLK_Set            7
const ulong  Freq_mult_ulong  = 2010536;
const double Freq_mult_doulle = 2010535.54793326;
*/
/*
#define      CLK_Set            8
const ulong  Freq_mult_ulong  = 1759219;
const double Freq_mult_doulle = 1759218.6044416;
*/
/*
#define      CLK_Set            9
const ulong  Freq_mult_ulong  = 1563750;
const double Freq_mult_doulle = 1563749.87061476;
*/
/*
#define      CLK_Set            10
const ulong  Freq_mult_ulong  = 1407375;
const double Freq_mult_doulle = 1407374.88355328;
*/
/*
#define      CLK_Set            11
const ulong  Freq_mult_ulong  = 1279432;
const double Freq_mult_doulle = 1279431.712321164;
*/

//时钟12倍频后为240MHZ 输出正弦频率范围在0~(1/2)*SYSCLK
//即为：0~120MHZ用这个配置即可达到最大输出
#define      CLK_Set            6
const ulong  Freq_mult_ulong  = 7036874;
const double Freq_mult_doulle = 7036874.4177664;


/*
#define      CLK_Set            13
const ulong  Freq_mult_ulong  = 1082596;
const double Freq_mult_doulle = 1082596.064271754;
*/

/*
#define      CLK_Set            14
const ulong  Freq_mult_ulong  = 1005268;
const double Freq_mult_doulle = 1005267.773966629;
*/

/*
#define      CLK_Set            15
const ulong  Freq_mult_ulong  = 938250;
const double Freq_mult_doulle = 938249.9223688533;

 */

uint8_t FreqWord[6];				 //6个字节频率控制字

static void AD9854_WR_Byte(uint32_t addr,uint32_t dat);
extern void AD9854_Init(void);						  
static void Freq_convert(long Freq);	         	  
extern void AD9854_SetSine(ulong Freq,uint Shape);
	  
//static void Freq_double_convert(double Freq);		  
//extern void AD9854_SetSine_double(double Freq,unsigned int Shape);



void AD9854_IO_Init(void){
	//控制PORT外设使能,设置GPIO为输出口
	SysCtlPeripheralEnable(AD9854_CONTROL_PERIPH);
	SysCtlPeripheralEnable(AD9854_ADDR_PERIPH);
	//PF0 解锁
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0xFF;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;  
	
	GPIOPinTypeGPIOOutput(AD9854_CONTROL_BASE,AD9854_UDCLK_PIN|AD9854_WR_PIN|AD9854_RD_PIN|AD9854_OSK_PIN|AD9854_FSK_PIN);
	GPIOPinTypeGPIOOutput(AD9854_ADDR_BASE,AD9854_RESET_PIN);
	//数据PORT外设使能,设置GPIO为输出口
//	SysCtlPeripheralEnable(AD9854_DATA_PERIPH);
//	GPIOPinTypeGPIOOutput(AD9854_DATA_BASE,AD9854_D0_PIN|AD9854_D1_PIN|AD9854_D2_PIN|AD9854_D3_PIN|
//											AD9854_D4_PIN|AD9854_D5_PIN|AD9854_D6_PIN|AD9854_D7_PIN);
	//地址PORT外设使能,设置GPIO为输出口

	GPIOPinTypeGPIOOutput(AD9854_ADDR_BASE,AD9854_A0_PIN|AD9854_A1_PIN|AD9854_A2_PIN|
										   AD9854_A3_PIN|AD9854_A4_PIN|AD9854_A5_PIN);
	}

	uint32_t dat1,dat2;
//====================================================================================
//函数名称:void AD9854_WR_Byte(uchar addr,uchar dat)
//函数功能:AD9854并行口写入数据
//入口参数:addr     6位地址
//         dat      写入的数据
//出口参数:无
//====================================================================================
void AD9854_WR_Byte(uint32_t addr,uint32_t dat)
{
		dat1= dat|(addr<<8);
	//将地址写入地址寄存器中
	//addr&0x0f是将地址的后四位保留下来 addr&0x30将地址的前两位保留下来
	//最后二者相或即可得到六位地址的二进制表示
	//最后将八位二进制中包含的四位向左移两位，将地址推到高六位以输出
	GPIOPinWrite(AD9854_ADDR_BASE, AD9854_A0_PIN|AD9854_A1_PIN|AD9854_A2_PIN|
				 AD9854_A3_PIN|AD9854_A4_PIN|AD9854_A5_PIN,	(uint8_t)(addr&0x0f)|((addr&0x30)<<2));
	//将数据写入数据寄存器中 直接把八位数据发出去             
	GPIOPinWrite(AD9854_DATA_BASE, AD9854_D0_PIN|AD9854_D1_PIN|AD9854_D2_PIN|
	             AD9854_D3_PIN|AD9854_D4_PIN|AD9854_D5_PIN|AD9854_D6_PIN|AD9854_D7_PIN,(uint8_t)dat);
//	PCF8574_Write((uint8_t)dat);
	AD9854_WR_L;
	AD9854_WR_H;
}
//====================================================================================
//函数名称:void AD9854_Init(void)
//函数功能:AD9854初始化
//入口参数:无
//出口参数:无
//====================================================================================
void AD9854_Init(void){
	AD9854_IO_Init();
	AD9854_WR_H;	//将读、写控制端口设为无效
	AD9854_RD_H;
	AD9854_UDCLK_L;
	AD9854_RESET_H;
	AD9854_RESET_L;
	
	AD9854_WR_Byte(0x1d,0x00);	           //关闭比较器
	AD9854_WR_Byte(0x1e,CLK_Set);	   //设置系统时钟倍频            
	AD9854_WR_Byte(0x1f,0x00);	   //设置系统为模式0，由外部更新
	AD9854_WR_Byte(0x20,0x60);	   //设置为可调节幅度，取消插值补偿

	AD9854_UDCLK_H;               //更新AD9854输出
  AD9854_UDCLK_L;

}
//====================================================================================
//函数名称:void Freq_convert(long Freq)
//函数功能:正弦信号频率数据转换
//入口参数:Freq   需要转换的频率，取值从0~SYSCLK/2
//出口参数:无   但是影响全局变量FreqWord[6]的值
//说明：   该算法位多字节相乘算法，有公式FTW = (Desired Output Frequency × 2N)/SYSCLK
//         得到该算法，其中N=48，Desired Output Frequency 为所需要的频率，即Freq，SYSCLK
//         为可编程的系统时钟，FTW为48Bit的频率控制字，即FreqWord[6]
//====================================================================================
void Freq_convert(long Freq){
	ulong FreqBuf;
    ulong Temp=Freq_mult_ulong; 
	
	uchar Array_Freq[4];			     //将输入频率因子分为四个字节
	Array_Freq[0]=(uchar)Freq;
	Array_Freq[1]=(uchar)(Freq>>8);
	Array_Freq[2]=(uchar)(Freq>>16);
	Array_Freq[3]=(uchar)(Freq>>24);

	FreqBuf=Temp*Array_Freq[0];                  
    FreqWord[0]=FreqBuf;    
    FreqBuf>>=8;

    FreqBuf+=(Temp*Array_Freq[1]);
    FreqWord[1]=FreqBuf;
    FreqBuf>>=8;

    FreqBuf+=(Temp*Array_Freq[2]);
    FreqWord[2]=FreqBuf;
    FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[3]);
    FreqWord[3]=FreqBuf;
    FreqBuf>>=8;

    FreqWord[4]=FreqBuf;
    FreqWord[5]=FreqBuf>>8;	
}
//====================================================================================
//函数名称:void AD9854_SetSine(ulong Freq,uint Shape)
//函数功能:AD9854正弦波产生程序
//入口参数:Freq   频率设置，取值范围为0~(1/2)*SYSCLK
//         Shape  幅度设置. 为12 Bit,取值范围为(0~4095) ,取值越大,幅度越大 
//出口参数:无
//====================================================================================
void AD9854_SetSine(ulong Freq,uint Shape){
	uchar count;
	uchar Adress;
	Adress = 0x04;                    //选择频率控制字地址的初值
	Freq_convert(Freq);		          //正弦信号频率数据转换 此处全局变量FreqWord[6]的值改变
	for(count=6;count>0;)	          //写入6字节的频率控制字  
    {
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
    }
	AD9854_WR_Byte(0x21,Shape>>8);	  //设置I通道幅度
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));
	
	AD9854_WR_Byte(0x23,Shape>>8);	  //设置Q通道幅度
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK_H;                    //更新AD9854输出
    AD9854_UDCLK_L;
}

//====================================================================================
//函数名称:void Freq_doublt_convert(double Freq)
//函数功能:正弦信号频率数据转换
//入口参数:Freq   需要转换的频率，取值从0~SYSCLK/2
//出口参数:无   但是影响全局变量FreqWord[6]的值
//说明：   有公式FTW = (Desired Output Frequency × 2N)/SYSCLK得到该函数，
//         其中N=48，Desired Output Frequency 为所需要的频率，即Freq，SYSCLK
//         为可编程的系统时钟，FTW为48Bit的频率控制字，即FreqWord[6]
//注意：   该函数与上面函数的区别为该函数的入口参数为double，可使信号的频率更精确
//         建议在100HZ以下用本函数，在高于100HZ的情况下用函数void Freq_convert(long Freq)
//====================================================================================
void Freq_double_convert(double Freq)   
{
	ulong Low32;
	uint  High16;
    double Temp=Freq_mult_doulle;   	            //23ca99为2的48次方除以120M
	Freq*=(double)(Temp);
//	1 0000 0000 0000 0000 0000 0000 0000 0000 = 4294967295
	High16 =(int)(Freq/4294967295);                  //2^32 = 4294967295
	Freq -= (double)High16*4294967295;
	Low32 = (ulong)Freq;

    FreqWord[0]=Low32;	     
    FreqWord[1]=Low32>>8;
    FreqWord[2]=Low32>>16;
    FreqWord[3]=Low32>>24;
    FreqWord[4]=High16;
    FreqWord[5]=High16>>8;			
} 

//====================================================================================
//函数名称:void AD9854_SetSine_double(double Freq,uint Shape)
//函数功能:AD9854正弦波产生程序
//入口参数:Freq   频率设置，取值范围为0~1/2*SYSCLK
//         Shape  幅度设置. 为12 Bit,取值范围为(0~4095) 
//出口参数:无
//====================================================================================
void AD9854_SetSine_double(double Freq,uint Shape)
{
	uchar count=0;
	uchar Adress;

	Adress=0x04;						     //选择频率控制字1地址的初值

	Freq_double_convert(Freq);		           //频率转换
	 
	for(count=6;count>0;)	                    //写入6字节的频率控制字  
    {
		AD9854_WR_Byte(Adress++,FreqWord[--count]);
    }
	
	AD9854_WR_Byte(0x21,Shape>>8);	  //设置I通道幅度
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));
	
	AD9854_WR_Byte(0x23,Shape>>8);	  //设置Q通道幅度
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK_H;                    //更新AD9854输出
  AD9854_UDCLK_L;
}
//====================================================================================
//函数名称:void AD9854_InitRFSK(void)
//函数功能:AD9854的RFSK初始化
//入口参数:无
//出口参数:无
//====================================================================================
void AD9854_InitRFSK(void)
{
	AD9854_WR_H;                      //将读、写控制端口设为无效
	AD9854_RD_H;
	AD9854_UDCLK_L;
	AD9854_RESET_H;                     //复位AD9854
	AD9854_RESET_L;
	
	AD9854_WR_Byte(0x1d,0x00);	       //关闭比较器
	AD9854_WR_Byte(0x1e,CLK_Set);	   //设置系统时钟倍频
	AD9854_WR_Byte(0x1f,0x24);	        //设置系统为模式2，由外部更新,使能三角波扫频功能
	AD9854_WR_Byte(0x20,0x60);	        //设置为可调节幅度，取消插值补偿	

	AD9854_UDCLK_H;                    //更新AD9854输出
  AD9854_UDCLK_L;
}
//====================================================================================
//函数名称:void AD9854_SetRFSK(void)
//函数功能:AD9854的RFSK设置
//入口参数:Freq_Low          RFSK低频率	   48Bit
//         Freq_High         RFSK高频率	   48Bit
//         Freq_Up_Down		 步进频率	   48Bit
//		   FreRate           斜率时钟控制  20Bit
//出口参数:无
//注：     每两个脉冲之间的时间周期用下式表示（FreRate +1）*（System Clock ），一个脉冲,
//         频率 上升或者下降 一个步进频率
//====================================================================================
void AD9854_SetRFSK(ulong Freq_Low,ulong Freq_High,ulong Freq_Up_Down,ulong FreRate)
{
	uchar count=6;
	uchar Adress1,Adress2,Adress3;
    const uint  Shape=4000;			   //幅度设置. 为12 Bit,取值范围为(0~4095)

	Adress1=0x04;		     //选择频率控制字地址的初值 
	Adress2=0x0a;
	Adress3=0x10;

	Freq_convert(Freq_Low);                             //频率1转换

	for(count=6;count>0;)	                         //写入6字节的频率控制字  
    {
		AD9854_WR_Byte(Adress1++,FreqWord[--count]);
    }

	Freq_convert(Freq_High);                             //频率2转换

	for(count=6;count>0;)	                         //写入6字节的频率控制字  
    {
		AD9854_WR_Byte(Adress2++,FreqWord[--count]);
    }

	Freq_convert(Freq_Up_Down);                             //步进频率转换

	for(count=6;count>0;)	                               //写入6字节的频率控制字  
    {
		AD9854_WR_Byte(Adress3++,FreqWord[--count]);
    }

	AD9854_WR_Byte(0x1a,(uchar)((FreRate>>16)&0x0f));				   //设置斜升速率
	AD9854_WR_Byte(0x1b,(uchar)(FreRate>>8));
	AD9854_WR_Byte(0x1c,(uchar)FreRate);				    

	AD9854_WR_Byte(0x21,Shape>>8);	                  //设置I通道幅度
	AD9854_WR_Byte(0x22,(uchar)(Shape&0xff));
	
	AD9854_WR_Byte(0x23,Shape>>8);	                  //设置Q通道幅度
	AD9854_WR_Byte(0x24,(uchar)(Shape&0xff));

	AD9854_UDCLK_H;                    //更新AD9854输出
  AD9854_UDCLK_L;	
}

//测试正弦波，采用120MHZ SYSCLK时,出来10MHZ波形，波形很好，测试成功
//当采用300MHZ SYSCLK时,测试50MHZ波形时,DDS发热厉害,且波形衰减严重,幅度在35mV左右
//
//int main()
//{
//	AD9854_Init();
//	AD9854_SetSine(80000000,4095);
//	while(1);			
//}
////测试扫频
//int main(){
//	AD9854_Init();
//	AD9854_InitRFSK();//初始化FSK扫频
////	AD9854_SetRFSK(SweepMinFre, SweepMaxFre, SweepStepFre, SweepTime);//输入扫频参数
//                                         最大值
//AD9854_SetRFSK(10000000, 50000000, 1000, 1048575);//输入扫频参数
//}
