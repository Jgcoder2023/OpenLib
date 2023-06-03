#include "timer.h"

ulong Tick = 0;   //ϵͳ������
uchar TickCycle = 0; //������������
TimeList* HeadNode = NULL; //ͷ���ڵ�
TimeList* FootNode = NULL; //β���ڵ�

//����һ���洢�ڵ�
void AddTimerNode(TimeValue* timeValue){
	TimeList* p = HeadNode;
	TimeList* InsertNode = FootNode;  //Ѱ�Һ��ʵĲ���ڵ�,���û�о�β��
	TimeList* NewNode = (TimeList*)malloc(sizeof(TimeList));
	if(NewNode == NULL){
		return;  //˵�������ڴ�ʧ��
	}
	//�ж��Ƿ���ͷ�ڵ�
	if(HeadNode == NULL){
		HeadNode = NewNode;
		FootNode = NewNode;
		NewNode->prev = NULL;
		NewNode->next = NULL;
	}else{
		//Ѱ�Һ��ʵĲ���ڵ�   ����
		while(p != NULL){
			if(p->Data->TimingTime > timeValue->TimingTime){
				InsertNode = p;
				break;
			}
			p = p->next;
		}
		if(InsertNode == HeadNode){
			//ͷ��
			NewNode->next = InsertNode;
			InsertNode->prev = NewNode;
			HeadNode = NewNode;
		}else if(InsertNode == FootNode){
			//β��
			NewNode->next = NULL;
			NewNode->prev = InsertNode;
			InsertNode->next = NewNode;
			FootNode = NewNode;
		}else{
			//�м����
			NewNode->next = InsertNode;
			InsertNode->prev->next = NewNode;
		}
	}
	NewNode->Data = timeValue;
}

//���һ����ʱ��
TimeValue* AddTime(uint TimingTime,uint RunNum,any Data,void(*TimerCallBack)(any)){
	TimeValue* NewTime = (TimeValue*)malloc(sizeof(TimeValue));
	if(NewTime == NULL){
		return NULL;  //˵�������ڴ�ʧ��
	}
	NewTime->TimingTime = TimingTime;
	NewTime->TimeOut = Tick + TimingTime;
	NewTime->TimeOutCycle = TickCycle;
	NewTime->RunNum = RunNum;
	NewTime->Forever = (RunNum==0)?ON:OFF;
	NewTime->Data = Data;
	NewTime->TimerCallBack = TimerCallBack;
	NewTime->IsCmd = ON;
	//�����������
	AddTimerNode(NewTime);
	return NewTime;
}


//ɾ����ʱ��
void DelTime(TimeValue* timeNode){
	TimeList* p = HeadNode;
	while(p != NULL){
		if(p->Data == timeNode){
			break;
		}
		p = p->next;
	}
	//����ȷ��
	if(p->Data != timeNode){
		return;
	}
	//��ʼɾ��
	if(p == HeadNode){
		//ͷ��ɾ��
		HeadNode = p->next;
		p->next->prev = NULL;
	}else if(p == FootNode){
		//β��ɾ��
		FootNode = p->prev;
		p->prev->next = NULL;
	}else{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p->Data);
	free(p);
}

//����
void HeartTimer(void){
	Tick++;
	if(Tick==0){
		TickCycle++;
	}
}

//����
void ActivityTimer(void){
	TimeList* p = HeadNode;
	uchar is_run = OFF;
	while(p != NULL){
		//�Ƿ�ʹ��
		if(p->Data->IsCmd == OFF){
			p = p->next;
			continue;
		}
		//�Ƿ�ͬһ����ʱ����
		if(p->Data->TimeOutCycle != TickCycle){
			p = p->next;
			continue;
		}
		if(p->Data->Forever == ON){//ֱ��ִ��
			is_run = ON;
		}else{
			if(p->Data->RunNum > 0){is_run = ON;}
		}
		if(Tick >= p->Data->TimeOut && is_run == ON){
			//���ó�ʱʱ��
			p->Data->TimeOut = Tick + p->Data->TimingTime;
			if(p->Data->TimeOut < Tick){p->Data->TimeOutCycle++;}  //��������
			if(p->Data->RunNum > 0){p->Data->RunNum--;}
			p->Data->TimerCallBack(p->Data->Data);
		}else{
			TimerIdle();
		}
		p = p->next;
	}
}

//��ͣ��ʱ��
void PauseTime(TimeValue* timeNode){
	timeNode->IsCmd = OFF;
}
//������ʱ��
void RestartTime(TimeValue* timeNode){
	timeNode->IsCmd = ON;
}

//�����������Ķ�ʱ��(��ʱ��ֹͣ���������)
void RestartTimeNum(TimeValue* timeNode,uint RunNum){
	if(timeNode->RunNum == 0 && timeNode->Forever == OFF){
		timeNode->RunNum = RunNum;
	}
}


//һ�����������ڵĿ��к���
__weak void TimerIdle(void){}

//��ʼ����ʱ��
Timer* TimerInit(void){
	Timer* time = (Timer*)malloc(sizeof(Timer));
	if(time == NULL){
		return NULL;
	}
	time->Add = AddTime;
	time->Del = DelTime;
	time->Pause = PauseTime;
	time->Restart = RestartTime;
	time->RestartTimeNum = RestartTimeNum;
	return time;
}



