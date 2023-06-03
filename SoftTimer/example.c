#include "time.h"


/**
 * ��ʾ���ǻ���1ms����
 *  ��ϸ����˵���뿴��Ӧ�ĵ�
*/



Timer* timer;
TimeValue* t1000;
TimeValue* t500;
TimeValue* t2000;


//1000ms�Ļص�
void LedBlink1000(any data){
	printf("1S \r\n");
}

//500ms�Ļص�
void LedBlink500(any data){
	printf("500ms \r\n");
}

//2000ms�Ļص�
void LedBlink2000(any data){
	printf("2S \r\n");
}

//���������ڵĿ��к���
void TimerIdle(void){
//	printf("Idle \r\n");
}



//��Ƭ����1ms�жϺ���
// ����ʱ���ṩ��С���ģ���С������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  HeartTimer();
}



int main(void){
  timer = TimerInit();    //��ʼ����ʱ������
	t1000 = timer->Add(1000,0,(any)0,LedBlink1000);   //���һ��1000ms ����ѭ���Ķ�ʱ��
	t500 = timer->Add(500,10,(any)0,LedBlink500);   //���һ��500ms ִ��10�εĶ�ʱ��
	t2000 = timer->Add(2000,0,(any)0,LedBlink2000);  //���һ��2000ms ����ѭ���Ķ�ʱ��

	while(1){
		//��ʱ������
    ActivityTimer();
	}
}

