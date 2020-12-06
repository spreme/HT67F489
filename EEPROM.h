#ifndef __EEPROM_H__
#define __EEPROM_H__

extern uchar Show_rx[6];

void e2prom_write(uchar adr,uchar dat);
uchar e2prom_read(uchar adr);
void e2prom_init();
//void e2prom_write_show();
//void e2prom_write_empty();
//void e2prom_read_show();

#endif