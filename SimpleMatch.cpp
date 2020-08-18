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

//�����Ӵ�strSub������strMain�е�pos���ַ����λ�ã��������ڣ���������0
int Index(char *strMain, char *strSub, int pos) {
	int i = pos;  //i��������strMain�е�ǰλ���±�ֵ
	int j = 1;    //j�����Ӵ�strSub �е�ǰλ���±�ֵ
	int lenMain = getCharLength(strMain); //��������
	int lenSub = getCharLength(strSub);   //�Ӵ�����
	while (i <= lenMain && j <= lenSub) {
		if (strMain[i] == strSub[j-1]) {  //�����ַ���ȼ������Ƚ�
			++i;
			++j;
		}
		else {                //ָ��������¿�ʼƥ��
			i = i - j + 2;    //i���ݵ���һ��ƥ����λ����һ��
			j = 1;            //j�˻ص��Ӵ�T����λ
		}
	}
	if (j > lenSub) {         //j�����Ӵ��ĳ��ȣ�˵���������ҵ����Ӵ���ȫƥ����ַ���
		return i - lenSub + 1;//���ظ��ַ������׸��ַ��������е�λ�ã���1����ΪC���ַ����Ǵ�0��ʼ�ģ���ϰ�����Ǵ�1��ʼ�ģ�Ϊ�˸�ֱ�۵��ò��������
	}
	else {                    //��֮��û���ҵ�ƥ����ַ���������0
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
	k = Index(strMain, strSub, pos);
	if (k) {
		printf("The result of index is:%d\n", k);
	}
	else {
		printf("Sorry!No corresponding results were found!\n");
	}
	system("pause");
	return 0;
}