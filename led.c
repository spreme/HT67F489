
#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"
#include "Menu.h"
#include "Feed.h"
#include "sound_isd1820.h"
#include "Led.h"
#include "Motor.h"


u8 feed_error = 0; //��¼����ιʳת������
u8 task_delay_error = 100;
u8 task_run_motor = 1;

u8 feed_detect_again = 0;


void pwr_task(void)
{
	RECODE_LED = ~RECODE_LED;		//�����˸
	
//	if(error_time == 0)				//ֻ��һ��ִ��
		PWR_LED = LED_OFF;			//�ر��̵�
	
//	error_time = 1;					//��һ��ִ�б�־λ
	
//	if(PWR_LED == LED_ON)			//��˸���������������̵����ˣ��˳�����
//		task_run_led = 0;			//���������ս�
	
}


void error_task(void)
{
	if(feed_error)
	{
		task_run_led = 1;
		led_flag = 4;
	}
	else
	{
		task_run_led = 0;
		led_flag = 0;
	}

	//�жϺ���Թ��Ƿ�һֱ���赲��gpio���ŵ�ƽ0��1��
	//	if (IR_DET) {
	//		feed_error |= ERROR_IR;
	//	} else {
	//		feed_error &= ~ERROR_IR;
	//	}
}


