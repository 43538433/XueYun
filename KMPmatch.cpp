#include<stdio.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

//��ȡĳ���ַ����ĳ���
int getCharLength(char *string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

// ͨ�����㷵���Ӵ�T��next����
void get_next(char *strSub, int *next) {
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;
	int lenSub = getCharLength(strSub);
	while (i < lenSub) {
		if (j == 0 || strSub[i] == strSub[j]) { //strSub[i]��ʾ��׺�ĵ����ַ���strSub[j]��ʾǰ׺�ĵ����ַ�
			i++;
			j++;
			next[i] = j;
		}
		else {
			j = next[j];    //���ַ�����ͬ����jֵ����
		}
	}
}

/*
��ģʽ��T��next��������ֵ����������nextval��next���������
ʹ��ʱ��ֻ���Index_KMP�е�get_next(strSub, next); ��Ϊget_nextval(strSub, next); ����
*/
void get_nextval(char *strSub, int *nextval) {
	int i, j;
	i = 1;
	j = 0;
	nextval[1] = 0;
	int lenSub = getCharLength(strSub);
	while (i < lenSub) {
		if (j == 0 || strSub[i] == strSub[j]) { //strSub[i]��ʾ��׺�ĵ����ַ���strSub[j]��ʾǰ׺�ĵ����ַ�
			i++;
			j++;
			if (strSub[i] != strSub[j]) {       //����ǰ�ַ���ǰ׺�ַ���ͬ
				nextval[i] = j;                 //��ǰ��jΪnextval��iλ�õ�ֵ
			}
			else {
				nextval[i] = nextval[j];        //�����ǰ׺�ַ���ȣ���ǰ׺�ַ���nextvalֵ��ֵ��nextval[i]
			}
		}
		else {
			j = nextval[j];                     //���ַ�����ͬ����jֵ����
		}
	}
}

//�����Ӵ�T������S�е�pos���ַ�֮���λ�á��������ڣ���������ֵΪ0
int Index_KMP(char *strMain, char *strSub, int pos) {
	int i = pos;   //i��������strMain�е�ǰλ���±�ֵ
	int j = 1;     //j�����Ӵ�strSub �е�ǰλ���±�ֵ
	int lenMain = getCharLength(strMain);  //��������
	int lenSub = getCharLength(strSub);    //�Ӵ�����
	int next[100];                 //����һ��next����
	get_next(strSub, next);        //�����õ�next����
	while (i <= lenMain && j <= lenSub) {
		if (j == 0 || strMain[i] == strSub[j - 1]) {
			i++;
			j++;
		}
		else {
			j = next[j];   //ָ��������¿�ʼƥ�䣬j�˻غ��ʵ�λ�ã�iֵ����
		}
	}
	if (j > lenSub) {
		return i - lenSub + 1;
	}
	else {
		return 0;
	}
}

int main() {
	char strMain[100];
	char strSub[100];
	int k, pos;
	int m = 1;
	printf("Please input the source string:\n");
	scanf("%s", strMain);
	printf("Please input the goal string:\n");
	scanf("%s", strSub);
	printf("Please input the value of pos:\n");
	scanf("%d", &pos);
	while (m) {
		if (pos < 0 || pos >= getCharLength(strMain)) {
			printf("The value of pos is not right,please try again:");
			scanf("%d", &pos);
		}
		else {
			m = 0;
		}
	}
	k = Index_KMP(strMain, strSub, pos);
	if (k) {
		printf("The result of index is:%d\n", k);
	}
	else {
		printf("Sorry!No corresponding results were found!\n");
	}
	system("pause");
	return 0;
}