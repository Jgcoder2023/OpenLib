#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint; 
typedef unsigned long ulong;
typedef void* any;


typedef enum{
	none = 0,  //没有错误
	full,      //队列已满
	empty      //队列为空
}err;


struct Fun;
typedef struct{
	any *Menory;    //存储数据的存储空间指针
	any *Start;   //队列开始的指针
	any *End;     //队列结束的指针
	any *In;      //队列插入消息的指针
	any *Out;    //队列取出消息的指针
	uint Size;   //队列的大小
	uint Num;    //队列当前条数
}Queue;

Queue* NewQueue(uint Size);
void DelQueue(Queue* Queue);
err ReceiveMsg(Queue* Queue,any* msg);
err SendFirstMsg(Queue* Queue,any msg);
err SendMsg(Queue* Queue,any msg);
#endif 



