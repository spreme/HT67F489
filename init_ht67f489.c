

//====================================================//
//先初始化完成IO口，IO口配置请务必根据项目要求进行配置//
//		   根据项目要求再配置并初始化其他模块		   //
//		   注意主函数调用初始化函数的先后顺序		  //
//					程序必须做好注释				  //
//====================================================//
#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"


//===========================PA端口初始化函数=========================================//
void GPIOA_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal) //u8 为无符号字符型
{
	if((uchar)
	GPIO_Mode == (uchar) 0x01) //pa为输入型时
	{
		_pac |= GPIO_Pin;		//当pa引脚GPIO_Pin为输入，则置位pac ，同时设置上拉电阻

		/*	_papu|=GPIO_Pin;*/
	}
	else
	{
		_pac &= (uchar) (~GPIO_Pin); //将pa设置为输出型 
		_papu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET) //重置
	{
		_pa |= GPIO_Pin;
	}
	else
	{
		_pa &= (uchar) (~GPIO_Pin);

	}
}


//===========================PB端口初始化函数=========================================//
void GPIOB_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pbc |= GPIO_Pin;

		/*_pbpu|=GPIO_Pin;*/
	}
	else
	{
		_pbc &= (uchar) (~GPIO_Pin);
		_pbpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pb |= GPIO_Pin;
	}
	else
	{
		_pb &= (uchar) (~GPIO_Pin);
	}
}


//===========================PC端口初始化函数=========================================//
void GPIOC_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pcc |= GPIO_Pin;

		/*	_pcpu|=GPIO_Pin;*/
	}
	else
	{
		_pcc &= (uchar) (~GPIO_Pin);
		_pcpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pc |= GPIO_Pin;
	}
	else
	{
		_pc &= (uchar) (~GPIO_Pin);
	}
}


//===========================PD端口初始化函数=========================================//
void GPIOD_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pdc |= GPIO_Pin;

		/*	_pdpu|=GPIO_Pin;*/
	}
	else
	{
		_pdc &= (uchar) (~GPIO_Pin);
		_pdpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pd |= GPIO_Pin;
	}
	else
	{
		_pd &= (uchar) (~GPIO_Pin);
	}
}


//===========================PE端口初始化函数=========================================//
void GPIOE_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pec |= GPIO_Pin;

		/*_pepu|=GPIO_Pin;*/
	}
	else
	{
		_pec &= (uchar) (~GPIO_Pin);
		_pepu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pe |= GPIO_Pin;
	}
	else
	{
		_pe &= (uchar) (~GPIO_Pin);
	}
}


//===========================PF端口初始化函数=========================================//
void GPIOF_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal) //u8 为无符号字符型
{
	if((uchar)
	GPIO_Mode == (uchar) 0x01) //pa为输入型时
	{
		_pfc |= GPIO_Pin;		//当pa引脚GPIO_Pin为输入，则置位pac ，同时设置上拉电阻

		/*	_pfpu|=GPIO_Pin;*/
	}
	else
	{
		_pfc &= (uchar) (~GPIO_Pin); //将pa设置为输出型 
		_pfpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET) //重置
	{
		_pf |= GPIO_Pin;
	}
	else
	{
		_pf &= (uchar) (~GPIO_Pin);

	}
}


//LCD初始化,LCD时钟为fsub，需启动LXT或LIRC振荡器
void LCD_init()
{
	_segcr0 = 0x00; 			//
	_segcr1 = 0xe0; 			//
	_segcr2 = 0x0f; 			//
	_lcdc0 = 0xd2;				//UNC
	_lcdc1 = 0xef;				//UNC
}


//UART初始化
void UART_init()
{
	_uare = 1;					//ad中断
	_ucr1 = 0x80;
	_ucr2 = 0xc4;				//低速波特率
	_brg = 12;					//9600

	//_ucr2=0xec;
	//_brg=0x03;	//115200
}


