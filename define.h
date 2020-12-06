#ifndef __DEFINE_H__
#define __DEFINE_H__

//UART
extern uchar uart_flag;               
extern uchar com_pos;
extern uchar rx_com[7];			   
extern uchar rx_pos;
extern uchar rx_flag;




extern uint k;//voltage 		//（原）

//extern uchar Count;
//lock：锁	portion：时分分界冒号			meal：菜单	col：		power：电源
//==============LCD显示定义===================//
#define portion_on  do{_mp1h=1;_mp1l = 0x8b; _iar1 |=0x02 ;_mp1h=0;}while(0)  //portion
#define portion_off do{_mp1h=1;_mp1l = 0x8b; _iar1 &=~0x02 ;_mp1h=0;}while(0)  
#define lock_on     do{_mp1h=1;_mp1l = 0x8b; _iar1 |=0x01;_mp1l = 0x8c;_iar1 |=0x02 ;_mp1h=0;}while(0) 
#define lock_off    do{_mp1h=1;_mp1l = 0x8c; _iar1 |=0x03 ;_mp1h=0;}while(0)  //lock_off  
#define lock_clr    do{_mp1h=1;_mp1l = 0x8b; _iar1 &= ~0x01;_mp1l = 0x8c;_iar1 &= ~0x03 ;_mp1h=0;}while(0)    

#define meal_on     do{_mp1h=1;_mp1l = 0x86;_iar1 |= 0x08; _mp1h=0;}while(0)
#define meal_off    do{_mp1h=1;_mp1l = 0x86;_iar1 &= ~0x08; _mp1h=0;}while(0)  
#define col_on      do{_mp1h=1;_mp1l = 0x84;_iar1 |= 0x08 ; _mp1h=0;}while(0)
#define col_off     do{_mp1h=1;_mp1l = 0x84;_iar1 &= ~0x08 ; _mp1h=0;}while(0)

#define power_0     do{_mp1h=1;_mp1l = 0x80; _iar1 |=0x01 ;_mp1h=0;}while(0)  
#define power_1     do{_mp1h=1;_mp1l = 0x82; _iar1 |=0x08 ;_mp1h=0;}while(0) 
#define power_2     do{_mp1h=1;_mp1l = 0x80; _iar1 |=0x08 ;_mp1h=0;}while(0)  
#define power_3     do{_mp1h=1;_mp1l = 0x80; _iar1 |=0x04 ;_mp1h=0;}while(0)  
#define power_4     do{_mp1h=1;_mp1l = 0x80; _iar1 |=0x02 ;_mp1h=0;}while(0) 
 
#define power_0_clr     do{_mp1h=1;_mp1l = 0x80; _iar1 &= ~0x01 ;_mp1h=0;}while(0)  
#define power_1_clr     do{_mp1h=1;_mp1l = 0x82; _iar1 &= ~0x08 ;_mp1h=0;}while(0) 
#define power_2_clr     do{_mp1h=1;_mp1l = 0x80; _iar1 &= ~0x08 ;_mp1h=0;}while(0)  
#define power_3_clr     do{_mp1h=1;_mp1l = 0x80; _iar1 &= ~0x04 ;_mp1h=0;}while(0)  
#define power_4_clr     do{_mp1h=1;_mp1l = 0x80; _iar1 &= ~0x02 ;_mp1h=0;}while(0)  
#define power_clr       do{_mp1h=1;_mp1l = 0x80; _iar1 &= ~0x0f ; _mp1l = 0x82; _iar1 &= ~0x08;_mp1h=0;}while(0)  
 
#define lcd_1     do{_mp1h=1;_mp1l = 0x88;_iar1 |= 0x08 ; _mp1h=0;}while(0)
#define lcd_2     do{_mp1h=1;_mp1l = 0x8c;_iar1 |= 0x08 ; _mp1h=0;}while(0)
#define lcd_3     do{_mp1h=1;_mp1l = 0x8c;_iar1 |= 0x04 ; _mp1h=0;}while(0)
#define lcd_4     do{_mp1h=1;_mp1l = 0x8b;_iar1 |= 0x04 ; _mp1h=0;}while(0)
//#define lcd_clean     do{_mp1h=1;_mp1l = 0x88;_iar1 &= ~0x08 ;_mp1l = 0x8c;_iar1 &=~ 0x08 ;_iar1 &= ~0x04 ;_mp1l = 0x8b;_iar1 &= ~0x04 ; _mp1h=0;}while(0)
#define lcd_num_off do{_mp1h=1;_mp1l = 0x8c;_iar1 &= ~0x0c ;_mp1l = 0x88;_iar1 &= ~0x08 ;_mp1l = 0x8b;_iar1 &= ~0x04 ; _mp1h=0;}while(0)

