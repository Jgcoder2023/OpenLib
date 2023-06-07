#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>

typedef unsigned char uchar;
typedef unsigned int uint; 
typedef unsigned long ulong;
typedef void* any;


typedef enum{
	none = 0,  //û�д���
	full,      //��������
	empty      //����Ϊ��
}err;


struct Fun;
typedef struct{
	any *Menory;    //�洢���ݵĴ洢�ռ�ָ��
	any *Start;   //���п�ʼ��ָ��
	any *End;     //���н�����ָ��
	any *In;      //���в�����Ϣ��ָ��
	any *Out;    //����ȡ����Ϣ��ָ��
	uint Size;   //���еĴ�С
	uint Num;    //���е�ǰ����
}Queue;

Queue* NewQueue(uint Size);
void DelQueue(Queue* Queue);
err ReceiveMsg(Queue* Queue,any* msg);
err SendFirstMsg(Queue* Queue,any msg);
err SendMsg(Queue* Queue,any msg);
#endif 



