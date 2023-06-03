#include "time.h"


/**
 * 本示例是基于1ms节拍
 *  详细函数说明请看对应文档
*/



Timer* timer;
TimeValue* t1000;
TimeValue* t500;
TimeValue* t2000;


//1000ms的回调
void LedBlink1000(any data){
	printf("1S \r\n");
}

//500ms的回调
void LedBlink500(any data){
	printf("500ms \r\n");
}

//2000ms的回调
void LedBlink2000(any data){
	printf("2S \r\n");
}

//单个周期内的空闲函数
void TimerIdle(void){
//	printf("Idle \r\n");
}



//单片机的1ms中断函数
// 给定时器提供最小节拍（最小心跳）
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  HeartTimer();
}



int main(void){
  timer = TimerInit();    //初始化定时器对象
	t1000 = timer->Add(1000,0,(any)0,LedBlink1000);   //添加一个1000ms 无限循环的定时器
	t500 = timer->Add(500,10,(any)0,LedBlink500);   //添加一个500ms 执行10次的定时器
	t2000 = timer->Add(2000,0,(any)0,LedBlink2000);  //添加一个2000ms 无限循环的定时器

	while(1){
		//定时器保活
    ActivityTimer();
	}
}