//UART初始化
void UART_init_lowpower()
{
	_uare = 1;					//ad中断
	_ucr1 = 0x80;
	_ucr2 = 0xc4;
	_brg = 0;					//512

	//_ucr2=0xec;
	//_brg=0x03;	//115200
}


//=========================================================================//

/*
A/D设置步骤:
步骤1
通过ADCR1 寄存器中的ADCK2~ADCK0 位，选择所需的A/D 转换时钟。
步骤2
清零ADCR0 寄存器中的ADOFF 位使能A/D。
步骤3
通过ADCR1 和ADCR0 寄存器中的ACS4~ACS0 位，选择连接至内部A/D 转
换器的通道。
步骤4
通过ACERL 寄存器中的ACE7~ACE0 位以及ACERH 寄存器中的
ACE9~ACE8 位，选择哪些引脚规划为A/D 输入引脚。
步骤5
如果要使用中断，则中断控制寄存器需要正确地设置，以确保A/D 转换功
能是激活的。总中断控制位EMI 需要置位为“1”, 以及A/D 转换器中断位
ADE 也需要置位为“1”。
步骤6
现在可以通过设定ADCR0 寄存器中的START 位从“0”到“1”再回到“0”，
开始模数转换的过程。注意，该位需初始化为“0”。

注意:ADC需要使用定时器和中断
*/
//=========================================================================//
void AD_init() //UNC
{
	_ade = 0;

	_adcr0 = 0x00;				//接入AN0，AD转换结束，ADC电源模块开，ADC数据高字节ADRH的bit7-0，低字节ADRL7-4
	_adcr1 = 0xc2;				//A/D时钟源选择fsys/4，内部Vbg做ADC输入控制位，Vbg使能，内部ADC电源
	_acerl = 0x01;				//定义 PB0 是否为 A/D 输入
	_acerh = 0x00;				//AN0是A/D输入
}


//系统初始化
void init_SyS()
{
	/*配置系统时钟，选用8M时钟，	不使用高低速振荡器就绪标志位，
	空闲模式除能，HLCLK系统时钟选择为fH/2-fH/64 or fSUB*/
	_smod = 0x09;				/* 0xe8;	*/
	_lvdc = 0;
	_wdtc = 0x55;				//使用看门狗 2 16 /f SUB
	_ctrl = 0x00;				//0X01		// //DEBUG 3.13

	_pawu = 0x00;				//PA口都没有唤醒功能
	_fsyson = 0;				//进入空闲模式，低频时钟fsub开启
	_idlen = 1;					//=0时进入休眠模式0（所有都停止，LVDEN也要为0）

}


//定时器使用TM0,以下参数配置只使用TM0中断
void init_Timer() //5ms
{
	//以下为选择中断配置项
	_tmpc = 0x00;				//不使用外部中断 //（原）不使用定时器输出引脚
	_tm0c0 = 0x38;				//计数器使能并打开计数器总控制，使用时钟为fH/64 //（原）  单位时间8us
	_tm0c1 = 0xc1;				//TM0工作模式为定时/计数器模式，清零条件与TM0比较器A匹配

	//	_tm0dl= 0x00;				//（原）没有这2句
	//	_tm0dh= 0x00;				
	_tm0al = 0x71;				//625
	_tm0ah = 0x02;
}


