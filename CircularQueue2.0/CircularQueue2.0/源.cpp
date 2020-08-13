#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef int QElemType;  //*ElemType类型根据实际情况而定，这里假设为int *
typedef int Status;
#define OK 1
#define ERROR 0

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

/*
这里定义的是静态的数组，由系统自动回收，无法手动操作，所以没有“销毁队列”这个选项
*/

/*循环队列的顺序存储结构*/
typedef struct {
	QElemType data[MAXSIZE];
	int front;    //头指针
	int rear;     //尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;

//初始化一个空队列
Status InitQueue(SqQueue *Q) {
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//队列判空
Status EmptyQueue(SqQueue Q) {
	if (Q.front == Q.rear) {
		return OK;
	}
	return ERROR;
}

//求队列的长度
int QueueLength(SqQueue Q) {
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

//若队列未满，则插入元素e为Q新的队尾元素
Status EnterQueue(SqQueue *Q, int e) {
	if ((Q->rear + 1) % MAXSIZE == Q->front) {  //队列满的判断
		return ERROR;
	}
	Q->data[Q->rear] = e;       //将元素e赋值给队尾
	Q->rear = (Q->rear + 1) % MAXSIZE;     //rear指针向后移一个位置，若到最后则转至数组头
	return OK;
}

//若队列不空，则删除Q中队头元素，用e返回其值
Status DeleteQueue(SqQueue *Q, QElemType *e) {
	if (Q->front == Q->rear) {  //队列为空
		return ERROR;
	}
	*e = Q->data[Q->front];   //将队头元素赋值给e
	Q->front = (Q->front + 1) % MAXSIZE;    //front指针向后移一个位置，若到最后则转到数组头部
	return OK;
}

//显示队列中的元素
void ShowQueue(SqQueue Q) {
	if (Q.front == Q.rear) {
		printf("队列为空！无数据显示！\n");
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

//清空队列
Status ClearQueue(SqQueue *Q) {
	Q->front = Q->rear = 0;
	return OK;
}

int main() {
	SqQueue *Q;
	Q = (SqQueue*)malloc(sizeof(SqQueue));
	int k = 1;
	printf("\n*******************************************************************************\n");
	printf("**************************数 据 结 构 之 循 环 队 列***************************\n");
	printf("***************************作 者：薛 云（3219005084)***************************\n");
	printf("*                            1.队列判空                                       *\n");
	printf("*                            2.队列长度                                       *\n");
	printf("*                            3.队列清空                                       *\n");
	printf("*                            4.删除队头元素                                   *\n");
	printf("*                            5.队尾插入元素                                   *\n");
	printf("*                            6.遍历队列                                       *\n");
	printf("*                            0.退出                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	InitQueue(Q);
	while (k) {
		float choose;
		int n;
		printf("请根据需要输入数字代号：");
		n = scanf("%f", &choose);
		while (n == 0) {
			while (getchar() != '\n');
			printf("亲，您输入的不是数字哦！！");
			printf("请重新选择：");
			n = scanf("%f", &choose);
		}
		int Rchoose;
		Rchoose = (int)choose;
		switch (Rchoose)
		{
		case 1: {
			if (EmptyQueue(*Q)) {
				printf("队列为空！\n");
			}
			else {
				printf("队列不为空！\n");
			}
			break;
		}
		case 2: {
			int n;
			n = QueueLength(*Q);
			printf("该队列的长度为%d\n", n);
			break;
		}
		case 3: {
			ClearQueue(Q);
			printf("队列已清空！\n");
			break;
		}
		case 4: {
			QElemType e;
			if (DeleteQueue(Q, &e)) {//将e的地址传给函数Delete，该函数再通过指针的形式直接修改e的值
				printf("队头元素已被删除，该元素为%d\n", e);
			}
			else {
				printf("队列为空,无数据可删除！\n");
			}
			break;
		}
		case 5: {
			int e;
			printf("请输入想要插入队列的数据：");
			scanf("%d", &e);
			if (EnterQueue(Q, e)) {
				printf("成功将数据插入队列！\n");
			}
			else {
				printf("队列已满！不能再插入数据！可选择删除数据后再插入\n");
			}
			break;
		}
		case 6: {
			printf("该队列数据如下：\n");
			ShowQueue(*Q);
			printf("\n");
			break;
		}
		case 0: {
			printf("程序退出！！\n");
			k = 0;
			break;
		}
		default: {
			printf("请在0-6之间选择！\n");
			break;
		}
		}

	}
	system("pause");
	return 0;
}