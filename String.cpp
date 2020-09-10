//�ο����ͣ�https://www.cnblogs.com/itgungnir/p/6690133.html
#include<stdio.h>
#include<stdlib.h>

typedef int Status;
#define OK 1
#define ERROR 0
#define S1BIG 2
#define EQUAL 3
#define S2BIG 4
#define MAXSIZE 100

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);
/*
ע�⣺�ַ���������'\0'���Ž�β��
*/

//�����ַ��������ݽṹ��
typedef struct String {
	char *data;       //����ŵ���ʼ��ַ
	int curLength;    //���ĵ�ǰ�ĳ���
	int maxLength;    //�ַ������ܳ��ȣ�����Ĵ洢�ռ�Ĵ�С
}String;

//��ȡĳ���ַ����ĳ���
int getCharLength(char *string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

//���ĳ�ʼ������������һ���µ��ַ��������а���string�е������ַ���
Status InitString(String *S, char *string) {
	int i = 0;
	int length = getCharLength(string);  //��ȡ�ַ���string�ĳ���
	S->data = (char*)malloc(sizeof(char));
	if (S->data == NULL) {
		printf("�ռ����ʧ�ܣ���ʼ���ַ���ʧ�ܣ���\n");
		printf("δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		return ERROR;
	}
	S->curLength = length;
	S->maxLength = MAXSIZE;
	for (i = 0; i < length; i++) {   //��string��ֵ��S
		S->data[i] = string[i];
	}
	return OK;
}

//��ֵ�ַ�������string�е������ַ����Ƶ��ַ���S�У�
Status copyString(String *S, char *string) {
	int i;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("δ��ʼ���ַ������ַ��������ڣ�����ʧ�ܣ���\n");
		printf("δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (length > S->maxLength) {
		S->data = (char*)realloc(S->data, length * sizeof(char));// realloc���������޸�һ��ԭ���Ѿ�������ڴ��Ĵ�С������ʹһ���ڴ���������С
		if (S->data == NULL) {
			printf("�ط���ռ�ʧ�ܣ������ַ���ʧ�ܣ���\n");
			return ERROR;
		}
		S->maxLength = length;
	}
	S->curLength = length;
	for (i = 0; i < length; i++) {
		S->data[i] = string[i];
	}
	return OK;
}

//�ж��ַ����Ƿ�Ϊ��
Status isStringEmpty(String *S) {
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (S->curLength == 0) {
		return OK;
	}
	return ERROR;
}

//�Ƚ������ַ����Ĵ�С�����ص���S1��S2�ȽϵĽ����
Status compareString(String *S1, String *S2) {
	int i = 0;
	if (S1->data == NULL || S2->data == NULL) {
		printf("����������һ���ַ��������ڣ�ֻ�е������ַ��������ڲſɱȽ�!\n");
		return ERROR;
	}
	if (S1->curLength > S2->curLength) {
		return S1BIG;
	}
	else if (S1->curLength < S2->curLength) {
		return S2BIG;
	}
	else if (S1->curLength == 0 && S2->curLength == 0) {
		return EQUAL;
	}
	else {
		for (i = 0; ; i++) {
			if (S1->data[i] > S2->data[i]) {
				return S1BIG;
			}
			else if(S1->data[i]<S2->data[i]){
				return S2BIG;
			}
		}
	}

}

//��ȡ�ַ����ĳ���
int getStringLength(String *S) {
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	return S->curLength;
}

//����ַ���
Status clearString(String *S) {
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	S->curLength = 0;
	return OK;
}

//���ַ���S2���ӵ��ַ���S1����
Status concatString(String *S1, String *S2) {
	if (S1->data == NULL || S2->data == NULL) {
		printf("����������һ���ַ��������ڣ�ֻ�е������ַ��������ڲſ�ƴ��!\n");
		return ERROR;
	}
	int i;
	int len1 = getStringLength(S1);
	int len2 = getStringLength(S2);
	if (S1->maxLength < len1 + len2) {
		S1->data = (char*)realloc(S1->data, (len1 + len2) * sizeof(char));
		if (S1->data == NULL) {
			printf("���·���ռ�ʧ�ܣ��ַ���ƴ��ʧ�ܣ�\n");
			return ERROR;
		}
		S1->maxLength = len1 + len2;
	}
	for (i = 0; i < len2; i++) {
		S1->data[len1 + i] = S2->data[i];
	}
	S1->curLength = len1 + len2;
	return OK;
}

//�����ַ���S�д�posλ�ÿ�ʼ������Ϊlen���ַ���
char* getSubString(String *S, int pos, int len) {
	char* result = NULL;
	int i;
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos�����ѳ����ַ�����Χ��\n");
		exit(1);
	}
	if (len > S->curLength - pos) {
		printf("�Ӵ����ȳ�����Χ��\n");
		exit(1);
	}
	for (i = 0; i < len; i++) {
		result[i]= S->data[pos + i];
	}
	result[i] = '\0';  //���ַ���result��һ��������
	return result;
}

//�����ַ���S�д�posλ�ÿ�ʼ�����Ӵ�string��ȵĵ�һ���Ӵ���λ��
int locateSubString(String *S, char *string, int pos) {
	int i, j;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos�����ѳ����ַ�����Χ��\n");
		return 0;
	}
	if(length + pos > S->curLength) {
		printf("�Ӵ����ȳ�����Χ��\n");
		return 0;
	}
	for (i = pos; i <= S->curLength - length; i++) {
		for (j = 0; j < length; j++) {
			if (S->data[i + j] != string[j]) {
				break;
			}
		}
		if (j == length) {
			return i;  //�ҵ������������Ӵ��������Ӵ���λ��
		}
	}
	return -1;//û���ҵ������������Ӵ�������-1
}

