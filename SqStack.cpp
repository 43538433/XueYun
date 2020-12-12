#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#define ERROR 0;
#define OK 1;
int k = 1;	//全局变量k，k=0时结束程序
int d = 1;	//全局变量d，d=0时表示栈已被销毁，需重新初始化一个顺序栈

typedef int ElemType;
typedef int Status;

typedef struct SqStack {
	ElemType *elem;	//存储空间的基址
	int top;		//栈顶元素的下一个位置，简称栈顶位标
	int size;		//当前分配的存储容量
	int increment;	//扩容时，增加的存储容量
}SqStack;

/*
初始化空顺序栈S
*/
Status InitStack_Sq(SqStack &S, int size, int inc) {
	S.elem = (ElemType*)malloc(size*sizeof(ElemType));	//分配存储空间
	if (NULL == S.elem) {
		printf("初始化顺序栈失败！\n");
		return ERROR;
	}
	S.top = 0;			//置S为空栈
	S.size = size;		//初始化容量值
	S.increment = inc;	//初始化增量值
	d = 1;				//表示栈已被初始化
	return OK;
}

/*
销毁顺序栈S
*/
Status DestroyStack_Sq(SqStack &S) {
	free(S.elem);
	return OK;
}

/*
顺序栈判空
*/
Status StackEmpty_Sq(SqStack S) {
	if (S.top == 0) {
		return OK;
	}
	return ERROR;
}

/*
清空栈S
*/
Status ClearStack_Sq(SqStack &S) {
	S.top = 0;
	return OK;
}

/*
入栈
*/
Status Push_Sq(SqStack &S, ElemType e) {
	ElemType *newbase;
	if (S.top >= S.size) {
		newbase = (ElemType*)realloc(S.elem, (S.size + S.increment) * sizeof(ElemType));
		if (NULL == newbase) {
			return ERROR;
		}
		S.elem = newbase;
		S.size += S.increment;
	}
	S.elem[S.top] = e;
	S.top++;
	return OK;
}

/*
栈顶元素出栈
*/
Status Pop_Sq(SqStack &S, ElemType &e) {
	e = S.elem[S.top - 1];
	S.top--;
	return OK;
}

/*
获取栈顶元素
*/
Status GetTop_Sq(SqStack S, ElemType &e) {
	e = S.elem[S.top - 1];
	return OK;
}

/*
测量栈的长度
*/
int Length_Sq(SqStack S) {
	int len;
	len = S.top;
	return len;
}

/*
遍历栈中元素
*/
void Visit_Sq(SqStack S) {
	printf("[ ");
	while (S.top != 0) {
		S.top--;
		if (S.top == 0) {
			printf("%d", S.elem[S.top]);
		}
		else {
			printf("%d，", S.elem[S.top]);
		}
	}
	printf(" ]\n");
}

/*
主页面
*/
void menu(SqStack &S) {
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
	case 1:
		if (d == 1) {
			printf("顺序栈已存在，无需初始化！\n");
		}
		else {
			int size, inc;
			printf("请确定顺序栈的容量大小：");
			scanf("%d", &size);
			printf("请确定顺序栈扩容量的大小：");
			scanf("%d", &inc);
			InitStack_Sq(S, size, inc);
			printf("顺序栈初始化成功！顺序栈的容量大小为%d，扩容量大小为%d\n", size, inc);
		}
		break;
	case 2:
		if (d==0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			if (StackEmpty_Sq(S)) {
				printf("栈为空！\n");
			}
			else {
				printf("栈不为空！\n");
			}
		}
		break;
	case 3:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			ClearStack_Sq(S);
			printf("栈已清空！\n");
		}
		break;
	case 4:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			int len;
			len = Length_Sq(S);
			printf("顺序栈的长度为:%d\n",len);
		}
		break;
	case 5:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			if (S.top == 0) {	//栈为空
				printf("栈为空，无栈顶元素！\n");
			}
			else {
				ElemType e;
				GetTop_Sq(S, e);
				printf("栈顶元素为：%d\n", e);
			}
		}
		break;
	case 6:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			ElemType e;
			printf("请输入一个数据：");
			scanf("%d", &e);
			Push_Sq(S, e);
			printf("数据入栈成功！\n");
		}
		break;
	case 7:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			if (S.top == 0) {
				printf("栈为空，无栈顶元素！\n");
			}
			else {
				ElemType e;
				Pop_Sq(S, e);
				printf("元素出栈成功，该元素为%d\n", e);
			}
		}
		break;
	case 8:
		if (d == 0) {
			printf("栈已被销毁，请先初始化一个顺序栈！\n");
		}
		else {
			if (S.top == 0) {
				printf("栈为空！\n");
			}
			else {
				printf("遍历栈中元素如下：\n");
				Visit_Sq(S);
			}
		}
		break;
	case 9:
		if (d == 0) {
			printf("栈已被销毁！\n");
		}
		else {
			DestroyStack_Sq(S);
			d = 0;
			printf("栈已被销毁！\n");
		}
		break;
	case 0:
		printf("程序已退出！\n");
		k = 0;
		break;
	default:
		printf("请在0-9之间选择！\n");
	}
}

int main() {
	SqStack S;
	InitStack_Sq(S,5,5);
	printf("\n*******************************************************************************\n");
	printf("**********************数 据 结 构 之 顺 序 栈 程 序 设 计**********************\n");
	printf("**********************作 者：薛 云（3219005084）*******************************\n");
	printf("*                            1.初始化顺序栈                                   *\n");
	printf("*                            2.顺序栈判空                                     *\n");
	printf("*                            3.清空栈                                         *\n");
	printf("*                            4.测量栈长度                                     *\n");
	printf("*                            5.获取栈顶元素                                   *\n");
	printf("*                            6.入栈                                           *\n");
	printf("*                            7.出栈                                           *\n");
	printf("*                            8.遍历栈                                         *\n");
	printf("*                            9.销毁栈                                         *\n");
	printf("*                            0.退出                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	printf("\n-------------------默认顺序栈已初始化完毕，容量为5，扩容量为5------------------\n\n");
	while (k) {
		menu(S);
	}
	return 0;
}