#ifndef	__MOTOR_H
#define	__MOTOR_H

//#define USER_IR_DET      //使能红外探测
//#define USER_IR_DETFOOD  //使能红外探测,探测粮食是否空



#define MOTO_TIMEOUT                900  //9s



//错误码
#define ERROR_MOTOR_TIMEOUT					0x01	//超时
#define ERROR_EMPTY							0x02	//喂食份数空
#define ERROR_IR							0x03	//红外被挡
#define ERROR_EMPTY_NIR						0x04	//食物空
#define ERROR_FULL_IR						0x05	//食物满挡住红外
#define ERROR_EMPTY_IR						0x06	//食物空，红外被不明挡住



extern u8 err_type;


u8 motor(u8 count,u8 *err_type);
void motor_init(void);

#endif