//定时器使用TM1,以下参数配置只使用TM1中断
void init_Timer1()
{
#if 0

	//以下为选择中断配置项
	//_t1cp	=1;
	_tm1c0 = 0x18;				//0x08;				//计数器使能并打开计数器总控制，使用时钟为
	_tm1c1 = 0xa1;				//TM0工作模式为定时/计数器模式，清零条件与TM0比较器A匹配
	_tm1dl = 0x00;
	_tm1dh = 0x00;
	_tm1al = 0xff;				//固定背光
	_tm1ah = 0x00;
#endif

	//以下为选择中断配置项				//（原）
	BL_EN = 0;					//背光关闭
	_t1cp = 1;					//DEBUG 3.13		TP1引脚控制位 1：使能
	_tm1c0 = 0x10;				//0x18;//0x08;	DEBUG 3.13	//除能TM1，使用时钟为系统时钟fh
	_tm1c1 = 0xa1;				//TM1工作模式为pwm模式，256占空，1024周期	
		
//	_tm1al = 0xff;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0x00;				//TM1 CCRA 高字节寄存器			255 	25%

	_tm1al = 0x00;				//固定背光			TM1 CCRA 低字节寄存器
	_tm1ah = 0x02;				//TM1 CCRA 高字节寄存器			512 	50%
	
//	_tm1al = 0x00;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0x03;				//TM1 CCRA 高字节寄存器			768 	75%

//	_tm1al = 0b11111111;				//固定背光			TM1 CCRA 低字节寄存器
//	_tm1ah = 0b00000011;				//TM1 CCRA 高字节寄存器			1023	100%
	
	_t1on = 0;					//DEBUG 3.13		TM1计数器 0：off		1：on

}



//定时器使用TM2,以下参数配置只使用TM2中断
//void init_Timer2()
//{

//	//以下为选择中断配置项
//	// _tmpc = 0x00;				//不使用外部中断
//	_tm2c0 = 0x08;				//计数器使能并打开计数器总控制，使用时钟为fH
//	_tm2c1 = 0xc1;				//TM2工作模式为定时/计数器模式，清零条件与TM2比较器A匹配
//	_tm2dl = 0x00;
//	_tm2dh = 0x00;
//	_tm2al = 0xb9;				//185
//	_tm2ah = 0x00;				//2.7KHZ
//	_mf2e = 1;
//	_emi = 1;
//}


//定时器使用TM3,以下参数配置只使用TM2中断
//void init_Timer3(void)
//{
//				
// //以下为选择中断配置项
// // _tmpc = 0x00;			//不使用外部中断
//	_tm3c0= 0x08;				//计数器使能并打开计数器总控制，使用时钟为fH/64
//	_tm3c1= 0xc1;				//TM3工作模式为定时/计数器模式，清零条件与TM2比较器A匹配
//	_tm3dl= 0x00;				
//	_tm3dh= 0x00;				
//	_tm3al= 0xb9;			   //125
//	_tm3ah= 0x00;			   //200ns
//	_mf3e = 1;
//	_emi = 1;			
//}
void init_Timer_isc0()
{
	//以下为选择时基0中断配置项
	_fsubc = 0x55;				//0xd5;  debug	3.13	//使用外部32.768kHz晶体振荡器LXT			

	_tbc = 0x87;				//1s时基定时
	_tb0f = 0;					//使用时基0，中断请求标志位TB0F清0 
	_tb0e = 1;					//时基0使能置位
	_mf4e = 1;					//多功能中断4中断控制位	1：使能
	_mfi4 = 0x04;				//时基0中断控制位
	_emi = 1;					//总中断控制位 1：使能
}





//以下为定时器中断功能配置项  
void init_Timerset()
{
	_integ = 0xaa;				//使用外部中断边缘控制位	外部中断全部设置成下降沿触发		
	_intc0 = 0x0f;				//多功能中断0和总中断使能   使能中中断EMI和外部中断1和外部中断0，和多功能中断0
	_intc1 = 0x02;				//A/D和多功能中断1-3除能  使能多功能中断2

	_intc2 = 0x07;				//0x67; 			//UART使能，INT2-3和多功能中断4除能

	_mfi0 = 0x02;				//TM0比较器A匹配中断控制位使能		使用了TM0~1
	_mfi1 = 0x00;				//0x02; 	 //TM1比较器A匹配中断控制位使能  //debug 3.13
	_mfi2 = 0x00;				//0x02		//TM2比较器A/P使能
	_mfi3 = 0x00;				//TM3比较器A/P除能

}


