#ifndef	__SOUND_ISD1820_H
#define	__SOUND_ISD1820_H


void sound_rec(void);
void sound_play(void);
extern u8 ISD1820_REC_TIME;
extern u8 REC_TIME_flag ;
extern u8 buzzer_detect ;
extern u8 voltage_low ;

#endif
