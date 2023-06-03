#ifndef TIMER_H__
#define TIMER_H__

#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint; 
typedef unsigned long ulong;
typedef void* any;

//��������ö��
typedef enum{
	OFF = 0,
	ON = 1
}Sw;

//��ʱ���ĸ������
typedef struct{
	ulong TimingTime;   //��ʱʱ��
	ulong TimeOut;  //��ʱʱ��
	uchar TimeOutCycle;  //��ʱ����
	Sw Forever;  //�Ƿ���Զִ��
	uint RunNum;  //ִ�д���    0-65535
	any Data;       //����Я��һ��255���ڵĲ���
	void (*TimerCallBack)(any);  //��ʱ�ص�����
	Sw IsCmd;     //�Ƿ�ʹ��
}TimeValue;

typedef struct{
	//��Ӷ�ʱ��
	TimeValue*(*Add)(uint TimingTime,uint RunNum,any Data,void(*TimerCallBack)(any));
	void(*Del)(TimeValue* time);
	void (*Pause)(TimeValue* timeNode);
	void (*Restart)(TimeValue* timeNode);
}Timer;

//��ʱ������
struct TimeList;
typedef struct TimeList{
	struct TimeList* prev;  //��һ���ڵ�
	struct TimeList* next;  //��һ���ڵ�
	TimeValue* Data;  //���ڵ�����
}TimeList;

__weak void TimerIdle(void);
Timer* TimerInit(void);
void HeartTimer(void);
void ActivityTimer(void);


#endif

