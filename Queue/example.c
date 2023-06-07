#include "queue.h"



Queue* queue;   //定义一个存储队列的指针变量


void main(void){
	//创建一个长度为10的队列
	queue = NewQueue(10);

	//要发送的消息
	uint8_t pmsg[] = "123"; 
	uint8_t pmsg2[] = "456";

	//发送普通消息到队列
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);

	SendFirstMsg(queue,(any)pmsg2);     //发送优先级消息到队列

	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);


	while (1){
		any msg;  //定义接受消息的变量
		err errs = ReceiveMsg(queue,&msg); //接收消息
		if(errs != none){
			//没有获取到消息
			printf("no data \r\n");
		}else{
			//成功获取消息     （已默认单片机支持printf方法）
			printf("msg=%s \r\n",(uint8_t *)msg);
		}
	}
	
}