#define lcd_4_0     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0f ;_mp1l = 0x88;_iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_4_1     do{_mp1h=1;_mp1l = 0x88;_iar1 |= 0x05 ; _mp1h=0;}while(0)
#define lcd_4_2     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0d ;_mp1l = 0x88; _iar1 |=0x03 ; _mp1h=0;}while(0)
#define lcd_4_3     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x09 ;_mp1l = 0x88; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_4_4     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x02 ;_mp1l = 0x88; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_4_5     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0b ;_mp1l = 0x88; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_4_6     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0f ;_mp1l = 0x88; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_4_7     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x01 ;_mp1l = 0x88; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_4_8     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0f ;_mp1l = 0x88; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_4_9     do{_mp1h=1;_mp1l = 0x87;_iar1 |= 0x0b ;_mp1l = 0x88; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_4_clr   do{_mp1h=1;_mp1l = 0x87;_iar1 &=~0x0f ;_mp1l = 0x88; _iar1 &=~0x07; _mp1h=0;}while(0)

#define lcd_3_0     do{_mp1h=1;_mp1l = 0x85;_iar1 |= 0x0f ;_mp1l = 0x86; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_3_1     do{_mp1h=1;_mp1l = 0x86;_iar1 |= 0x05 ;_mp1h=0;}while(0)
#define lcd_3_2     do{_mp1h=1;_mp1l = 0x85;_iar1 |= 0x0d ;_mp1l = 0x86; _iar1 |=0x03 ; _mp1h=0;}while(0)
#define lcd_3_3     do{_mp1h=1;_mp1l = 0x85;_iar1 |= 0x09 ;_mp1l = 0x86; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_3_4     do{_mp1h=1;_mp1l = 0x85;_iar1 |= 0x02 ;_mp1l = 0x86; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_3_5     do{_mp1h=1;_mp1l = 0x85;_iar1 |= 0x0b ;_mp1l = 0x86; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_3_clr   do{_mp1h=1;_mp1l = 0x85;_iar1 &=~0x0f ;_mp1l = 0x86; _iar1 &=~0x07; _mp1h=0;}while(0)

#define lcd_2_0     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0f ;_mp1l = 0x84; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_2_1     do{_mp1h=1;_mp1l = 0x84; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_2_2     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0d ;_mp1l = 0x84; _iar1 |=0x03 ; _mp1h=0;}while(0)
#define lcd_2_3     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x09 ;_mp1l = 0x84; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_2_4     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x02 ;_mp1l = 0x84; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_2_5     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0b ;_mp1l = 0x84; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_2_6     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0f ;_mp1l = 0x84; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_2_7     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x01 ;_mp1l = 0x84; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_2_8     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0f ;_mp1l = 0x84; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_2_9     do{_mp1h=1;_mp1l = 0x83;_iar1 |= 0x0b ;_mp1l = 0x84; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_2_clr   do{_mp1h=1;_mp1l = 0x83;_iar1 &=~0x0f ;_mp1l = 0x84; _iar1 &=~0x07; _mp1h=0;}while(0)

#define lcd_1_0     do{_mp1h=1;_mp1l = 0x81;_iar1 |= 0x0f;_mp1l = 0x82; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_1_1     do{_mp1h=1;_mp1l = 0x82;_iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_1_2     do{_mp1h=1;_mp1l = 0x81;_iar1 |=0x0d ; _mp1l = 0x82; _iar1 |=0x03 ; _mp1h=0;}while(0)
#define lcd_1_clr   do{_mp1h=1;_mp1l = 0x81;_iar1 &=~0x0f;_mp1l = 0x82; _iar1 &=~0x07; _mp1h=0;}while(0)

