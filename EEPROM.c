#include "HT67F489.h"
#include "init_ht67f489.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "UART.h"
#include "LCD.h"

//E2PROM–¥»Î
void e2prom_write(uchar adr,uchar dat)
{
  _emi=0;
  _eea=adr;
  _eed=dat;
  _mp1l=0x40;
  _mp1h=0x01;
  //_wren=1;
  //_wr=1;
  _iar1=_iar1|0x08;
  _iar1=_iar1|0x04;
  while(_iar1&0x04){
  	_nop();
  	_nop();
  	_nop();
  }
  //_wren=0;
  _iar1=0;
  _mp1h=0x00;
  _emi=1;
}



//∂¡E2PROM
uchar e2prom_read(uchar adr)
{
  _emi=0;
  _eea=adr;
  _eed=0;
  _mp1l=0x40;
  _mp1h=0x01;
  //_rden=1;
  //_rd=1;
  _iar1=_iar1|0x02;
  _iar1=_iar1|0x01;
  while(_iar1&0x01){
  	_nop();
  	_nop();
  	_nop();
  }
  //_rden=0;
  _iar1=0;
  _mp1h=0x00;
  _emi=1;
  return _eed;
}

void e2prom_init()
{ 
	u8 i =0;
	if(e2prom_read(2) ==255)
	{
		for(i=0;i<33;i++)
		{
		  e2prom_write(i,0)	;
		}
	}	
}