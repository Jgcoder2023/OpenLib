#include "queue.h"

//������ͨ��Ϣ
err SendMsg(Queue* Queue,any msg){
	if(Queue->Num >= Queue->Size){
		return full;
	}
	*Queue->In++ = msg;
	Queue->Num++;
	//�Ƿ��ѵ���β
	if(Queue->In == Queue->End){
		Queue->In = Queue->Start;
	}
	return none;
}


//����������Ϣ
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


//������Ϣ
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


//ɾ������
void DelQueue(Queue* Queue){
	free(Queue->Menory);
	free(Queue);
}	


//��ʼ������
//������ ������󳤶�
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