#define lcd_5_0     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0f ;_mp1l = 0x8a; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_5_1     do{_mp1h=1;_mp1l = 0x8a; _iar1|=0x05 ; _mp1h=0;}while(0)
#define lcd_5_2     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0d ;_mp1l = 0x8a; _iar1 |=0x03 ; _mp1h=0;}while(0)
#define lcd_5_3     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x09 ;_mp1l = 0x8a; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_5_4     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x02 ;_mp1l = 0x8a; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_5_5     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0b ;_mp1l = 0x8a; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_5_6     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0f ;_mp1l = 0x8a; _iar1 |=0x06 ; _mp1h=0;}while(0)
#define lcd_5_7     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x01 ;_mp1l = 0x8a; _iar1 |=0x05 ; _mp1h=0;}while(0)
#define lcd_5_8     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0f ;_mp1l = 0x8a; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_5_9     do{_mp1h=1;_mp1l = 0x89;_iar1 |= 0x0b ;_mp1l = 0x8a; _iar1 |=0x07 ; _mp1h=0;}while(0)
#define lcd_5_clr   do{_mp1h=1;_mp1l = 0x89;_iar1 &= ~0x0f ;_mp1l = 0x8a; _iar1 &= ~0x07 ; _mp1h=0;}while(0)


//==============LED灯控制引脚定义===================//
#define  	LED_B  				    _pa3 
#define  	MOTOR_EN  				_pa7 			//电机     
#define  	RECODE_LED  			_pe6			//红灯
#define  	PWR_LED  				_pe4			//电源灯
//#define  	RECODE_LED  			_pe4			//红灯
//#define  	PWR_LED  				_pe6			//电源灯
#define  	LED_G  					_pe7
#define  	Key_Set  				_pf6

/*#define  	Key_Play  				_pa6//_pf7
#define  	Key_Record  			_pa0
#define  	Key_UP  				_pa2
#define     Key_Down                _pf7//_pa6
#define     BUZZER                  _pb2//_t2cp //;//_pe5
*/
#define  	Key_Play  				_pa2//_pf7
#define  	Key_Record  			_pa6//_pa0
#define  	Key_UP  				_pf7//_pa2
#define     Key_Down                _pa0//_pa6
#define     BUZZER                  _pb2			//铚傞福鍣?

#define     LED_R                   _pb5//		         
#define     MOTOR_DET               _pb4
#define     BL_EN                   _pb3
#define     ISD1820_REC             _pc5//_pb2
#define     ISD1820_PLAYE           _pc6//_pb1
#define     DC_DET                  _pc7

//==============数码管控制引脚定义===================//
//#define   SEG_0         _pd0 
//#define   SEG_1         _pd1        
//#define   SEG_2         _pd2  
//#define   SEG_3         _pd3  
//#define   SEG_4         _pd4
//#define   SEG_5         _pd5
//#define   SEG_6         _pd6
//#define   SEG_7         _pd7
//#define   SEG_8         _pc0
//#define   SEG_9         _pc1
//#define   SEG_10        _pc2
//#define   SEG_11        _pc3
//#define   SEG_12        _pc4
//
//#define   COM_1         _pe0  
//#define   COM_2         _pc1 
//#define   COM_3         _pc2 
//#define   COM_4         _pc3  


#define     SET           0X01                //1：SET
#define     RESET         0X00                //0：RESET
#define     sheep_time    8000
#define     meal_time     6000
#define     LED_ON                    0
#define     LED_OFF                   1
#define     IR_LED_ON                 1
#define     IR_LED_OFF                0
#define     BUZZER_ON                 1
#define     BUZZER_OFF                0      


/****************************************************************************************/
typedef enum
{
  GPIO_Pin_0    = ((uchar)0x01),   /*!< Pin 0 selected */
  GPIO_Pin_1    = ((uchar)0x02),   /*!< Pin 1 selected */
  GPIO_Pin_2    = ((uchar)0x04),   /*!< Pin 2 selected */
  GPIO_Pin_3    = ((uchar)0x08),   /*!< Pin 3 selected */
  GPIO_Pin_4    = ((uchar)0x10),   /*!< Pin 4 selected */
  GPIO_Pin_5    = ((uchar)0x20),   /*!< Pin 5 selected */
  GPIO_Pin_6    = ((uchar)0x40),   /*!< Pin 6 selected */
  GPIO_Pin_7    = ((uchar)0x80),   /*!< Pin 7 selected */
  GPIO_Pin_LNib = ((uchar)0x0F),   /*!< Low nibble pins selected */
  GPIO_Pin_HNib = ((uchar)0xF0),   /*!< High nibble pins selected */
  GPIO_Pin_All  = ((uchar)0xFF)    /*!< All pins selected */
}GPIO_Pin_TypeDef;

typedef enum
{
  GPIO_Mode_INT      = (uchar)0x01,   
  GPIO_Mode_OUT      = (uchar)0x00,  

}GPIO_Mode_TypeDef;

#endif
