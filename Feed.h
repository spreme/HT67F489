#ifndef __FEED_H__
#define __FEED_H__

#define FEED_MAX_NUM 4 //定时喂食最大条数

struct feed_record {
	u8 hour;
	u8 minute;
	u8 quantity;		//喂食量
	u8 music;
};

u8 feed_run(struct feed_record *info);
void feed_scan(struct feed_record *feed);
extern u8 feed_going  ;
#endif