#ifndef	__LED_H
#define	__LED_H






extern u8 task_run_led;					//led����
extern u8 task_delay_led;
extern  u8 feed_error ;
extern u8 task_delay_error;				//������˸led����
extern u8 task_run_motor;				//�������
extern u8 led_flag;						
//extern u16 task_feed_again;
extern u8 feed_detect_again;
void pwr_task(void);
void error_task(void);
extern u8 error_time;					//����������д���������������



#endif