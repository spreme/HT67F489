

//====================================================//
//�ȳ�ʼ�����IO�ڣ�IO����������ظ�����ĿҪ���������//
//		   ������ĿҪ�������ò���ʼ������ģ��		   //
//		   ע�����������ó�ʼ���������Ⱥ�˳��		  //
//					�����������ע��				  //
//====================================================//
#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"


//===========================PA�˿ڳ�ʼ������=========================================//
void GPIOA_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal) //u8 Ϊ�޷����ַ���
{
	if((uchar)
	GPIO_Mode == (uchar) 0x01) //paΪ������ʱ
	{
		_pac |= GPIO_Pin;		//��pa����GPIO_PinΪ���룬����λpac ��ͬʱ������������

		/*	_papu|=GPIO_Pin;*/
	}
	else
	{
		_pac &= (uchar) (~GPIO_Pin); //��pa����Ϊ����� 
		_papu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET) //����
	{
		_pa |= GPIO_Pin;
	}
	else
	{
		_pa &= (uchar) (~GPIO_Pin);

	}
}


//===========================PB�˿ڳ�ʼ������=========================================//
void GPIOB_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pbc |= GPIO_Pin;

		/*_pbpu|=GPIO_Pin;*/
	}
	else
	{
		_pbc &= (uchar) (~GPIO_Pin);
		_pbpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pb |= GPIO_Pin;
	}
	else
	{
		_pb &= (uchar) (~GPIO_Pin);
	}
}


//===========================PC�˿ڳ�ʼ������=========================================//
void GPIOC_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pcc |= GPIO_Pin;

		/*	_pcpu|=GPIO_Pin;*/
	}
	else
	{
		_pcc &= (uchar) (~GPIO_Pin);
		_pcpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pc |= GPIO_Pin;
	}
	else
	{
		_pc &= (uchar) (~GPIO_Pin);
	}
}


//===========================PD�˿ڳ�ʼ������=========================================//
void GPIOD_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pdc |= GPIO_Pin;

		/*	_pdpu|=GPIO_Pin;*/
	}
	else
	{
		_pdc &= (uchar) (~GPIO_Pin);
		_pdpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pd |= GPIO_Pin;
	}
	else
	{
		_pd &= (uchar) (~GPIO_Pin);
	}
}


//===========================PE�˿ڳ�ʼ������=========================================//
void GPIOE_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal)
{

	if((uchar)
	GPIO_Mode == (uchar) 0x01)
	{
		_pec |= GPIO_Pin;

		/*_pepu|=GPIO_Pin;*/
	}
	else
	{
		_pec &= (uchar) (~GPIO_Pin);
		_pepu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET)
	{
		_pe |= GPIO_Pin;
	}
	else
	{
		_pe &= (uchar) (~GPIO_Pin);
	}
}


//===========================PF�˿ڳ�ʼ������=========================================//
void GPIOF_INIT(uchar GPIO_Pin, uchar GPIO_Mode, uchar GPIO_BitVal) //u8 Ϊ�޷����ַ���
{
	if((uchar)
	GPIO_Mode == (uchar) 0x01) //paΪ������ʱ
	{
		_pfc |= GPIO_Pin;		//��pa����GPIO_PinΪ���룬����λpac ��ͬʱ������������

		/*	_pfpu|=GPIO_Pin;*/
	}
	else
	{
		_pfc &= (uchar) (~GPIO_Pin); //��pa����Ϊ����� 
		_pfpu &= (uchar) (~GPIO_Pin);
	}

	if(GPIO_BitVal != RESET) //����
	{
		_pf |= GPIO_Pin;
	}
	else
	{
		_pf &= (uchar) (~GPIO_Pin);

	}
}


//LCD��ʼ��,LCDʱ��Ϊfsub��������LXT��LIRC����
void LCD_init()
{
	_segcr0 = 0x00; 			//
	_segcr1 = 0xe0; 			//
	_segcr2 = 0x0f; 			//
	_lcdc0 = 0xd2;				//UNC
	_lcdc1 = 0xef;				//UNC
}


//UART��ʼ��
void UART_init()
{
	_uare = 1;					//ad�ж�
	_ucr1 = 0x80;
	_ucr2 = 0xc4;				//���ٲ�����
	_brg = 12;					//9600

	//_ucr2=0xec;
	//_brg=0x03;	//115200
}


//UART��ʼ��
void UART_init_lowpower()
{
	_uare = 1;					//ad�ж�
	_ucr1 = 0x80;
	_ucr2 = 0xc4;
	_brg = 0;					//512

	//_ucr2=0xec;
	//_brg=0x03;	//115200
}


