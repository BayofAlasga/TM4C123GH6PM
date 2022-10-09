#include "bsp_ad9959.h"

uint8_t CSR_DATA0[1] = {0x10};     // 开 CH0
uint8_t CSR_DATA1[1] = {0x20};      // 开 CH1
uint8_t CSR_DATA2[1] = {0x40};      // 开 CH2
uint8_t CSR_DATA3[1] = {0x80};      // 开 CH3		
uint8_t FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
uint8_t CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302	   
																	
uint8_t CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360

uint8_t LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
uint8_t RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
uint8_t FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

uint32_t SinFre[4] = {1000, 1000, 50, 50};
uint32_t SinAmp[4] = {80, 540, 540, 540};
uint32_t SinPhr[4] = {0, 360 , 0, 180};

//在使用时需要根据实际情况改变该函数的参数（也不叫参数，这个函数没有参数）
void AD9959_init(void)
{
	uint8_t FR1_DATA[3] = {0xD0,0x00,0x00};

	SysCtlPeripheralEnable(AD9959_CONTROL1_PERIPH);
	SysCtlPeripheralEnable(AD9959_CONTROL2_PERIPH);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	#define UNLOCK_PD7 \
	{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD); \
	HWREG(GPIO_PORTD_BASE + 0x520) = 0x4C4F434B; \
	HWREG(GPIO_PORTD_BASE + 0x524)  = 0x80;}
	#define UNLOCK_PF0 \
	{SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); \
	HWREG(GPIO_PORTF_BASE + 0x520) = 0x4C4F434B; \
	HWREG(GPIO_PORTF_BASE + 0x524)  = 0x01;}

	GPIOPinTypeGPIOOutput(AD9959_CONTROL1_BASE, AD9959_P0_PIN);  //P0
	GPIOPinTypeGPIOOutput(AD9959_CONTROL1_BASE, AD9959_P1_PIN);  //P1
	GPIOPinTypeGPIOOutput(AD9959_CONTROL1_BASE, AD9959_P2_PIN);  //P2
	GPIOPinTypeGPIOOutput(AD9959_CONTROL1_BASE, AD9959_P3_PIN);  //P3
	GPIOPinTypeGPIOOutput(AD9959_CONTROL1_BASE, AD9959_SD0_PIN);  //SD0
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_SD1_PIN);  //SD1
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_SD2_PIN);  //SD2
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_SD3_PIN);  //SD3
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_SCK_PIN);  //SCLK
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, AD9959_CS_PIN);  //CS
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_UP_PIN);  //UPDATE
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_RST_PIN);  //RST
	GPIOPinTypeGPIOOutput(AD9959_CONTROL2_BASE, AD9959_PDC_PIN);  //PWR(PDC)

	Intserve();  //IO口初始化
	IntReset();  //AD9959复位  

	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//写功能寄存器1
	//  WriteData_AD9959(FR2_ADD,2,FR2_DATA,0);
	//  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
	//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
	//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
	//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
	//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
	//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
	
	
	//写入初始频率
	AD9959_Write_frequence(0,SinFre[0]);
	AD9959_Write_frequence(1,SinFre[1]);
	AD9959_Write_frequence(2,SinFre[2]);
	AD9959_Write_frequence(3,SinFre[3]);

	AD9959_Write_Phase(0, SinPhr[0]);
	AD9959_Write_Phase(1, SinPhr[1]);
	AD9959_Write_Phase(2, SinPhr[2]);
	AD9959_Write_Phase(3, SinPhr[3]);

	AD9959_Write_Amplitude(0, SinAmp[0]);
	AD9959_Write_Amplitude(1, SinAmp[1]);
	AD9959_Write_Amplitude(2, SinAmp[2]);
	AD9959_Write_Amplitude(3, SinAmp[3]);
}


void Intserve(void)
{
	AD9959_PWR_L;
	AD9959_CS_H;
	AD9959_SCLK_L;
	AD9959_UPDATE_L;
	AD9959_PS0_L;
	AD9959_PS1_L;
	AD9959_PS2_L;
	AD9959_PS3_L;
	AD9959_SDIO0_L;
	AD9959_SDIO1_L;
	AD9959_SDIO2_L;
	AD9959_SDIO3_L;
}
void IntReset(void)	  
{
  AD9959_Reset_L;
	bsp_Delay_ms(1);
	AD9959_Reset_H;
	bsp_Delay_ms(30);
	AD9959_Reset_L;
}

void IO_Update(void)  
{
	AD9959_UPDATE_L;
	bsp_Delay_ms(2);
	AD9959_UPDATE_H;
	bsp_Delay_ms(4);
	AD9959_UPDATE_L;
}

