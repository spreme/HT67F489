

#ifndef __MENU_H__
#define __MENU_H__


void lcd_num_5(u8 num);
void lcd_num(u8 num);
void lcd_num_3(u8 num);
void lcd_num2_2(u8 num);
void lcd_num_1(u8 num);

void lcd_selcet(u8 addr, u8 num); //LCD选择
void lcd_selcet_off(u8 addr); //LCD没有选择
char set_val(uchar addr, char min, char max, char meal); //（原）//设置定时喂食任务
char set_val_time(char addr, char min, char max); //设置定时喂食任务时间
void get_meal(u8 num); //获取菜单
char set_time(void); //设置时间
char set_meal(u8 num); //设置菜单 
void sleep_mode(); //睡眠模式
void frist_menu(); //主菜单
void kaiji_mode(); //开机模式
void GPIO_INIT();
void kaiji_init(); //开机初始化

extern u8 time2_task;
extern u8 res; //复位标志位
extern u8 sheep_flag; //睡眠模式标志位

/*extern  u8 buzzer_time ;*/
extern char key_lock;
extern char col_staus;
extern char meal_flag;
extern u8 eeprom_feed[5];
extern u8 time_save_flag;		//时间保存标志位一小时保存一次
extern u8 time_save_flag_1;		//休眠标志位,1:代表休眠 0：代表醒着
void menu_lcd();

#endif
