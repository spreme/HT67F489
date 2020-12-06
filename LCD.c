//====================================================//
//													  //
//         本程序为定制液晶的使用方式，仅供参考		  //
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

//uchar adress;
//uchar data;


/******************************************/



void lcd_fill_sr()//全屏显示
{
	_emi=0;
	_mp1h = 0x01;    //sector
    _mp1l = 0x80;
    _iar1 |=0x01 ;//dianchi
    _iar1 |=0x02 ;//dianchi_4
    _iar1 |=0x04 ;//dianchi_3
    _iar1 |=0x08 ;//dianchi_2
       
    _mp1l = 0x81;//1_8
    _iar1 |=0x01 ;
    _iar1 |=0x02 ;//1_6
    _iar1 |=0x04 ;//1_5
    _iar1 |=0x08 ;//1_8
    
    _mp1l = 0x82;
    _iar1 |=0x01 ;//1_2
    _iar1 |=0x02 ;//1_7
    _iar1 |=0x04 ;//1_3
    _iar1 |=0x08 ;//dianchi1 
   
     _mp1l = 0x83;
    _iar1 |=0x01 ;//2_1
    _iar1 |=0x02 ;//2_6
    _iar1 |=0x04 ;//2_5*/
    _iar1 |=0x08 ;//2_4
    
     
     _mp1l = 0x84;
     _iar1 |=0x01 ;//2_2
     _iar1 |=0x02 ;//2_7
     _iar1 |=0x04 ;//2_3
     _iar1 |=0x08 ;//col
    
     
    _mp1l = 0x85;
    _iar1 =0x01 ;//3_1
    _iar1 |=0x02 ;//3_6
    _iar1 |=0x04 ;//3_5
    _iar1|=0x08 ;//3_4
     
     
    _mp1l = 0x86;
    _iar1 |=0x01 ;//3_2
    _iar1 |=0x02 ;//3_7
    _iar1 |=0x04 ;//3_3
    _iar1|=0x08 ;//meal
    
    
    _mp1l = 0x87;        
    _iar1 |=0x01 ;//4_1
    _iar1 |=0x02 ;//4_6
    _iar1 |=0x04 ;//4_5
    _iar1 |=0x08 ;//4_4
    
    _mp1l = 0x88;        
    _iar1 |=0x01 ;//4_2
    _iar1 |=0x02 ;//4_7
    _iar1 |=0x04 ;//4_3
    _iar1 |=0x08 ;//1
    
    _mp1l = 0x89;   
    _iar1 |=0x01 ;//5_1
    _iar1 |=0x02 ;//5_6
    _iar1 |=0x04 ;//5_8
    _iar1 |=0x08 ;//5_4
    
    _mp1l = 0x8a;   
    _iar1 |=0x01 ;//5_2
    _iar1 |=0x02 ;//5_7
    _iar1 |=0x04 ;//5_3
    //_iar1 |=0x08 ;
    
    _mp1l = 0x8b;
    _iar1|=0x01 ;//lock_on  
    _iar1|=0x02 ;//portion        
    _iar1|=0x04 ;//4
    //_iar1|=0x08 ;*/
    
    _mp1l = 0x8c;//
    _iar1|=0x01 ;//lock_off   
    _iar1|=0x02 ;//lock   
    _iar1|=0x04 ;//3   
    _iar1|=0x08 ;//2 
    
    _mp1h = 0x00;
	_emi=1;
}



