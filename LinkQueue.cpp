#include<stdio.h>
#include<stdlib.h>

typedef int QElemType;  //*ElemType类型根据实际情况而定，这里假设为int *
typedef int Status;
#define OK 1
#define ERROR 0
#define OVER -1

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

//队列的链式存储结构
typedef struct QNode {
	QElemType data;   //数据域
	struct QNode *next;  //结构域
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;  //队头指针
	QueuePtr rear;   //队尾指针
}LinkQueue;

//初始化一个空的队列
Status InitQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) {
		printf("initialization failed!!");
		exit(OVER);  //存储分配失败
	}
	Q->front->next = NULL;
	return OK;
}

//销毁队列
Status DestroyQueue(LinkQueue *Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);    //从队头取出每一个元素并释放内存，Q->rear作为一个临时指针使用
		Q->front = Q->rear;
	}
	return OK;
}

//清空队列
Status ClearQueue(LinkQueue *Q) {
	Q->front = Q->rear;
	return OK;
}

//队列判空
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear) {
		return OK;
	}
	return ERROR;
}

//队列的长度
int LengthQueue(LinkQueue Q) {
	QNode *p = Q.front->next;  //front是指向头结点的，头结点不存储数据，front的next是队头结点
	int len = 0;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

//获得队头元素
Status GetheadQueue(LinkQueue Q, QElemType *e) {
	if (Q.front == Q.rear) {
		return ERROR;
	}
	QNode *p = Q.front->next;  //front是指向头结点的，头结点不存储数据，front的next是队头结点
	*e = p->data;              //或者传入的参数为&e的形式，这里就只需要e=p->data就行了
	return OK;
}

//队尾插入元素
Status EnterQueue(LinkQueue *Q, QElemType e) {
	QNode *p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) {
		return ERROR;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;  //当前队尾指针的next指向新元素
	Q->rear = p;        //修改尾指针
	return OK;
}

//删除队头元素，并返回该元素
Status DeleteQueue(LinkQueue *Q, QElemType &e) {
	if (Q->front == Q->rear) {
		return ERROR;
	}
	QNode *p = Q->front->next;  //front是指向头结点的，头结点不存储数据，front的next是队头结点，即p成为队头结点
	e = p->data;                //获取队头数据
	Q->front->next = p->next;   //Q->front->next是指头结点的next指针去连接p的下一个结点，就是把头结点p隔离出去了
	if (Q->rear == p) {         //如果该队列恰巧只有一个元素，删除之后队列就为空了，所以front=near
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

//遍历队列
void ShowQueue(LinkQueue Q) {
	if (Q.front == Q.rear) {
		printf("该队列为空，无数据显示！！\n");
		return;
	}
	QNode *p = Q.front->next;   //front是指向头结点的，头结点不存储数据，front的next是队头结点，即p成为队头结点
	printf("队列输出如下：\n");
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
	printf("***************************数 据 结 构 之 链 队 列*****************************\n");
	printf("***************************作 者：薛 云（3219005084)***************************\n");
	printf("*                            1.队列判空                                       *\n");
	printf("*                            2.队列长度                                       *\n");
	printf("*                            3.队列清空                                       *\n");
	printf("*                            4.队列销毁                                       *\n");
	printf("*                            5.获得队头元素                                   *\n");
	printf("*                            6.删除队头元素                                   *\n");
	printf("*                            7.队尾插入元素                                   *\n");
	printf("*                            8.遍历队列                                       *\n");
	printf("*                            0.退出                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	InitQueue(&Q);
	printf("链队列已初始化！\n");
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
			if (EmptyQueue(&Q)) {
				printf("队列为空！\n");
			}
			else {
				printf("队列不为空！\n");
			}
			break;
		}
		case 2: {
			int n;
			n = LengthQueue(Q);
			printf("该队列的长度为%d\n", n);
			break;
		}
		case 3: {
			ClearQueue(&Q);
			printf("队列已清空！\n");
			break;
		}
		case 4: {
			DestroyQueue(&Q);
			printf("队列已被销毁！\n");
			printf("是否重新初始化一个队列，输入“1”将重新初始化一个队列，输入“0”即选择不初始化队列，则将退出程序！！\n");
			while (m) {
				float choose2;
				int n;
				printf("请输入您的选择：");
				n = scanf("%f", &choose2);
				while (n == 0) {
					while (getchar() != '\n');
					printf("亲，您输入的不是数字哦！！");
					printf("请重新输入您的选择：");
					n = scanf("%f", &choose2);
				}
				int Rchoose2;
				Rchoose2 = (int)choose2;
				switch (Rchoose2)
				{
				case 0: {
					printf("即将退出程序！\n");
					exit(OVER);
					break;
				}
				case 1: {
					InitQueue(&Q);
					printf("已重新初始化一个新的队列！\n");
					m = 0;
					break;
				}
				default: {
					printf("请在0和1之间选择！\n");
					break;
				}
				}
			}
			break;
		}
		case 5: {
			QElemType e1;
			if (GetheadQueue(Q, &e1)) {
				printf("队头元素为：%d\n", e1);
			}
			else{
				printf("该队列为空，无队头元素！\n");
			}
			break;
		}
		case 6: {
			QElemType e2;
			if (DeleteQueue(&Q, e2)) {
				printf("队头元素已被删除，该元素为：%d\n", e2);
			}
			else {
				printf("队列为空,无数据可删除！\n");
			}
			break;
		}
		case 7: {
			QElemType e;
			printf("请输入想要插入队列的数据：");
			scanf("%d", &e);
			if (EnterQueue(&Q, e)) {
				printf("成功将数据插入队列！\n");
			}
			else {
				printf("申请内存空间失败，无法插入数据！\n");
			}
			break;
		}
		case 8: {
			ShowQueue(Q);
			break;
		}
		case 0: {
			printf("程序退出！！\n");
			k = 0;
			break;
		}
		default: {
			printf("请在0-8之间选择！\n");
			break;
		}
		}
	}
	system("pause");
	return 0;
}