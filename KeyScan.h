#ifndef __KEYSCAN_H__
#define __KEYSCAN_H__

#include "define.h"




//�̰�
#define KEY_SET     0x05		//������һ��
#define KEY_ESC     0x08		//key_play	�ֶ�ιʳ
#define KEY_REC     0x07		//����¼��
#define KEY_UP     	0x06		//��
#define KEY_DOWN    0x04		//��
//����
#define KEY_SET_L     0x15		//����	��ʼ����
#define KEY_ESC_L     0x18		//key_play
#define KEY_REC_L     0x17		//��ʼ¼��
#define KEY_UP_L      0x16		//
#define KEY_DOWN_L    0x14		//

u8 key_scan(void);

//extern u8 key_value_flag;
extern char key_up_flag ;
//extern int count;
extern u8 key_int;

extern  u8 key_int_1;
extern  u8 key_int_2;
extern  u8 key_int_3;

#endif