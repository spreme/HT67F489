//====================================================//
//													  //
//													  //
//      ������Ϊ�򵥵Ĵ��ڷ��ͺͽ��մ��������ο�	  //
//   	  		  									  //
//					     			  				  //
//====================================================//

#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"


 void Delay_ms(uint ms)
{
	while(ms--)
	{
		GCC_DELAY(2000);//�������Դ���ʱָ�������ڣ�����Ƶ8Mhz�£�һ��ָ������Ϊ0.5us	
		GCC_CLRWDT();
	}
}


#if 0
//���͵����ַ�
void UART_SendChar(uchar data)
{
	uchar buff[3];
    uchar i;
    
    buff[0] = (data/100)%10+0x30;  
    buff[1] = (data/10)%10+0x30;  
    buff[2] = data%10+0x30;
	if(_txif)						//�жϷ������ݼĴ���Ϊ��
	{   
		for(i=0;i<3;i++)
		{
		_txr_rxr=buff[i];				//д��TXR--------���־λTXIF��TXIF=1��־TXRд��TSR,0��־��ֹд��TXR����������
		while(!_txif);				//�ȴ�����д��TSR
		while(!_tidle);
		}				//�ȴ����ݴ������
	}
}

//���͵����ַ�
void UART_SendChar_int(int data)
{
	int buff[4];
    uchar i;
    
    buff[0] = (data/1000)%10+0x30;
    buff[1] = (data/100)%10+0x30;  
    buff[2] = (data/10)%10+0x30;  
    buff[3] = data%10+0x30;
	if(_txif)						//�жϷ������ݼĴ���Ϊ��
	{   
		for(i=0;i<4;i++)
		{
		_txr_rxr=buff[i];				//д��TXR--------���־λTXIF��TXIF=1��־TXRд��TSR,0��־��ֹд��TXR����������
		while(!_txif);				//�ȴ�����д��TSR
		while(!_tidle);
		}				//�ȴ����ݴ������
	}
}

//�����ַ���
void SendString(uchar *ch)
{
	while(*ch!=0)
	{
		send_command(*(ch++));	
	}	
	
}


//���ʹ���
void send_command(uchar com)         
{
 /*_emi=0;
  _txr_rxr=0xba;
  while(_tidle==0);			   
  _txr_rxr=second;
  while(_tidle==0); 
  _txr_rxr=0x01;
  while(_tidle==0);
  _txr_rxr=second;
  while(_tidle==0);
  _txr_rxr=com;
  while(_tidle==0);
  _txr_rxr=0x0d;
  while(_tidle==0)
  _emi=1;*/
  
  	if(_txif)						//�жϷ������ݼĴ���Ϊ��
	{
		_txr_rxr=com;				//д��TXR--------���־λTXIF��TXIF=1��־TXRд��TSR,0��־��ֹд��TXR����������
		while(!_txif);				//�ȴ�����д��TSR
		while(!_tidle);				//�ȴ����ݴ������
	}
}

//���մ���
void deal_command()                           
{
  for(com_pos=0;com_pos<7;com_pos++){
  	if((rx_com[com_pos]==0xba)&&(rx_com[com_pos+6]=0x0d)){
	  rx_com[1]=0x00;
	  rx_com[2]=0x00;
	  rx_com[3]=0x00;
	  rx_com[4]=0x00;
      rx_com[5]=0x00;
	  rx_com[6]=0x00; 
  	}
  }
}
#endif
