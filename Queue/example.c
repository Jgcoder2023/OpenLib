#include "queue.h"



Queue* queue;   //����һ���洢���е�ָ�����


void main(void){
	//����һ������Ϊ10�Ķ���
	queue = NewQueue(10);

	//Ҫ���͵���Ϣ
	uint8_t pmsg[] = "123"; 
	uint8_t pmsg2[] = "456";

	//������ͨ��Ϣ������
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);

	SendFirstMsg(queue,(any)pmsg2);     //�������ȼ���Ϣ������

	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);
	SendMsg(queue,(any)pmsg);


	while (1){
		any msg;  //���������Ϣ�ı���
		err errs = ReceiveMsg(queue,&msg); //������Ϣ
		if(errs != none){
			//û�л�ȡ����Ϣ
			printf("no data \r\n");
		}else{
			//�ɹ���ȡ��Ϣ     ����Ĭ�ϵ�Ƭ��֧��printf������
			printf("msg=%s \r\n",(uint8_t *)msg);
		}
	}
	
}