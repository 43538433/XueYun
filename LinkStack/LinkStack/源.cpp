#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
int k = 1;
int count;

typedef struct Node {      //�����ڵ�
	int data;              //������
	struct Node *next;     //ָ����
}LinkStack;

/*������ջ*/
int InitStack(LinkStack *&S)//*&Ϊ���ã�����ֱ���޸�ʵ��ָ���λ��
{                           //��ջ����ͷ��㣬��ʼ����ջֻ��Ҫ��ջ����Ϊ��
	S = (LinkStack *)malloc(sizeof(LinkStack));
	S->next = NULL;//ջΪ�յı�־
	return 1;
}

/*�пղ���*/
int Empty(LinkStack *S)
{
	if (S->next == NULL) {
		return 1;
	}
	else
		return 0;
}

/*����ջ��Ϊ��*/
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

/*���ص�ǰջ�ĳ���*/
int StackLen() {
	return count;
}

/*����ջ
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

/*��ջ*/
void Push(LinkStack* &S, int x)//SΪͷ���
{
	LinkStack *p;
	p = (LinkStack *)malloc(sizeof(LinkStack));//����һ�������ڵ�
	p->data = x;//����Ҫ��ջ����Ϣ
	p->next = S->next;
	S->next = p;
	count++;
	printf("��������ѹ��ջ��\n");
}

/*��ջ*/
int Pop(LinkStack *&S, int &ptr)//ͨ��*ptr���س�ջ��ֵ,SΪͷ���
{
	LinkStack *p = S->next;
	if (S->next == NULL)
	{
		return 0;
	}
	else
	{
		ptr = p->data;//����ջ����ֵ
		S->next = p->next;//ջ��λ�ñ仯
		free(p);//�ͷ�ջ���ռ�
		count--;
		return ptr;
	}
}

/*ȡջ��Ԫ��*/
int GetTop(LinkStack *S, int &ptr)//���ջ������ڲ��ı�ջ
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
		if (Empty(S)) {
			printf("����ջΪ�գ���\n");
		}
		else {
			printf("����ջ��Ϊ�գ���\n");
		}
		break;
	case 2:
		get = GetTop(S, data);
		if (!get) {
			printf("��ջΪ�գ���\n");
		}
		else {
			printf("��ջ��ջ��Ԫ��Ϊ:%d\n", data);
		}
		break;
	case 3:
		if (ResetStack(S)) {
			printf("����ջΪ�գ���\n");
		}
		else {
			printf("�������ջ����\n");
		}
		break;
	/*case 4:
		DestroyStack(S);
		printf("��ջ�ѱ����٣�\n");
		break;*/
	case 4:
		get= StackLen();
		if (get) {
			printf("����ջ��ǰ�ĳ���Ϊ��%d\n", get);
		}
		else {
			printf("��ջΪ�գ�\n");
		}
		break;
	case 5:
		float set;
		int Rset;
		printf("������һ�����ݣ�");
		get=scanf("%f", &set);
		while (get == 0) {
			while (getchar() != '\n');
			printf("�ף�������Ĳ�������Ŷ����");
			printf("������ѡ��");
			n = scanf("%f", &set);
		}
		Rset = (int)set;
		Push(S, Rset);
		break;
	case 6:
		if (Pop(S, data)) {
			printf("�ѽ�ջ���������Ƴ�ջ,������Ϊ��");
			printf("%d\n", data);
		}
		else {
			printf("����ʧ�ܣ���\n");
		}
		break;
	case 0:
		printf("�������˳���\n");
		k = 0;
		break;
	default:
		printf("����0-6֮��ѡ��\n");
	}
}

int main()
{
	//int x;//������ȡ��ջ����
	//int y;
	LinkStack *top;//����ջ��ָ�벢��ʼ��
	if (InitStack(top)) {
		printf("����ջ������ɣ�\n");
	}
	else {
		printf("����ջ����ʧ�ܣ�\n");
	}
	float len;
	int n;
	printf("������ջ�Ĵ�С��");
	n = scanf("%f", &len);
	while (n == 0) {
		while (getchar() != '\n');
		printf("�ף�������Ĳ�������Ŷ����");
		printf("����������ջ�ĳ��ȣ�");
		n = scanf("%f", &len);
	}
	float num;
	for (int i = 1; i <=(int)len; i++) {
		printf("�������%d�����ݣ�", i);
		n = scanf("%f", &num);
		while (n == 0) {
			while (getchar() != '\n');
			printf("�ף�������Ĳ�������Ŷ����");
			printf("�����������%d�����ݣ�", i);
			n = scanf("%f", &num);
		}
		Push(top, (int)num);
		if (i == len) {
			printf("�ѽ�ȫ������ѹ��ջ\n");
		}
	}
	printf("\n*******************************************************************************\n");
	printf("**********************�� �� �� �� ֮ �� ջ �� �� �� ��*************************\n");
	printf("**********************�� �ߣ�Ѧ �ƣ�3219005084��*******************************\n");
	printf("*                            1.�ж���ջ�Ƿ�Ϊ��                               *\n");
	printf("*                            2.�õ�ջ��Ԫ��                                   *\n");
	printf("*                            3.���ջ                                         *\n");
	printf("*                            4.����ջ����                                     *\n");
	printf("*                            5.��ջ                                           *\n");
	printf("*                            6.��ջ                                           *\n");
	printf("*                            0.�˳�                                           *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
	while (k) {
		menu(top);
	}
	system("pause");
	return 0;
}