//LCD显示时间表
void rtc_lcd()
{
//	_mp1h = 0x01;    //sector
    
   
	  if((rtc_date.minute %10) == 0)
	  {
	  	lcd_4_clr;
	  	lcd_4_0  ;
	   
	  }else if((rtc_date.minute %10) == 1){
	  	
	  /*1*/
	    lcd_4_clr;
	    lcd_4_1  ;
	    
	  	
	  }else if((rtc_date.minute %10) == 2){
	    /*2*/
	    lcd_4_clr;
	    lcd_4_2  ;
	   
	   	
	  }else if((rtc_date.minute %10) == 3){
	 	/*3*/
	    lcd_4_clr;
	    lcd_4_3  ;
	   
		
	  }else if((rtc_date.minute %10) == 4){
	    /*4*/
	    lcd_4_clr;
	    lcd_4_4  ;
	  
		
	  }else if((rtc_date.minute %10) == 5){
	    /*5*/
	   lcd_4_clr;
	   lcd_4_5 ;
	   
		
	  }else if((rtc_date.minute %10) == 6){
	    /*6*/
	    lcd_4_clr;
	    lcd_4_6  ;
	   
		
	 }else if((rtc_date.minute %10) == 7){
	    /*7*/
	    lcd_4_clr;
	    lcd_4_7  ;
	   
		
	  }else if((rtc_date.minute %10 )== 8){
	   /*8*/
	    lcd_4_clr;
	    lcd_4_8  ;
	   
		
	  }else if((rtc_date.minute %10) == 9){
        lcd_4_clr;
        lcd_4_9  ;
	  
		
	  }
	
	if((rtc_date.minute/10) == 0 )
	 {
	  /*0*/
	  lcd_3_clr;
	  lcd_3_0  ;
      
	 	
	 }else if((rtc_date.minute/10) == 1 ){
	 /*1*/
      lcd_3_clr;
      lcd_3_1  ;      
     
	 		 	
	 }else if((rtc_date.minute/10) == 2 ){
	 /*2*/
	  lcd_3_clr; 
	  lcd_3_2 ;
     
	 		 	
	 }else if((rtc_date.minute/10) == 3 ){
	 /*3*/
	  lcd_3_clr;  
	  lcd_3_3  ;
      
	 	
	 }else if((rtc_date.minute/10) == 4 ){
	 /*4*/
	  lcd_3_clr; 
	  lcd_3_4  ;
     
	 		 	
	 }else if((rtc_date.minute/10) == 5 ){
	 /*5*/
	  lcd_3_clr;
	  lcd_3_5  ;
      
	 		 	
	 }
	 
	 if((rtc_date.hour %10) == 0)
	  {
	    lcd_2_clr;
	    /*0*/
	    lcd_2_0  ;
	   
    

	  }else if((rtc_date.hour %10) == 1){
	  	
	  /*1*/
	     lcd_2_clr;
	     lcd_2_1  ;
	   
	  	
	  }else if((rtc_date.hour %10) == 2){
	    /*2*/
	     lcd_2_clr;
	     lcd_2_2  ;
	     
	   	
	  }else if((rtc_date.hour %10) == 3){
	 	/*3*/
	     lcd_2_clr;
	     lcd_2_3  ;
	     
	  }else if((rtc_date.hour %10) == 4){
	    /*2*/
	     lcd_2_clr;
	     lcd_2_4  ;
	     
	   	
	  }else if((rtc_date.hour %10) == 5){
	 	/*3*/
	     lcd_2_clr;
	     lcd_2_5  ;
	     
	  }else if((rtc_date.hour %10) == 6){
	    /*2*/
	     lcd_2_clr;
	     lcd_2_6  ;
	     
	   	
	  }else if((rtc_date.hour %10) == 7){
	 	/*3*/
	     lcd_2_clr;
	     lcd_2_7  ;
	     
	  }else if((rtc_date.hour %10) == 8){
	    /*2*/
	     lcd_2_clr;
	     lcd_2_8  ;
	     
	   	
	  }else if((rtc_date.hour %10) == 9){
	 	/*3*/
	     lcd_2_clr;
	     lcd_2_9  ;
	     
	  }
	  
	  
	
	  if((rtc_date.hour/10) == 0 )
	 {
	  /*0*/
	     lcd_1_clr;
	     lcd_1_0  ;
       
	 	
	 }else if((rtc_date.hour/10) == 1 ){
	 /*1*/
        lcd_1_clr;  
        lcd_1_1  ;         
	   
	 		 	
	 }else if((rtc_date.hour/10) == 2 ){
	 /*2*/
	    lcd_1_clr;   
	    lcd_1_2  ;
        
	 }		 	
	 

}







void LCD_clrscreen()
{
  lcd_1_clr;
  lcd_2_clr;
  lcd_3_clr;
  lcd_4_clr;
  lcd_5_clr;
  lcd_num_off;
  meal_off ;
  portion_off ;  
  lock_clr ;
  col_off  ;
  power_clr;
}