//���ַ���S��posλ�ò����ַ���string
Status stringInsert(String *S, int pos, char *string) {
	int i;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (pos<0 || pos>S->curLength) {
		printf("pos����������Χ�������ַ�ʧ�ܣ�\n");
		return ERROR;
	}
	if (S->curLength + length > S->maxLength) {
		S->data = (char*)realloc(S->data, (S->curLength + length) * sizeof(char));
		if (S->data == NULL) {
			printf("���·���ռ�ʧ�ܣ������ַ�ʧ�ܣ�\n");
			return ERROR;
		}
		S->maxLength = S->curLength + length;
	}
	for (i = S->curLength - 1; i >= pos; i--) {//��posλ�ú���ַ�����ƶ�length������
		S->data[i + length] = S->data[i];
	}
	for (i = 0; i < length; i++) {  //��pos�����string
		S->data[pos + i] = string[i];
	}
	S->curLength = S->curLength + length;
	return OK;
}

//ɾ���ַ���S�д�posλ�ÿ�ʼ��len���ַ�
Status stringDelete(String *S, int pos, int len) {
	int i;
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos����������Χ��ɾ���ַ�ʧ�ܣ�\n");
		return ERROR;
	}
	if (pos + len > S->curLength) {
		printf("�Ӵ����ȳ�����Χ��ɾ���ֽ�ʧ�ܣ���\n");
		return ERROR;
	}
	for (i = pos + len; i < S->curLength; i++) {
		S->data[i - len] = S->data[i];
	}
	S->curLength = S->curLength - len;
	return OK;
}

//���ַ���newStr�滻�ַ���S�г��ֵ��������Ӵ�oldStr��ͬ�Ĳ��ص����Ӵ�
Status replaceString(String *S, char *oldStr, char *newStr) {
	int index;
	int oldLen = getCharLength(oldStr);
	int newLen = getCharLength(newStr);
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	index = locateSubString(S, oldStr, 0);
	while (index >= 0 && index + oldLen <= S->curLength) {
		stringDelete(S, index, oldLen);
		stringInsert(S, index, newStr);
		if (oldLen + index + newLen >= S->curLength) { //�����̫���ΪʲôҪ��oldLen??
			break;
		}
		index = locateSubString(S, oldStr, index + newLen);
	}
	return OK;
}

//�����ַ���
void traverseString(String *S) {
	int i;
	if (S->data == NULL) {
		printf("��δ��ʼ���ַ������ַ��������ڣ��޷�ʵ���������ܣ����򼴽��˳�����\n");
		exit(1);
	}
	for (i = 0; i < S->curLength; i++) {
		printf("%c", S->data[i]);
	}
	printf("\n");
}

