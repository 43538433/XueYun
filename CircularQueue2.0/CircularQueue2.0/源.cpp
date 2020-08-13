#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef int QElemType;  //*ElemType���͸���ʵ������������������Ϊint *
typedef int Status;
#define OK 1
#define ERROR 0

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

/*
���ﶨ����Ǿ�̬�����飬��ϵͳ�Զ����գ��޷��ֶ�����������û�С����ٶ��С����ѡ��
*/

/*ѭ�����е�˳��洢�ṹ*/
typedef struct {
	QElemType data[MAXSIZE];
	int front;    //ͷָ��
	int rear;     //βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��
}SqQueue;

//��ʼ��һ���ն���
Status InitQueue(SqQueue *Q) {
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//�����п�
Status EmptyQueue(SqQueue Q) {
	if (Q.front == Q.rear) {
		return OK;
	}
	return ERROR;
}

//����еĳ���
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//������δ���������Ԫ��eΪQ�µĶ�βԪ��
Status EnterQueue(SqQueue *Q, int e) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {  //���������ж�
		return ERROR;
	}
	Q->data[Q->rear] = e;       //��Ԫ��e��ֵ����β
	Q->rear = (Q->rear + 1) % MAXSIZE;     //rearָ�������һ��λ�ã����������ת������ͷ
	return OK;
}

//�����в��գ���ɾ��Q�ж�ͷԪ�أ���e������ֵ
Status DeleteQueue(SqQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {  //����Ϊ��
		return ERROR;
	}
	*e = Q->data[Q->front];   //����ͷԪ�ظ�ֵ��e
	Q->front = (Q->front + 1) % MAXSIZE;    //frontָ�������һ��λ�ã����������ת������ͷ��
	return OK;
}

//��ʾ�����е�Ԫ��
void ShowQueue(SqQueue Q) {
	if (Q.front == Q.rear) {
		printf("����Ϊ�գ���������ʾ��\n");
		return;
	}
	while (1) {
		printf("%d ", Q.data[Q.front]);
		Q.front = (Q.front + 1) % MAXSIZE;
		if (Q.front == Q.rear) {
			break;
		}
	}
}

//��ն���
Status ClearQueue(SqQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

int main() {
	SqQueue *Q;
	Q = (SqQueue*)malloc(sizeof(SqQueue));
	int k = 1;
	printf("\n*******************************************************************************\n");
	printf("**************************�� �� �� �� ֮ ѭ �� �� ��***************************\n");
	printf("***************************�� �ߣ�Ѧ �ƣ�3219005084)***************************\n");
	printf("*                            1.�����п�                                       *\n");
	printf("*                            2.���г���                                       *\n");
	printf("*                            3.�������                                       *\n");
	printf("*                            4.ɾ����ͷԪ��                                   *\n");
	printf("*                            5.��β����Ԫ��                                   *\n");
	printf("*                            6.��������                                       *\n");
	printf("*                            0.�˳�                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	InitQueue(Q);
	while (k) {
		float choose;
		int n;
		printf("�������Ҫ�������ִ��ţ�");
		n = scanf("%f", &choose);
		while (n == 0) {
			while (getchar() != '\n');
			printf("�ף�������Ĳ�������Ŷ����");
			printf("������ѡ��");
			n = scanf("%f", &choose);
		}
		int Rchoose;
		Rchoose = (int)choose;
		switch (Rchoose)
		{
		case 1: {
			if (EmptyQueue(*Q)) {
				printf("����Ϊ�գ�\n");
			}
			else {
				printf("���в�Ϊ�գ�\n");
			}
			break;
		}
		case 2: {
			int n;
			n = QueueLength(*Q);
			printf("�ö��еĳ���Ϊ%d\n", n);
			break;
		}
		case 3: {
			ClearQueue(Q);
			printf("��������գ�\n");
			break;
		}
		case 4: {
			QElemType e;
			if (DeleteQueue(Q, &e)) {//��e�ĵ�ַ��������Delete���ú�����ͨ��ָ�����ʽֱ���޸�e��ֵ
				printf("��ͷԪ���ѱ�ɾ������Ԫ��Ϊ%d\n", e);
			}
			else {
				printf("����Ϊ��,�����ݿ�ɾ����\n");
			}
			break;
		}
		case 5: {
			int e;
			printf("��������Ҫ������е����ݣ�");
			scanf("%d", &e);
			if (EnterQueue(Q, e)) {
				printf("�ɹ������ݲ�����У�\n");
			}
			else {
				printf("���������������ٲ������ݣ���ѡ��ɾ�����ݺ��ٲ���\n");
			}
			break;
		}
		case 6: {
			printf("�ö����������£�\n");
			ShowQueue(*Q);
			printf("\n");
			break;
		}
		case 0: {
			printf("�����˳�����\n");
			k = 0;
			break;
		}
		default: {
			printf("����0-6֮��ѡ��\n");
			break;
		}
		}

	}
	system("pause");
	return 0;
}