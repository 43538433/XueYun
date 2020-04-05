//˳��ջ
//�ο��ڣ�https://www.cnblogs.com/mwq1024/p/10146943.html
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
#define STACK_INIT_SIZE 100     //����ռ��ʼ������
#define STACKINCREMENT  10      //�洢�ռ��������
#define OK 1
#define ERROR 0
int k = 1;
typedef int StackType; //ջԪ������

typedef struct {
	StackType *base;   //�ڹ���֮ǰ������֮��base��ֵΪNULL
	StackType *top;    //ջ��ָ��
	int stacksize;     //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack; //˳��ջ

//ջ�ĳ�ʼ��
int InitStack(SqStack *p) {
	p->base = (StackType*)malloc(STACK_INIT_SIZE * sizeof(StackType));
	if (p->base == NULL)  return ERROR;  //�ڴ����ʧ��
	p->top = p->base;                    //ջ����ջ����ͬ��ʾһ����ջ
	p->stacksize = STACK_INIT_SIZE;
	return OK;

}

//�ж�ջ�Ƿ�Ϊ��
int EmptyStack(SqStack *p) {             //��Ϊ��ջ �򷵻�OK�����򷵻�ERROR
	if (p->top == p->base) return OK;
	else return ERROR;
}

//˳��ջ��ѹ��
int Push(SqStack *p, StackType e) {           //����Ԫ��eΪ�µ�ջ��Ԫ��
	if ((p->top - p->base) >= p->stacksize)   //ջ����׷�Ӵ���ռ�
	{
		p->base = (StackType*)realloc(p->base, (p->stacksize + STACKINCREMENT) * sizeof(StackType));
		if (p->base == NULL)   return ERROR;  // ����ռ����ʧ��
		p->top = p->base + p->stacksize;      
		p->stacksize += STACKINCREMENT;
	}
	*(p->top) = e;
	(p->top)++;
	printf("������ջ�ɹ���\n");
	return OK;
}

// ˳��ջ�ĵ���     
int Pop(SqStack *p, StackType *e) {           //��ջ���գ���ɾ��p��ջ��Ԫ�أ���e������ֵ
	if (p->top == p->base) return ERROR;
	--(p->top);
	*e = *(p->top);
	return OK;
}

//˳��ջ������
int DestroyStack(SqStack *p) {                
	free(p->base);                            //�ͷ�ջ�׿ռ䲢�ÿ�
	p->base = NULL;
	p->top = NULL;
	p->stacksize = 0;
	return OK;
}

//��˳��ջ�ÿ� ջ���Ǵ��ڵģ�ջ�е�Ԫ��Ҳ���ڣ������ջ��Ԫ�صĵ�ַ��Ȼ�ܵ���
int ClearStack(SqStack *p) {
	p->top = p->base;
	return OK;
}

//����˳��ջ��Ԫ�ظ���
int StackLength(SqStack p) {
	//ջ��ָ���ȥջ��ָ����ڳ��ȣ���Ϊջ��ָ��ָ��ǰջ��Ԫ�ص���һ��λ��
	return p.top - p.base;
}

//����˳��ջ��ջ��Ԫ��
int GetTop(SqStack *p, StackType *e) {
	//��ջ��Ϊ�գ�����e����p��ջ��Ԫ��
	if (p->top > p->base) {
		*e = *(p->top - 1); return OK;
	}
	else return ERROR;
}

//��ջ�׵�ջ�����ζ�ջ�е�ÿ��Ԫ�ص��ú���pfun(),����ջ
int StackTraverse(SqStack p, void(*pfun)(StackType)/*����ָ��*/) {
	
	while (p.top > p.base)
		pfun(*(p.base)++);                //�ȵ��ú����
	printf("\n");
	return OK;
}

//��ӡջ��Ԫ��
void print(StackType stack) {
	printf("%d  ", stack);
}

//����ջ�ĸ��ֲ���
int main() {
	int n, i;
	//int get;
	StackType *e, a;
	SqStack *pstack, stack;
	pstack = &stack;
	e = (StackType*)malloc(sizeof(StackType));    //Ϊָ��e�����ڴ��ַ
	//InitStack(pstack);                            //��ʼ��ջ
	if (InitStack(pstack)) {
		printf("��ջ������ɣ�\n");
	}
	else {
		printf("��ջ����ʧ�ܣ�\n");
	}
	float len;
	printf("������ջ�Ĵ�С��");
	n = scanf("%f", &len);
	while (n == 0) {
		while (getchar() != '\n');
		printf("�ף�������Ĳ�������Ŷ����");
		printf("����������ջ�ĳ��ȣ�");
		n = scanf("%f", &len);
	}
	for (i = 0; i < (int)len; i++)
	{
		printf("�������%d����ջ���ݣ�",i+1);
		scanf("%d", &a);
		Push(pstack, a);
	}
	printf("\n");
	printf("\n*******************************************************************************\n");
	printf("*********************�� �� �� �� ֮ ˳ �� ջ �� �� �� ��***********************\n");
	printf("**********************�� �ߣ�Ѧ �ƣ�3219005084��*******************************\n");
	printf("*                            1.�ж�ջ�Ƿ�Ϊ��                               *\n");
	printf("*                            2.�õ�ջ��Ԫ��                                   *\n");
	printf("*                            3.���ջ                                         *\n");
	printf("*                            4.����ջ                                         *\n");
	printf("*                            5.����ջ����                                     *\n");
	printf("*                            6.����ջ��Ԫ��                                   *\n");
	printf("*                            7.��ջ                                           *\n");
	printf("*                            8.��ջ                                           *\n");
	printf("*                            0.�˳�                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	while (k) {
		float choose;
		int n;
		int get;
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
		case 1:
			if (EmptyStack(pstack) == 0) {
				printf("ջ��Ϊ��!\n");
			}
			else {
				printf("ջΪ�գ�\n");
			}
			break;
		case 2:
			get = GetTop(pstack, e);
			if (get) {
				printf("ջ����Ԫ��Ϊ��%d\n", *e);
			}
			else {
				printf("����ʧ�ܣ�ջΪ�գ�\n");
			}
			break;
		case 3:
			if (ClearStack(pstack)) {
				printf("�����ջ��\n");
			}
			else {
				printf("����ʧ�ܣ�\n");
			}
			break;
		case 4:
			if (DestroyStack(pstack)) {
				printf("ջ�ѱ����٣�\n");
			}
			else {
				printf("����ʧ�ܣ�\n");
			}
			break;
		case 5:
			get = StackLength(stack);
			printf("ջ��Ԫ�صĸ���Ϊ��%d\n", get);
			break;
		case 6:
			printf("��ӡջ�е�Ԫ��:");
			StackTraverse(stack, print);
			break;
		case 7:
			printf("��������Ҫ��ջ�����ݣ�");
			scanf("%d", &a);
			if (Push(pstack, a)) {
			}
			else {
				printf("����ʧ�ܣ�\n");
			}
			break;
		case 8:
			get = Pop(pstack, e);
			if (get) {
				printf("��ջ����Ԫ�ص���,��Ԫ��Ϊ��%d\n", *e);
			}
			else {
				printf("��ջΪ�գ�����ʧ�ܣ�\n");
			}
			break;
		case 0:
			printf("�������˳���\n");
			k = 0;
			break;
		default:
			printf("����0-8֮��ѡ��\n");
		}
	}
	system("pause");
	return 0;
}