/*--------------------------------------------
函数功能：控制器通过SPI向AD9959写数据
RegisterAddress: 寄存器地址
NumberofRegisters: 所含字节数
*RegisterData: 数据起始地址
temp: 是否更新IO寄存器
----------------------------------------------*/
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp)
{
	uint8_t	ControlValue = 0;
	uint8_t	ValueToWrite = 0;
	uint8_t	RegisterIndex = 0;
	uint8_t	i = 0;

	ControlValue = RegisterAddress;
//写入地址
	AD9959_SCLK_L;
	AD9959_CS_L;	 
	for(i=0; i<8; i++)
	{
		AD9959_SCLK_L;
		if(0x80 == (ControlValue & 0x80))
		AD9959_SDIO0_H;	  
		else
		AD9959_SDIO0_L;	  
		AD9959_SCLK_H;
		ControlValue <<= 1;
	}
	AD9959_SCLK_L;
//写入数据
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			AD9959_SCLK_L;
			if(0x80 == (ValueToWrite & 0x80))
			AD9959_SDIO0_H;	  
			else
			AD9959_SDIO0_L;	  
			AD9959_SCLK_H;
			ValueToWrite <<= 1;
		}
		AD9959_SCLK_L;		
	}	
	if(temp==1)
        IO_Update();	
  AD9959_CS_H;
} 
/*---------------------------------------
函数功能：设置通道输出频率
Channel:  输出通道
Freq:     输出频率
---------------------------------------*/
void AD9959_Write_frequence(uint8_t Channel,uint32_t Freq)
{	 
    uint8_t CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//中间变量
    uint32_t Temp;            
    Temp=(uint32_t)Freq*8.589934592;	   //将输入频率因子分为四个字节  8.589934592=(2^32)/500000000 其中500M=25M*20(倍频数可编程)
    CFTW0_DATA[3]=(uint8_t)Temp;
    CFTW0_DATA[2]=(uint8_t)(Temp>>8);
    CFTW0_DATA[1]=(uint8_t)(Temp>>16);
    CFTW0_DATA[0]=(uint8_t)(Temp>>24);
    if(Channel==0)	  
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
        WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
    }
    else if(Channel==1)	
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH1通道
        WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH1设定频率	
    }
    else if(Channel==2)	
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH2通道
        WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH2设定频率	
    }
    else if(Channel==3)	
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH3通道
        WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.输出CH3设定频率	
    }																																																																										 
	
} 
/*---------------------------------------
函数功能：设置通道输出幅度
Channel:  输出通道
Ampli:    输出幅度,单位mv
---------------------------------------*/
void AD9959_Write_Amplitude(uint8_t Channel, uint16_t Ampli)
{ 
	Ampli=(uint16_t)((Ampli/540.0)*1023);
	uint16_t A_temp;//=0x23ff;
	uint8_t ACR_DATA[3] = {0x00,0x00,0x00};//default Value_Lx--0000 Rest_H8.91/Iout 
	
    A_temp=Ampli|0x1000;
    ACR_DATA[2] = (uint8_t)A_temp;  //低位数据
    ACR_DATA[1] = (uint8_t)(A_temp>>8); //高位数据
    if(Channel==0)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
        WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
    }
    else if(Channel==1)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
        WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
    }
    else if(Channel==2)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
        WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
    }
    else if(Channel==3)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
        WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
    }
}
/*---------------------------------------
函数功能：设置通道输出相位
Channel:  输出通道
Phase:    输出相位,范围：0~16383(对应角度：0°~360°(2π))
---------------------------------------*/
void AD9959_Write_Phase(uint8_t Channel,uint16_t Phase)
{
		Phase=(uint16_t)((Phase/360.0)*16383);
    uint16_t P_temp=0;
    P_temp=(uint16_t)Phase;
    CPOW0_DATA[1]=(uint8_t)P_temp;
    CPOW0_DATA[0]=(uint8_t)(P_temp>>8);
    if(Channel==0)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA0,0); 
        WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
    }
    else if(Channel==1)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA1,0); 
        WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
    }
    else if(Channel==2)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA2,0); 
        WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
    }
    else if(Channel==3)
    {
        WriteData_AD9959(CSR_ADD,1,CSR_DATA3,0); 
        WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
    }
}	

void Sweep_Freq_IntHandler(void)
{
  SinFre[0]+= 1000;
	AD9959_Write_frequence(0,SinFre[0]);
	while(SinFre[0]==200*1000)
	{
		SinFre[0]=0;
	}
	TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
}
void Sweep_Freq_Init(void)
{
	TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A,SysCtlClockGet()/100-1);
	IntMasterEnable();
	TimerIntRegister(TIMER0_BASE,TIMER_A,Sweep_Freq_IntHandler);
  TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER0A);
	TimerEnable(TIMER0_BASE, TIMER_A);
} 