//=========================================================================//

/*
A/D���ò���:
����1
ͨ��ADCR1 �Ĵ����е�ADCK2~ADCK0 λ��ѡ�������A/D ת��ʱ�ӡ�
����2
����ADCR0 �Ĵ����е�ADOFF λʹ��A/D��
����3
ͨ��ADCR1 ��ADCR0 �Ĵ����е�ACS4~ACS0 λ��ѡ���������ڲ�A/D ת
������ͨ����
����4
ͨ��ACERL �Ĵ����е�ACE7~ACE0 λ�Լ�ACERH �Ĵ����е�
ACE9~ACE8 λ��ѡ����Щ���Ź滮ΪA/D �������š�
����5
���Ҫʹ���жϣ����жϿ��ƼĴ�����Ҫ��ȷ�����ã���ȷ��A/D ת����
���Ǽ���ġ����жϿ���λEMI ��Ҫ��λΪ��1��, �Լ�A/D ת�����ж�λ
ADE Ҳ��Ҫ��λΪ��1����
����6
���ڿ���ͨ���趨ADCR0 �Ĵ����е�START λ�ӡ�0������1���ٻص���0����
��ʼģ��ת���Ĺ��̡�ע�⣬��λ���ʼ��Ϊ��0����

ע��:ADC��Ҫʹ�ö�ʱ�����ж�
*/
//=========================================================================//
void AD_init() //UNC
{
	_ade = 0;

	_adcr0 = 0x00;				//����AN0��ADת��������ADC��Դģ�鿪��ADC���ݸ��ֽ�ADRH��bit7-0�����ֽ�ADRL7-4
	_adcr1 = 0xc2;				//A/Dʱ��Դѡ��fsys/4���ڲ�Vbg��ADC�������λ��Vbgʹ�ܣ��ڲ�ADC��Դ
	_acerl = 0x01;				//���� PB0 �Ƿ�Ϊ A/D ����
	_acerh = 0x00;				//AN0��A/D����
}


//ϵͳ��ʼ��
void init_SyS()
{
	/*����ϵͳʱ�ӣ�ѡ��8Mʱ�ӣ�	��ʹ�øߵ�������������־λ��
	����ģʽ���ܣ�HLCLKϵͳʱ��ѡ��ΪfH/2-fH/64 or fSUB*/
	_smod = 0x09;				/* 0xe8;	*/
	_lvdc = 0;
	_wdtc = 0x55;				//ʹ�ÿ��Ź� 2 16 /f SUB
	_ctrl = 0x00;				//0X01		// //DEBUG 3.13

	_pawu = 0x00;				//PA�ڶ�û�л��ѹ���
	_fsyson = 0;				//�������ģʽ����Ƶʱ��fsub����
	_idlen = 1;					//=0ʱ��������ģʽ0�����ж�ֹͣ��LVDENҲҪΪ0��

}


//��ʱ��ʹ��TM0,���²�������ֻʹ��TM0�ж�
void init_Timer() //5ms
{
	//����Ϊѡ���ж�������
	_tmpc = 0x00;				//��ʹ���ⲿ�ж� //��ԭ����ʹ�ö�ʱ���������
	_tm0c0 = 0x38;				//������ʹ�ܲ��򿪼������ܿ��ƣ�ʹ��ʱ��ΪfH/64 //��ԭ��  ��λʱ��8us
	_tm0c1 = 0xc1;				//TM0����ģʽΪ��ʱ/������ģʽ������������TM0�Ƚ���Aƥ��

	//	_tm0dl= 0x00;				//��ԭ��û����2��
	//	_tm0dh= 0x00;				
	_tm0al = 0x71;				//625
	_tm0ah = 0x02;
}


