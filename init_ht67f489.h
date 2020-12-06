#ifndef __INIT_HT67F489_H__
#define __INIT_HT67F489_H__

#define uchar  unsigned char 
#define uint   unsigned int 
#define ushort unsigned short
#define u16 unsigned int
#define u8  unsigned char



void GPIOA_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void GPIOB_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void GPIOC_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void GPIOD_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void GPIOE_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void GPIOF_INIT(uchar GPIO_Pin,uchar GPIO_Mode,uchar GPIO_BitVal); 
void LCD_init();
void UART_init();

void init_Timer_isc0();
void AD_init();
void init_SyS();
void init_Timer();
void init_Timer1();
void init_Timerset();
//void init_Timer2();
/*void init_Timer3(void);*/

//void rtc_lcd_init_3();
//void rtc_lcd_init_2();
//void rtc_lcd_init_1();
//void rtc_lcd_init();
//void rtc_lcd_init_5();
void LCD_clrscreen();

#endif