#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"

//UART
uchar uart_flag;               
uchar com_pos;
uchar rx_com[7]={0};			  
uchar rx_pos;
uchar rx_flag;

//voltage









