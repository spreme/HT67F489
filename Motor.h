#ifndef	__MOTOR_H
#define	__MOTOR_H

//#define USER_IR_DET      //ʹ�ܺ���̽��
//#define USER_IR_DETFOOD  //ʹ�ܺ���̽��,̽����ʳ�Ƿ��



#define MOTO_TIMEOUT                900  //9s



//������
#define ERROR_MOTOR_TIMEOUT					0x01	//��ʱ
#define ERROR_EMPTY							0x02	//ιʳ������
#define ERROR_IR							0x03	//���ⱻ��
#define ERROR_EMPTY_NIR						0x04	//ʳ���
#define ERROR_FULL_IR						0x05	//ʳ������ס����
#define ERROR_EMPTY_IR						0x06	//ʳ��գ����ⱻ������ס



extern u8 err_type;


u8 motor(u8 count,u8 *err_type);
void motor_init(void);

#endif