#ifndef __VOLTAGE_H__
#define __VOLTAGE_H__

extern u8 voltage_low ;
void start_conversion();
uint voltage_get();
void voltage_lcd();
#endif