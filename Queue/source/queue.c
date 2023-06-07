#include "queue.h"

//插入普通消息
err SendMsg(Queue* Queue,any msg){
	if(Queue->Num >= Queue->Size){
		return full;
	}
	*Queue->In++ = msg;
	Queue->Num++;
	//是否已到结尾
	if(Queue->In == Queue->End){
		Queue->In = Queue->Start;
	}
	return none;
}


//插入优先消息
err SendFirstMsg(Queue* Queue,any msg){
	if(Queue->Num >= Queue->Size){
		return full;
	}
	if(Queue->Out == Queue->Start){
		Queue->Out = Queue->End;
	}
	Queue->Out--;
	*Queue->Out = msg;
	Queue->Num++;
	return none;
}


//消费消息
err ReceiveMsg(Queue* Queue,any* msg){
	if(Queue->Num <= 0){
		return empty;
	}
	*msg = *Queue->Out++;
	Queue->Num--;
	if(Queue->Out == Queue->End){
       Queue->Out = Queue->Start;
    }
	return none;
}


//删除队列
void DelQueue(Queue* Queue){
	free(Queue->Menory);
	free(Queue);
}	


//初始化队列
//参数： 队列最大长度
Queue* NewQueue(uint Size){
	Queue* newQueue = (Queue*)malloc(sizeof(Queue));
	newQueue->Menory = (any*)malloc(Size * sizeof(any));
	newQueue->Start = newQueue->Menory;
	newQueue->End = &newQueue->Menory[Size];
	newQueue->In = newQueue->Menory;
	newQueue->Out = newQueue->Menory;
	newQueue->Size = Size;
	newQueue->Num = 0;
	return newQueue;
}