//�����ַ���
Status destoryString(String *S) {
	if (S->data == NULL) {
		printf("�ַ��������ڣ��������٣�\n");
		return ERROR;
	}
	free(S->data);
	S->data = NULL;
	S->curLength = 0;
	S->maxLength = 0;
	return OK;
}

void menu() {
	printf("\n*******************************************************************************\n");
	printf("*******************************�� �� �� �� ֮ ��*******************************\n");
	printf("***************************�� �ߣ�Ѧ �ƣ�3219005084)***************************\n");
	printf("*     1.�ַ����п�                                                            *\n");
	printf("*     2.�ַ�������                                                            *\n");
	printf("*     3.��string�е������ַ����Ƶ��ַ���S��                                   *\n");
	printf("*     4.�Ƚ������ַ����Ĵ�С                                                  *\n");
	printf("*     5.ƴ�������ַ���                                                        *\n");
	printf("*     6.�����ַ���S�д�posλ�ÿ�ʼ������Ϊlen���Ӵ�                           *\n");
	printf("*     7.�����ַ���S�д�posλ�ÿ�ʼ�����Ӵ���ȵĵ�һ���Ӵ���λ��              *\n");
	printf("*     8.���ַ���S��posλ�ò����ַ���string                                    *\n");
	printf("*     9.ɾ���ַ���S�д�posλ�ÿ�ʼ��len���ַ�                                 *\n");
	printf("*     10.���ַ���newStr�滻�ַ���S�г��ֵ��������Ӵ�oldStr��ͬ�Ĳ��ص����Ӵ�  *\n");
	printf("*     11.����ַ���                                                           *\n");
	printf("*     12.�����ַ���                                                           *\n");
	printf("*     13.�����ַ���                                                           *\n");
	printf("*     0.�˳�                                                                  *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
}

int main() {
	String str1, str2, str3, str4; //����������str1��ԭ�ַ�����str2�ǱȽϴ�С��str3��ƴ�ӡ�
	char ch[100];
	int k = 1;
	printf("��ʼ���ַ���S1��������һ���ַ���(С�ڻ����100���ַ���)��\n"); //�����и�bug����������������100���ַ����ͻ������...
	scanf("%s", ch);//����������Ѿ�����õġ��ַ��������������ü�&����Ϊ��C��������������ʾ�������ʼ��ַ
	if (InitString(&str1, ch)) {
		printf("��ʼ���ַ���S1�ɹ���\n");
	}
	menu();
	while (k) {
		float choose;
		int n;
		printf("\n");
		printf("��ǰ�ַ���Ϊ��\n");
		traverseString(&str1);
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
			if (isStringEmpty(&str1)) {
				printf("���ַ���Ϊ�գ�\n");
			}
			else {
				printf("���ַ�����Ϊ�գ�\n");
			}
			break;
		}
		case 2: {
			int m;
			m = getStringLength(&str1);
			printf("���ַ����ĳ���Ϊ��%d\n", m);
			break;
		}
		case 3: {
			char ch1[100];
			printf("��������Ҫ���Ƶ��ַ���string(С�ڵ���100���ַ���)��\n");
			scanf("%s", ch1);  //�����и�bug����������������100���ַ����ͻ������...
			if (copyString(&str1, ch1)) {
				printf("�ַ������Ƴɹ���\n");
			}
			else {
				printf("�ַ�������ʧ�ܣ�\n");
			}
			break;
		}
		case 4: {
			char ch2[100];
			printf("��������Ҫ��ԭ�ַ����Ƚ��ַ���S2(С�ڻ����100���ַ���)��\n"); //�����и�bug����������������100���ַ����ͻ������...
			scanf("%s", ch2);//����������Ѿ�����õġ��ַ��������������ü�&����Ϊ��C��������������ʾ�������ʼ��ַ
			if (InitString(&str2, ch2)) {
				printf("��ʼ���ַ���S2�ɹ���\n");
			}
			else {
				break;
			}
			int a = compareString(&str1, &str2);
			switch (a)
			{
			case 0: {
				printf("���������ԣ�\n");
				break;
			}
			case 2 : {
				printf("�ַ���S2С��S1\n");
				printf("�ַ���S1Ϊ��");
				traverseString(&str1);
				printf("�ַ���S2Ϊ��");
				traverseString(&str2);
				break;
			}
			case 3: {
				printf("�ַ���S2����S1\n");
				printf("�ַ���S1Ϊ��");
				traverseString(&str1);
				printf("�ַ���S2Ϊ��");
				traverseString(&str2);
				break;
			}
			case 4: {
				printf("�ַ���S2����S1\n");
				printf("�ַ���S1Ϊ��");
				traverseString(&str1);
				printf("�ַ���S2Ϊ��");
				traverseString(&str2);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 5: {
			char ch3[100];
			printf("��������Ҫƴ�ӵ�S������ַ���(С�ڻ����100���ַ���)��\n");
			scanf("%s", ch3);
			if (InitString(&str3, ch3)) {
				printf("��ʼ���ַ���S3�ɹ���\n");
			}
			if (concatString(&str1, &str3)) {
				printf("�ַ���ƴ�ӳɹ���\n");
			}
			else {
				printf("�����³��ԣ�\n");
			}
			break;
		}
		case 6: {
			int a, b;
			char *ch4;
			printf("���磺SΪ��friend��,����posΪ4������lenΪ3����õ����Ϊ��end��\n");
			printf("������pos��ֵ��");
			scanf("%d", &a);
			printf("������len��ֵ��");
			scanf("%d", &b);
			ch4 = getSubString(&str1, a, b);
			if (InitString(&str4, ch4)) {
				printf("���ص��Ӵ�Ϊ��");
				traverseString(&str4);
			}
			break;
		}
		case 7: {
			char ch5[100];
			int a, b;
			printf("��������Ҫ���ҵ��Ӵ�(С�ڻ����100���ַ���)��\n");
			scanf("%s", ch5);
			printf("������pos��ֵ��");
			scanf("%d", &a);
			b = locateSubString(&str1, ch5, a);
			switch (b)
			{
			case 0: {
				printf("�����³��ԣ�\n");
				break;
			}
			case -1: {
				printf("δ���ҵ������������Ӵ�!\n");
				break;
			}
			default:
				printf("���Ӵ���λ��Ϊ��%d", b);
				break;
			}
			break;
		}
		case 8: {
			char ch6[100];
			int a;
			printf("��������Ҫ������ַ���(С�ڻ����100���ַ���)��\n");
			printf("������pos��ֵ��");
			scanf("%d", &a);
			if (stringInsert(&str1, a, ch6)) {
				printf("�ַ�������ɹ���\n");
			}
			else {
				printf("���������ԣ�\n");
			}
			break;
		}
		case 9: {
			int a, b;
			printf("������pos��ֵ��");
			scanf("%d", &a);
			printf("������len��ֵ��");
			scanf("%d", &b);
			if (stringDelete(&str1, a-1, b)) {
				printf("ɾ���ɹ���\n");
			}
			else {
				printf("���������ԣ�\n");
			}
			break;
		}
		case 10: {
			char newStr[100], oldStr[100];
			printf("������newString��");
			scanf("%s", newStr);
			printf("��������Ҫ�滻��oldString��");
			scanf("%s", oldStr);
			replaceString(&str1, oldStr, newStr);
			printf("�滻�ɹ���\n");
			break;
		}
		case 11: {
			clearString(&str1);
			printf("�ַ���S1��ճɹ���\n");
			break;
		}
		case 12: {
			if (destoryString(&str1)) {
				printf("�����ַ���S1�ɹ���\n");
			}
			if (destoryString(&str2)) {
				printf("�����ַ���S2�ɹ���\n");
			}
			if (destoryString(&str3)) {
				printf("�����ַ���S3�ɹ���\n");
			}
			if (destoryString(&str4)) {
				printf("�����ַ���S4�ɹ���\n");
			}
			break;
		}
		case 13: {
			printf("�����ַ�����");
			traverseString(&str1);
			break;
		}
		case 20: {
			printf("%d\n", &str1);
			printf("%d\n", &str2);
			printf("%d\n", &str3);
			printf("%d\n", &str4);
			break;
		}
		case 0: {
			printf("�����˳�����\n");
			k = 0;
			break;
		}
		default: {
			printf("����0-13֮��ѡ��\n");
			break;
		}
		}
	}
	system("pause");
	return 0;
}