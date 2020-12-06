//====================================================//
//													  //
//													  //
//      本程序为简单的串口发送和接收处理，仅供参考	  //
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
		GCC_DELAY(2000);//编译器自带延时指定个周期，在主频8Mhz下，一个指令周期为0.5us	
		GCC_CLRWDT();
	}
}


#if 0
//发送单个字符
void UART_SendChar(uchar data)
{
	uchar buff[3];
    uchar i;
    
    buff[0] = (data/100)%10+0x30;  
    buff[1] = (data/10)%10+0x30;  
    buff[2] = data%10+0x30;
	if(_txif)						//判断发送数据寄存器为空
	{   
		for(i=0;i<3;i++)
		{
		_txr_rxr=buff[i];				//写入TXR--------清标志位TXIF，TXIF=1标志TXR写入TSR,0标志禁止写入TXR中已有数据
		while(!_txif);				//等待数据写入TSR
		while(!_tidle);
		}				//等待数据传输结束
	}
}

//发送单个字符
void UART_SendChar_int(int data)
{
	int buff[4];
    uchar i;
    
    buff[0] = (data/1000)%10+0x30;
    buff[1] = (data/100)%10+0x30;  
    buff[2] = (data/10)%10+0x30;  
    buff[3] = data%10+0x30;
	if(_txif)						//判断发送数据寄存器为空
	{   
		for(i=0;i<4;i++)
		{
		_txr_rxr=buff[i];				//写入TXR--------清标志位TXIF，TXIF=1标志TXR写入TSR,0标志禁止写入TXR中已有数据
		while(!_txif);				//等待数据写入TSR
		while(!_tidle);
		}				//等待数据传输结束
	}
}

//发送字符串
void SendString(uchar *ch)
{
	while(*ch!=0)
	{
		send_command(*(ch++));	
	}	
	
}


//发送处理
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
  
  	if(_txif)						//判断发送数据寄存器为空
	{
		_txr_rxr=com;				//写入TXR--------清标志位TXIF，TXIF=1标志TXR写入TSR,0标志禁止写入TXR中已有数据
		while(!_txif);				//等待数据写入TSR
		while(!_tidle);				//等待数据传输结束
	}
}

//接收处理
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
