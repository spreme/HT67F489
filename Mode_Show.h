#ifndef __MODE_SHOW_H__
#define __MODE_SHOW_H__

#include "define.h"

//普通显示函数
void LCD_Winter();					//
void LCD_Summer();					//
void LCD_Set_Week();				//
void LCD_Auto_Set();				//
void LCD_Travel_Set();				//

//==================================//
//温度设置显示函数
void Heating_Set();					//采暖设置函数
void BathWater_Set();				//卫浴设置函数
void WeekHeating_Set();				//周编程采暖设置函数
void WeekBarth_Set();				//周编程卫浴设置函数
void AutoSpecial_Set();				//自动K值设置函数
void AutoBath_Set();				//自动水温设置函数
void TraveHeating_Set();			//旅行采暖设置函数
void TraveBarth_Set();				//旅行水温设置函数
//==================================//


#endif