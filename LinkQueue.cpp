#include<stdio.h>
#include<stdlib.h>

typedef int QElemType;  //*ElemType���͸���ʵ������������������Ϊint *
typedef int Status;
#define OK 1
#define ERROR 0
#define OVER -1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

//���е���ʽ�洢�ṹ
typedef struct QNode {
	QElemType data;   //������
	struct QNode *next;  //�ṹ��
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;  //��ͷָ��
	QueuePtr rear;   //��βָ��
}LinkQueue;

//��ʼ��һ���յĶ���
Status InitQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) {
		printf("initialization failed!!");
		exit(OVER);  //�洢����ʧ��
	}
	Q->front->next = NULL;
	return OK;
}

//���ٶ���
Status DestroyQueue(LinkQueue *Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);    //�Ӷ�ͷȡ��ÿһ��Ԫ�ز��ͷ��ڴ棬Q->rear��Ϊһ����ʱָ��ʹ��
		Q->front = Q->rear;
	}
	return OK;
}

//��ն���
Status ClearQueue(LinkQueue *Q) {
	Q->front = Q->rear;
	return OK;
}

//�����п�
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear) {
		return OK;
	}
	return ERROR;
}

//���еĳ���
int LengthQueue(LinkQueue Q) {
	QNode *p = Q.front->next;  //front��ָ��ͷ���ģ�ͷ��㲻�洢���ݣ�front��next�Ƕ�ͷ���
	int len = 0;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

//��ö�ͷԪ��
Status GetheadQueue(LinkQueue Q, QElemType *e) {
	if (Q.front == Q.rear) {
		return ERROR;
	}
	QNode *p = Q.front->next;  //front��ָ��ͷ���ģ�ͷ��㲻�洢���ݣ�front��next�Ƕ�ͷ���
	*e = p->data;              //���ߴ���Ĳ���Ϊ&e����ʽ�������ֻ��Ҫe=p->data������
	return OK;
}

//��β����Ԫ��
Status EnterQueue(LinkQueue *Q, QElemType e) {
	QNode *p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) {
		return ERROR;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;  //��ǰ��βָ���nextָ����Ԫ��
	Q->rear = p;        //�޸�βָ��
	return OK;
}

//ɾ����ͷԪ�أ������ظ�Ԫ��
Status DeleteQueue(LinkQueue *Q, QElemType &e) {
	if (Q->front == Q->rear) {
		return ERROR;
	}
	QNode *p = Q->front->next;  //front��ָ��ͷ���ģ�ͷ��㲻�洢���ݣ�front��next�Ƕ�ͷ��㣬��p��Ϊ��ͷ���
	e = p->data;                //��ȡ��ͷ����
	Q->front->next = p->next;   //Q->front->next��ָͷ����nextָ��ȥ����p����һ����㣬���ǰ�ͷ���p�����ȥ��
	if (Q->rear == p) {         //����ö���ǡ��ֻ��һ��Ԫ�أ�ɾ��֮����о�Ϊ���ˣ�����front=near
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

//��������
void ShowQueue(LinkQueue Q) {
	if (Q.front == Q.rear) {
		printf("�ö���Ϊ�գ���������ʾ����\n");
		return;
	}
	QNode *p = Q.front->next;   //front��ָ��ͷ���ģ�ͷ��㲻�洢���ݣ�front��next�Ƕ�ͷ��㣬��p��Ϊ��ͷ���
	printf("����������£�\n");
	while (p) {
		QElemType e = p->data;
		printf("%d ", e);
		p = p->next;
	}
	printf("\n");
}

int main() {
	LinkQueue Q;
	int k = 1;
	int m = 1;
	printf("\n*******************************************************************************\n");
	printf("***************************�� �� �� �� ֮ �� �� ��*****************************\n");
	printf("***************************�� �ߣ�Ѧ �ƣ�3219005084)***************************\n");
	printf("*                            1.�����п�                                       *\n");
	printf("*                            2.���г���                                       *\n");
	printf("*                            3.�������                                       *\n");
	printf("*                            4.��������                                       *\n");
	printf("*                            5.��ö�ͷԪ��                                   *\n");
	printf("*                            6.ɾ����ͷԪ��                                   *\n");
	printf("*                            7.��β����Ԫ��                                   *\n");
	printf("*                            8.��������                                       *\n");
	printf("*                            0.�˳�                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	InitQueue(&Q);
	printf("�������ѳ�ʼ����\n");
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
			if (EmptyQueue(&Q)) {
				printf("����Ϊ�գ�\n");
			}
			else {
				printf("���в�Ϊ�գ�\n");
			}
			break;
		}
		case 2: {
			int n;
			n = LengthQueue(Q);
			printf("�ö��еĳ���Ϊ%d\n", n);
			break;
		}
		case 3: {
			ClearQueue(&Q);
			printf("��������գ�\n");
			break;
		}
		case 4: {
			DestroyQueue(&Q);
			printf("�����ѱ����٣�\n");
			printf("�Ƿ����³�ʼ��һ�����У����롰1�������³�ʼ��һ�����У����롰0����ѡ�񲻳�ʼ�����У����˳����򣡣�\n");
			while (m) {
				float choose2;
				int n;
				printf("����������ѡ��");
				n = scanf("%f", &choose2);
				while (n == 0) {
					while (getchar() != '\n');
					printf("�ף�������Ĳ�������Ŷ����");
					printf("��������������ѡ��");
					n = scanf("%f", &choose2);
				}
				int Rchoose2;
				Rchoose2 = (int)choose2;
				switch (Rchoose2)
				{
				case 0: {
					printf("�����˳�����\n");
					exit(OVER);
					break;
				}
				case 1: {
					InitQueue(&Q);
					printf("�����³�ʼ��һ���µĶ��У�\n");
					m = 0;
					break;
				}
				default: {
					printf("����0��1֮��ѡ��\n");
					break;
				}
				}
			}
			break;
		}
		case 5: {
			QElemType e1;
			if (GetheadQueue(Q, &e1)) {
				printf("��ͷԪ��Ϊ��%d\n", e1);
			}
			else{
				printf("�ö���Ϊ�գ��޶�ͷԪ�أ�\n");
			}
			break;
		}
		case 6: {
			QElemType e2;
			if (DeleteQueue(&Q, e2)) {
				printf("��ͷԪ���ѱ�ɾ������Ԫ��Ϊ��%d\n", e2);
			}
			else {
				printf("����Ϊ��,�����ݿ�ɾ����\n");
			}
			break;
		}
		case 7: {
			QElemType e;
			printf("��������Ҫ������е����ݣ�");
			scanf("%d", &e);
			if (EnterQueue(&Q, e)) {
				printf("�ɹ������ݲ�����У�\n");
			}
			else {
				printf("�����ڴ�ռ�ʧ�ܣ��޷��������ݣ�\n");
			}
			break;
		}
		case 8: {
			ShowQueue(Q);
			break;
		}
		case 0: {
			printf("�����˳�����\n");
			k = 0;
			break;
		}
		default: {
			printf("����0-8֮��ѡ��\n");
			break;
		}
		}
	}
	system("pause");
	return 0;
}