//��ʱ��ʹ��TM1,���²�������ֻʹ��TM1�ж�
void init_Timer1()
{
#if 0

	//����Ϊѡ���ж�������
	//_t1cp	=1;
	_tm1c0 = 0x18;				//0x08;				//������ʹ�ܲ��򿪼������ܿ��ƣ�ʹ��ʱ��Ϊ
	_tm1c1 = 0xa1;				//TM0����ģʽΪ��ʱ/������ģʽ������������TM0�Ƚ���Aƥ��
	_tm1dl = 0x00;
	_tm1dh = 0x00;
	_tm1al = 0xff;				//�̶�����
	_tm1ah = 0x00;
#endif

	//����Ϊѡ���ж�������				//��ԭ��
	BL_EN = 0;					//����ر�
	_t1cp = 1;					//DEBUG 3.13		TP1���ſ���λ 1��ʹ��
	_tm1c0 = 0x10;				//0x18;//0x08;	DEBUG 3.13	//����TM1��ʹ��ʱ��Ϊϵͳʱ��fh
	_tm1c1 = 0xa1;				//TM1����ģʽΪpwmģʽ��256ռ�գ�1024����	
		
//	_tm1al = 0xff;				//�̶�����			TM1 CCRA ���ֽڼĴ���
//	_tm1ah = 0x00;				//TM1 CCRA ���ֽڼĴ���			255 	25%

	_tm1al = 0x00;				//�̶�����			TM1 CCRA ���ֽڼĴ���
	_tm1ah = 0x02;				//TM1 CCRA ���ֽڼĴ���			512 	50%
	
//	_tm1al = 0x00;				//�̶�����			TM1 CCRA ���ֽڼĴ���
//	_tm1ah = 0x03;				//TM1 CCRA ���ֽڼĴ���			768 	75%

//	_tm1al = 0b11111111;				//�̶�����			TM1 CCRA ���ֽڼĴ���
//	_tm1ah = 0b00000011;				//TM1 CCRA ���ֽڼĴ���			1023	100%
	
	_t1on = 0;					//DEBUG 3.13		TM1������ 0��off		1��on

}



//��ʱ��ʹ��TM2,���²�������ֻʹ��TM2�ж�
//void init_Timer2()
//{

//	//����Ϊѡ���ж�������
//	// _tmpc = 0x00;				//��ʹ���ⲿ�ж�
//	_tm2c0 = 0x08;				//������ʹ�ܲ��򿪼������ܿ��ƣ�ʹ��ʱ��ΪfH
//	_tm2c1 = 0xc1;				//TM2����ģʽΪ��ʱ/������ģʽ������������TM2�Ƚ���Aƥ��
//	_tm2dl = 0x00;
//	_tm2dh = 0x00;
//	_tm2al = 0xb9;				//185
//	_tm2ah = 0x00;				//2.7KHZ
//	_mf2e = 1;
//	_emi = 1;
//}


//��ʱ��ʹ��TM3,���²�������ֻʹ��TM2�ж�
//void init_Timer3(void)
//{
//				
// //����Ϊѡ���ж�������
// // _tmpc = 0x00;			//��ʹ���ⲿ�ж�
//	_tm3c0= 0x08;				//������ʹ�ܲ��򿪼������ܿ��ƣ�ʹ��ʱ��ΪfH/64
//	_tm3c1= 0xc1;				//TM3����ģʽΪ��ʱ/������ģʽ������������TM2�Ƚ���Aƥ��
//	_tm3dl= 0x00;				
//	_tm3dh= 0x00;				
//	_tm3al= 0xb9;			   //125
//	_tm3ah= 0x00;			   //200ns
//	_mf3e = 1;
//	_emi = 1;			
//}
void init_Timer_isc0()
{
	//����Ϊѡ��ʱ��0�ж�������
	_fsubc = 0x55;				//0xd5;  debug	3.13	//ʹ���ⲿ32.768kHz��������LXT			

	_tbc = 0x87;				//1sʱ����ʱ
	_tb0f = 0;					//ʹ��ʱ��0���ж������־λTB0F��0 
	_tb0e = 1;					//ʱ��0ʹ����λ
	_mf4e = 1;					//�๦���ж�4�жϿ���λ	1��ʹ��
	_mfi4 = 0x04;				//ʱ��0�жϿ���λ
	_emi = 1;					//���жϿ���λ 1��ʹ��
}





//����Ϊ��ʱ���жϹ���������  
void init_Timerset()
{
	_integ = 0xaa;				//ʹ���ⲿ�жϱ�Ե����λ	�ⲿ�ж�ȫ�����ó��½��ش���		
	_intc0 = 0x0f;				//�๦���ж�0�����ж�ʹ��   ʹ�����ж�EMI���ⲿ�ж�1���ⲿ�ж�0���Ͷ๦���ж�0
	_intc1 = 0x02;				//A/D�Ͷ๦���ж�1-3����  ʹ�ܶ๦���ж�2

	_intc2 = 0x07;				//0x67; 			//UARTʹ�ܣ�INT2-3�Ͷ๦���ж�4����

	_mfi0 = 0x02;				//TM0�Ƚ���Aƥ���жϿ���λʹ��		ʹ����TM0~1
	_mfi1 = 0x00;				//0x02; 	 //TM1�Ƚ���Aƥ���жϿ���λʹ��  //debug 3.13
	_mfi2 = 0x00;				//0x02		//TM2�Ƚ���A/Pʹ��
	_mfi3 = 0x00;				//TM3�Ƚ���A/P����

}


