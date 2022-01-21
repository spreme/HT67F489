
#include "HT67F4892.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "voltage.h"

//voltage
//
uint k, k1;


void start_conversion() //AD启动动作

{
	_start = 0;
	_start = 1;
	_start = 0;
}


uint voltage_get()
{
	//=====================================
	_acs4 = 1;					//第一次采集基准电压
	start_conversion();

	while(_eocb)
	{ //转换结束跳出循环
		GCC_CLRWDT1();
		GCC_CLRWDT2();
	};
	k1 = (_adrh << 4) | (_adrl >> 4); //AD的值赋值给K
	_acs4 = 0;					//第二次采集AN0
	start_conversion();

	while(_eocb)
	{ //转换结束跳出循环
		GCC_CLRWDT1();
		GCC_CLRWDT2();
	};

	//AD的值赋值给K
	k = (_adrh << 4) | (_adrl >> 4);
	return k;
}


uint AD_CaiJi(uchar Channel)
{
	uchar m, n;
	uint AD_Data;
	uint AD_Sum;

	_adcr0 = 0b00000000 + Channel; //ENADC

	for(m = 0; m < 10; m++);
	AD_Sum = 0;

	for(m = 0; m < 4; m++)
	{
		AD_Data = 0;

		for(n = 0; n < 10; n++);
		_start = 0;
		_start = 1;
		_start = 0;

		while(_eocb == 1);
		AD_Data = _adrh;
		AD_Data <<= 4;
		AD_Data += (_adrl >> 4);
		AD_Sum += AD_Data;
	}
	AD_Sum = AD_Sum / 4;
	return AD_Sum;
}


u8 voltage_low = 0;


void voltage_lcd()
{
//	_adoff = 0; 				//打开ad电源	
//	uint voltage = voltage_get();
//
//	if(voltage <= 2126)
//	{
//		voltage_low = 1;
//
//		if(buzzer_detect)
//		{
//			buzzer_detect = 0;
//			BUZZER_TASK();
//		}
//		T_POWER_clr;
//		T1_POWER;
//		T2_POWER_clr;
//		T3_POWER_clr;
//		T4_POWER_clr;
//	}
//	else if((voltage <= 2126) && (voltage > 2200))
//	{
//		voltage_low = 0;
//		T_POWER_clr;
//		T1_POWER;
//		T2_POWER_clr;
//		T3_POWER_clr;
//		T4_POWER;
//	}
//	else if(voltage <= 2300 && (voltage > 2200))
//	{
//		voltage_low = 0;
//		T_POWER_clr;
//		T1_POWER;
//		T2_POWER;
//		T3_POWER_clr;
//		T4_POWER;
//	}
//	else
//	{
//		voltage_low = 0;
//		T_POWER_clr;
//		T1_POWER;
//		T2_POWER;
//		T3_POWER;
//		T4_POWER;
//	}
//	_adoff = 1; 				//关闭ad电源
}


