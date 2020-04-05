//顺序栈
//参考于：https://www.cnblogs.com/mwq1024/p/10146943.html
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
#define STACK_INIT_SIZE 100     //储存空间初始分配量
#define STACKINCREMENT  10      //存储空间分配增量
#define OK 1
#define ERROR 0
int k = 1;
typedef int StackType; //栈元素类型

typedef struct {
	StackType *base;   //在构造之前和销毁之后，base的值为NULL
	StackType *top;    //栈顶指针
	int stacksize;     //当前已分配的存储空间，以元素为单位
}SqStack; //顺序栈

//栈的初始化
int InitStack(SqStack *p) {
	p->base = (StackType*)malloc(STACK_INIT_SIZE * sizeof(StackType));
	if (p->base == NULL)  return ERROR;  //内存分配失败
	p->top = p->base;                    //栈顶与栈底相同表示一个空栈
	p->stacksize = STACK_INIT_SIZE;
	return OK;

}

//判断栈是否为空
int EmptyStack(SqStack *p) {             //若为空栈 则返回OK，否则返回ERROR
	if (p->top == p->base) return OK;
	else return ERROR;
}

//顺序栈的压入
int Push(SqStack *p, StackType e) {           //插入元素e为新的栈顶元素
	if ((p->top - p->base) >= p->stacksize)   //栈满，追加储存空间
	{
		p->base = (StackType*)realloc(p->base, (p->stacksize + STACKINCREMENT) * sizeof(StackType));
		if (p->base == NULL)   return ERROR;  // 储存空间分配失败
		p->top = p->base + p->stacksize;      
		p->stacksize += STACKINCREMENT;
	}
	*(p->top) = e;
	(p->top)++;
	printf("数据入栈成功！\n");
	return OK;
}

// 顺序栈的弹出     
int Pop(SqStack *p, StackType *e) {           //若栈不空，则删除p的栈顶元素，用e返回其值
	if (p->top == p->base) return ERROR;
	--(p->top);
	*e = *(p->top);
	return OK;
}

//顺序栈的销毁
int DestroyStack(SqStack *p) {                
	free(p->base);                            //释放栈底空间并置空
	p->base = NULL;
	p->top = NULL;
	p->stacksize = 0;
	return OK;
}

//将顺序栈置空 栈还是存在的，栈中的元素也存在，如果有栈中元素的地址任然能调用
int ClearStack(SqStack *p) {
	p->top = p->base;
	return OK;
}

//返回顺序栈的元素个数
int StackLength(SqStack p) {
	//栈顶指针减去栈底指针等于长度，因为栈顶指针指向当前栈顶元素的下一个位置
	return p.top - p.base;
}

//返回顺序栈的栈顶元素
int GetTop(SqStack *p, StackType *e) {
	//若栈不为空，则用e返回p的栈顶元素
	if (p->top > p->base) {
		*e = *(p->top - 1); return OK;
	}
	else return ERROR;
}

//从栈底到栈顶依次对栈中的每个元素调用函数pfun(),遍历栈
int StackTraverse(SqStack p, void(*pfun)(StackType)/*函数指针*/) {
	
	while (p.top > p.base)
		pfun(*(p.base)++);                //先调用后递增
	printf("\n");
	return OK;
}

//打印栈中元素
void print(StackType stack) {
	printf("%d  ", stack);
}

//测试栈的各种操作
int main() {
	int n, i;
	//int get;
	StackType *e, a;
	SqStack *pstack, stack;
	pstack = &stack;
	e = (StackType*)malloc(sizeof(StackType));    //为指针e分配内存地址
	//InitStack(pstack);                            //初始化栈
	if (InitStack(pstack)) {
		printf("空栈构造完成！\n");
	}
	else {
		printf("空栈构建失败！\n");
	}
	float len;
	printf("请输入栈的大小：");
	n = scanf("%f", &len);
	while (n == 0) {
		while (getchar() != '\n');
		printf("亲，您输入的不是数字哦！！");
		printf("请重新输入栈的长度：");
		n = scanf("%f", &len);
	}
	for (i = 0; i < (int)len; i++)
	{
		printf("请输入第%d个入栈数据：",i+1);
		scanf("%d", &a);
		Push(pstack, a);
	}
	printf("\n");
	printf("\n*******************************************************************************\n");
	printf("*********************数 据 结 构 之 顺 序 栈 程 序 设 计***********************\n");
	printf("**********************作 者：薛 云（3219005084）*******************************\n");
	printf("*                            1.判断栈是否为空                               *\n");
	printf("*                            2.得到栈顶元素                                   *\n");
	printf("*                            3.清空栈                                         *\n");
	printf("*                            4.销毁栈                                         *\n");
	printf("*                            5.测量栈长度                                     *\n");
	printf("*                            6.遍历栈中元素                                   *\n");
	printf("*                            7.入栈                                           *\n");
	printf("*                            8.出栈                                           *\n");
	printf("*                            0.退出                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	while (k) {
		float choose;
		int n;
		int get;
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
			if (EmptyStack(pstack) == 0) {
				printf("栈不为空!\n");
			}
			else {
				printf("栈为空！\n");
			}
			break;
		case 2:
			get = GetTop(pstack, e);
			if (get) {
				printf("栈顶的元素为：%d\n", *e);
			}
			else {
				printf("操作失败！栈为空！\n");
			}
			break;
		case 3:
			if (ClearStack(pstack)) {
				printf("已清空栈！\n");
			}
			else {
				printf("操作失败！\n");
			}
			break;
		case 4:
			if (DestroyStack(pstack)) {
				printf("栈已被销毁！\n");
			}
			else {
				printf("操作失败！\n");
			}
			break;
		case 5:
			get = StackLength(stack);
			printf("栈中元素的个数为：%d\n", get);
			break;
		case 6:
			printf("打印栈中的元素:");
			StackTraverse(stack, print);
			break;
		case 7:
			printf("请输入需要入栈的数据：");
			scanf("%d", &a);
			if (Push(pstack, a)) {
			}
			else {
				printf("操作失败！\n");
			}
			break;
		case 8:
			get = Pop(pstack, e);
			if (get) {
				printf("将栈顶的元素弹出,该元素为：%d\n", *e);
			}
			else {
				printf("该栈为空！操作失败！\n");
			}
			break;
		case 0:
			printf("程序已退出！\n");
			k = 0;
			break;
		default:
			printf("请在0-8之间选择！\n");
		}
	}
	system("pause");
	return 0;
}