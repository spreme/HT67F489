

#ifndef __MENU_H__
#define __MENU_H__


void lcd_num_5(u8 num);
void lcd_num(u8 num);
void lcd_num_3(u8 num);
void lcd_num2_2(u8 num);
void lcd_num_1(u8 num);

void lcd_selcet(u8 addr, u8 num); //LCDѡ��
void lcd_selcet_off(u8 addr); //LCDû��ѡ��
char set_val(uchar addr, char min, char max, char meal); //��ԭ��//���ö�ʱιʳ����
char set_val_time(char addr, char min, char max); //���ö�ʱιʳ����ʱ��
void get_meal(u8 num); //��ȡ�˵�
char set_time(void); //����ʱ��
char set_meal(u8 num); //���ò˵� 
void sleep_mode(); //˯��ģʽ
void frist_menu(); //���˵�
void kaiji_mode(); //����ģʽ
void GPIO_INIT();
void kaiji_init(); //������ʼ��

extern u8 time2_task;
extern u8 res; //��λ��־λ
extern u8 sheep_flag; //˯��ģʽ��־λ

/*extern  u8 buzzer_time ;*/
extern char key_lock;
extern char col_staus;
extern char meal_flag;
extern u8 eeprom_feed[5];
extern u8 time_save_flag;		//ʱ�䱣���־λһСʱ����һ��
extern u8 time_save_flag_1;		//���߱�־λ,1:�������� 0����������
void menu_lcd();

#endif
