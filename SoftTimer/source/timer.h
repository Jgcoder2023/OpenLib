#ifndef TIMER_H__
#define TIMER_H__

#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint; 
typedef unsigned long ulong;
typedef void* any;

//开关量的枚举
typedef enum{
	OFF = 0,
	ON = 1
}Sw;

//定时器的各项参数
typedef struct{
	ulong TimingTime;   //定时时间
	ulong TimeOut;  //超时时间
	uchar TimeOutCycle;  //超时周期
	Sw Forever;  //是否永远执行
	uint RunNum;  //执行次数    0-65535
	any Data;       //可以携带一个255以内的参数
	void (*TimerCallBack)(any);  //超时回调函数
	Sw IsCmd;     //是否使能
}TimeValue;

typedef struct{
	//添加定时器
	TimeValue*(*Add)(uint TimingTime,uint RunNum,any Data,void(*TimerCallBack)(any));
	void(*Del)(TimeValue* time);
	void (*Pause)(TimeValue* timeNode);
	void (*Restart)(TimeValue* timeNode);
}Timer;

//定时器链表
struct TimeList;
typedef struct TimeList{
	struct TimeList* prev;  //上一个节点
	struct TimeList* next;  //下一个节点
	TimeValue* Data;  //本节点数据
}TimeList;

__weak void TimerIdle(void);
Timer* TimerInit(void);
void HeartTimer(void);
void ActivityTimer(void);


#endif

