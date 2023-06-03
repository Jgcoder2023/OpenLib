#include "timer.h"

ulong Tick = 0;   //系统节拍数
uchar TickCycle = 0; //完整节拍周期
TimeList* HeadNode = NULL; //头部节点
TimeList* FootNode = NULL; //尾部节点

//申请一个存储节点
void AddTimerNode(TimeValue* timeValue){
	TimeList* p = HeadNode;
	TimeList* InsertNode = FootNode;  //寻找合适的插入节点,如果没有就尾插
	TimeList* NewNode = (TimeList*)malloc(sizeof(TimeList));
	if(NewNode == NULL){
		return;  //说明申请内存失败
	}
	//判断是否是头节点
	if(HeadNode == NULL){
		HeadNode = NewNode;
		FootNode = NewNode;
		NewNode->prev = NULL;
		NewNode->next = NULL;
	}else{
		//寻找合适的插入节点   排序
		while(p != NULL){
			if(p->Data->TimingTime > timeValue->TimingTime){
				InsertNode = p;
				break;
			}
			p = p->next;
		}
		if(InsertNode == HeadNode){
			//头插
			NewNode->next = InsertNode;
			InsertNode->prev = NewNode;
			HeadNode = NewNode;
		}else if(InsertNode == FootNode){
			//尾插
			NewNode->next = NULL;
			NewNode->prev = InsertNode;
			InsertNode->next = NewNode;
			FootNode = NewNode;
		}else{
			//中间插入
			NewNode->next = InsertNode;
			InsertNode->prev->next = NewNode;
		}
	}
	NewNode->Data = timeValue;
}

//添加一个定时器
TimeValue* AddTime(uint TimingTime,uint RunNum,any Data,void(*TimerCallBack)(any)){
	TimeValue* NewTime = (TimeValue*)malloc(sizeof(TimeValue));
	if(NewTime == NULL){
		return NULL;  //说明申请内存失败
	}
	NewTime->TimingTime = TimingTime;
	NewTime->TimeOut = Tick + TimingTime;
	NewTime->TimeOutCycle = TickCycle;
	NewTime->RunNum = RunNum;
	NewTime->Forever = (RunNum==0)?ON:OFF;
	NewTime->Data = Data;
	NewTime->TimerCallBack = TimerCallBack;
	NewTime->IsCmd = ON;
	//加入链表管理
	AddTimerNode(NewTime);
	return NewTime;
}


//删除定时器
void DelTime(TimeValue* timeNode){
	TimeList* p = HeadNode;
	while(p != NULL){
		if(p->Data == timeNode){
			break;
		}
		p = p->next;
	}
	//二次确认
	if(p->Data != timeNode){
		return;
	}
	//开始删除
	if(p == HeadNode){
		//头部删除
		HeadNode = p->next;
		p->next->prev = NULL;
	}else if(p == FootNode){
		//尾部删除
		FootNode = p->prev;
		p->prev->next = NULL;
	}else{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	free(p->Data);
	free(p);
}

//心跳
void HeartTimer(void){
	Tick++;
	if(Tick==0){
		TickCycle++;
	}
}

//保活
void ActivityTimer(void){
	TimeList* p = HeadNode;
	uchar is_run = OFF;
	while(p != NULL){
		//是否使能
		if(p->Data->IsCmd == OFF){
			p = p->next;
			continue;
		}
		//是否同一个计时周期
		if(p->Data->TimeOutCycle != TickCycle){
			p = p->next;
			continue;
		}
		if(p->Data->Forever == ON){//直接执行
			is_run = ON;
		}else{
			if(p->Data->RunNum > 0){is_run = ON;}
		}
		if(Tick >= p->Data->TimeOut && is_run == ON){
			//重置超时时间
			p->Data->TimeOut = Tick + p->Data->TimingTime;
			if(p->Data->TimeOut < Tick){p->Data->TimeOutCycle++;}  //计算周期
			if(p->Data->RunNum > 0){p->Data->RunNum--;}
			p->Data->TimerCallBack(p->Data->Data);
		}else{
			TimerIdle();
		}
		p = p->next;
	}
}

//暂停定时器
void PauseTime(TimeValue* timeNode){
	timeNode->IsCmd = OFF;
}
//重启定时器
void RestartTime(TimeValue* timeNode){
	timeNode->IsCmd = ON;
}

//重启带次数的定时器(定时器停止后才能设置)
void RestartTimeNum(TimeValue* timeNode,uint RunNum){
	if(timeNode->RunNum == 0 && timeNode->Forever == OFF){
		timeNode->RunNum = RunNum;
	}
}


//一个节拍周期内的空闲函数
__weak void TimerIdle(void){}

//初始化定时器
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



