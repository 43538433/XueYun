#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
int k = 1;
int count;

typedef struct Node {      //建立节点
	int data;              //数据域
	struct Node *next;     //指针域
}LinkStack;

/*建立空栈*/
int InitStack(LinkStack *&S)//*&为引用，可以直接修改实参指向的位置
{                           //链栈不带头结点，初始化链栈只需要把栈顶置为空
	S = (LinkStack *)malloc(sizeof(LinkStack));
	S->next = NULL;//栈为空的标志
	return 1;
}

/*判空操作*/
int Empty(LinkStack *S)
{
	if (S->next == NULL) {
		return 1;
	}
	else
		return 0;
}

/*将链栈置为空*/
int ResetStack(LinkStack *&S) {
	if (S->next == NULL) {
		return 1;
	}
	LinkStack *p, *q;
	p = S;
	q = NULL;
	while (p) {
		q = p;
		p = p->next;
		free(q);
		count--;
	}
	count++;
	p = NULL;
	S->next = NULL;
	return 0;
}

/*返回当前栈的长度*/
int StackLen() {
	return count;
}

/*销毁栈
void DestroyStack(LinkStack *&S)
{
	LinkStack *p;
	p = NULL;
	while (S != NULL)
	{
		p = S;
		S = S->next;
		count--;
		free(p);
	}
	S->next = NULL;
}*/

/*入栈*/
void Push(LinkStack* &S, int x)//S为头结点
{
	LinkStack *p;
	p = (LinkStack *)malloc(sizeof(LinkStack));//创造一个工作节点
	p->data = x;//存入要入栈的信息
	p->next = S->next;
	S->next = p;
	count++;
	printf("该数据已压入栈！\n");
}

/*出栈*/
int Pop(LinkStack *&S, int &ptr)//通过*ptr返回出栈的值,S为头结点
{
	LinkStack *p = S->next;
	if (S->next == NULL)
	{
		return 0;
	}
	else
	{
		ptr = p->data;//返回栈顶的值
		S->next = p->next;//栈顶位置变化
		free(p);//释放栈顶空间
		count--;
		return ptr;
	}
}

/*取栈顶元素*/
int GetTop(LinkStack *S, int &ptr)//与出栈差距在于不改变栈
{
	if (S->next == NULL)
	{
		return 0;
	}
	ptr = S->next->data;
	return ptr;
}

void menu(LinkStack *S) {
	//LinkStack *top;
	float choose;
	int n;
	int data;
	int get;
	//int len;
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
		if (Empty(S)) {
			printf("该链栈为空！！\n");
		}
		else {
			printf("该链栈不为空！！\n");
		}
		break;
	case 2:
		get = GetTop(S, data);
		if (!get) {
			printf("该栈为空！！\n");
		}
		else {
			printf("该栈的栈顶元素为:%d\n", data);
		}
		break;
	case 3:
		if (ResetStack(S)) {
			printf("该链栈为空！！\n");
		}
		else {
			printf("已清空链栈！！\n");
		}
		break;
	/*case 4:
		DestroyStack(S);
		printf("链栈已被销毁！\n");
		break;*/
	case 4:
		get= StackLen();
		if (get) {
			printf("该链栈当前的长度为：%d\n", get);
		}
		else {
			printf("该栈为空！\n");
		}
		break;
	case 5:
		float set;
		int Rset;
		printf("请输入一个数据：");
		get=scanf("%f", &set);
		while (get == 0) {
			while (getchar() != '\n');
			printf("亲，您输入的不是数字哦！！");
			printf("请重新选择：");
			n = scanf("%f", &set);
		}
		Rset = (int)set;
		Push(S, Rset);
		break;
	case 6:
		if (Pop(S, data)) {
			printf("已将栈顶的数据移出栈,该数据为：");
			printf("%d\n", data);
		}
		else {
			printf("操作失败！！\n");
		}
		break;
	case 0:
		printf("程序已退出！\n");
		k = 0;
		break;
	default:
		printf("请在0-6之间选择！\n");
	}
}

int main()
{
	//int x;//用来读取出栈数据
	//int y;
	LinkStack *top;//定义栈顶指针并初始化
	if (InitStack(top)) {
		printf("空链栈建立完成！\n");
	}
	else {
		printf("空链栈构建失败！\n");
	}
	float len;
	int n;
	printf("请输入栈的大小：");
	n = scanf("%f", &len);
	while (n == 0) {
		while (getchar() != '\n');
		printf("亲，您输入的不是数字哦！！");
		printf("请重新输入栈的长度：");
		n = scanf("%f", &len);
	}
	float num;
	for (int i = 1; i <=(int)len; i++) {
		printf("请输入第%d个数据：", i);
		n = scanf("%f", &num);
		while (n == 0) {
			while (getchar() != '\n');
			printf("亲，您输入的不是数字哦！！");
			printf("请重新输入第%d个数据：", i);
			n = scanf("%f", &num);
		}
		Push(top, (int)num);
		if (i == len) {
			printf("已将全部数据压入栈\n");
		}
	}
	printf("\n*******************************************************************************\n");
	printf("**********************数 据 结 构 之 链 栈 程 序 设 计*************************\n");
	printf("**********************作 者：薛 云（3219005084）*******************************\n");
	printf("*                            1.判断链栈是否为空                               *\n");
	printf("*                            2.得到栈顶元素                                   *\n");
	printf("*                            3.清空栈                                         *\n");
	printf("*                            4.测量栈长度                                     *\n");
	printf("*                            5.入栈                                           *\n");
	printf("*                            6.出栈                                           *\n");
	printf("*                            0.退出                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	while (k) {
		menu(top);
	}
	system("pause");
	return 0;
}