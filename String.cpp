//参考博客：https://www.cnblogs.com/itgungnir/p/6690133.html
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
注意：字符串都是以'\0'符号结尾的
*/

//定义字符串的数据结构体
typedef struct String {
	char *data;       //串存放的起始地址
	int curLength;    //串的当前的长度
	int maxLength;    //字符串的总长度，分配的存储空间的大小
}String;

//获取某个字符串的长度
int getCharLength(char *string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

//串的初始化操作（创建一个新的字符串，其中包含string中的所有字符）
Status InitString(String *S, char *string) {
	int i = 0;
	int length = getCharLength(string);  //获取字符串string的长度
	S->data = (char*)malloc(sizeof(char));
	if (S->data == NULL) {
		printf("空间分配失败，初始化字符串失败！！\n");
		printf("未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		return ERROR;
	}
	S->curLength = length;
	S->maxLength = MAXSIZE;
	for (i = 0; i < length; i++) {   //将string赋值给S
		S->data[i] = string[i];
	}
	return OK;
}

//赋值字符串（将string中的所有字符复制到字符串S中）
Status copyString(String *S, char *string) {
	int i;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("未初始化字符串，字符串不存在，复制失败！！\n");
		printf("未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (length > S->maxLength) {
		S->data = (char*)realloc(S->data, length * sizeof(char));// realloc函数用于修改一个原先已经分配的内存块的大小，可以使一块内存的扩大或缩小
		if (S->data == NULL) {
			printf("重分配空间失败，复制字符串失败！！\n");
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

//判断字符串是否为空
Status isStringEmpty(String *S) {
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (S->curLength == 0) {
		return OK;
	}
	return ERROR;
}

//比较两个字符串的大小（返回的是S1与S2比较的结果）
Status compareString(String *S1, String *S2) {
	int i = 0;
	if (S1->data == NULL || S2->data == NULL) {
		printf("其中至少有一个字符串不存在！只有当两个字符串均存在才可比较!\n");
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

//获取字符串的长度
int getStringLength(String *S) {
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	return S->curLength;
}

//清空字符串
Status clearString(String *S) {
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	S->curLength = 0;
	return OK;
}

//将字符串S2连接到字符串S1后面
Status concatString(String *S1, String *S2) {
	if (S1->data == NULL || S2->data == NULL) {
		printf("其中至少有一个字符串不存在！只有当两个字符串均存在才可拼接!\n");
		return ERROR;
	}
	int i;
	int len1 = getStringLength(S1);
	int len2 = getStringLength(S2);
	if (S1->maxLength < len1 + len2) {
		S1->data = (char*)realloc(S1->data, (len1 + len2) * sizeof(char));
		if (S1->data == NULL) {
			printf("重新分配空间失败，字符串拼接失败！\n");
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

//返回字符串S中从pos位置开始，长度为len的字符串
char* getSubString(String *S, int pos, int len) {
	char* result = NULL;
	int i;
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos参数已超出字符串范围！\n");
		exit(1);
	}
	if (len > S->curLength - pos) {
		printf("子串长度超出范围！\n");
		exit(1);
	}
	for (i = 0; i < len; i++) {
		result[i]= S->data[pos + i];
	}
	result[i] = '\0';  //给字符串result加一个结束符
	return result;
}

//返回字符串S中从pos位置开始的与子串string相等的第一个子串的位置
int locateSubString(String *S, char *string, int pos) {
	int i, j;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos参数已超出字符串范围！\n");
		return 0;
	}
	if(length + pos > S->curLength) {
		printf("子串长度超出范围！\n");
		return 0;
	}
	for (i = pos; i <= S->curLength - length; i++) {
		for (j = 0; j < length; j++) {
			if (S->data[i + j] != string[j]) {
				break;
			}
		}
		if (j == length) {
			return i;  //找到符和条件的子串，返回子串的位置
		}
	}
	return -1;//没有找到符合条件的子串，返回-1
}

//在字符串S的pos位置插入字符串string
Status stringInsert(String *S, int pos, char *string) {
	int i;
	int length = getCharLength(string);
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (pos<0 || pos>S->curLength) {
		printf("pos参数超出范围，插入字符失败！\n");
		return ERROR;
	}
	if (S->curLength + length > S->maxLength) {
		S->data = (char*)realloc(S->data, (S->curLength + length) * sizeof(char));
		if (S->data == NULL) {
			printf("重新分配空间失败，插入字符失败！\n");
			return ERROR;
		}
		S->maxLength = S->curLength + length;
	}
	for (i = S->curLength - 1; i >= pos; i--) {//将pos位置后的字符向后移动length个长度
		S->data[i + length] = S->data[i];
	}
	for (i = 0; i < length; i++) {  //在pos后插入string
		S->data[pos + i] = string[i];
	}
	S->curLength = S->curLength + length;
	return OK;
}

//删除字符串S中从pos位置开始的len个字符
Status stringDelete(String *S, int pos, int len) {
	int i;
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	if (pos < 0 || pos >= S->curLength) {
		printf("pos参数超出范围，删除字符失败！\n");
		return ERROR;
	}
	if (pos + len > S->curLength) {
		printf("子串长度超出范围，删除字节失败！！\n");
		return ERROR;
	}
	for (i = pos + len; i < S->curLength; i++) {
		S->data[i - len] = S->data[i];
	}
	S->curLength = S->curLength - len;
	return OK;
}

//用字符串newStr替换字符串S中出现的所有与子串oldStr相同的不重叠的子串
Status replaceString(String *S, char *oldStr, char *newStr) {
	int index;
	int oldLen = getCharLength(oldStr);
	int newLen = getCharLength(newStr);
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	index = locateSubString(S, oldStr, 0);
	while (index >= 0 && index + oldLen <= S->curLength) {
		stringDelete(S, index, oldLen);
		stringInsert(S, index, newStr);
		if (oldLen + index + newLen >= S->curLength) { //这个不太理解为什么要加oldLen??
			break;
		}
		index = locateSubString(S, oldStr, index + newLen);
	}
	return OK;
}

//遍历字符串
void traverseString(String *S) {
	int i;
	if (S->data == NULL) {
		printf("还未初始化字符串，字符串不存在！无法实现其他功能，程序即将退出！！\n");
		exit(1);
	}
	for (i = 0; i < S->curLength; i++) {
		printf("%c", S->data[i]);
	}
	printf("\n");
}

//销毁字符串
Status destoryString(String *S) {
	if (S->data == NULL) {
		printf("字符串不存在，无需销毁！\n");
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
	printf("*******************************数 据 结 构 之 串*******************************\n");
	printf("***************************作 者：薛 云（3219005084)***************************\n");
	printf("*     1.字符串判空                                                            *\n");
	printf("*     2.字符串长度                                                            *\n");
	printf("*     3.将string中的所有字符复制到字符串S中                                   *\n");
	printf("*     4.比较两个字符串的大小                                                  *\n");
	printf("*     5.拼接两个字符串                                                        *\n");
	printf("*     6.返回字符串S中从pos位置开始，长度为len的子串                           *\n");
	printf("*     7.返回字符串S中从pos位置开始的与子串相等的第一个子串的位置              *\n");
	printf("*     8.在字符串S的pos位置插入字符串string                                    *\n");
	printf("*     9.删除字符串S中从pos位置开始的len个字符                                 *\n");
	printf("*     10.用字符串newStr替换字符串S中出现的所有与子串oldStr相同的不重叠的子串  *\n");
	printf("*     11.清空字符串                                                           *\n");
	printf("*     12.销毁字符串                                                           *\n");
	printf("*     13.遍历字符串                                                           *\n");
	printf("*     0.退出                                                                  *\n");
	printf("*******************************************************************************\n");
	printf("*******************************************************************************\n");
}

int main() {
	String str1, str2, str3, str4; //声明变量【str1是原字符串，str2是比较大小，str3是拼接】
	char ch[100];
	int k = 1;
	printf("初始化字符串S1，请输入一个字符串(小于或等于100的字符串)：\n"); //这里有个bug，如果故意输入大于100的字符串就会溢出了...
	scanf("%s", ch);//输入参数是已经定义好的“字符数组名”，不用加&，因为在C语言中数组名表示数组的起始地址
	if (InitString(&str1, ch)) {
		printf("初始化字符串S1成功！\n");
	}
	menu();
	while (k) {
		float choose;
		int n;
		printf("\n");
		printf("当前字符串为：\n");
		traverseString(&str1);
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
			if (isStringEmpty(&str1)) {
				printf("该字符串为空！\n");
			}
			else {
				printf("该字符串不为空！\n");
			}
			break;
		}
		case 2: {
			int m;
			m = getStringLength(&str1);
			printf("该字符串的长度为：%d\n", m);
			break;
		}
		case 3: {
			char ch1[100];
			printf("请输入想要复制的字符串string(小于等于100的字符串)：\n");
			scanf("%s", ch1);  //这里有个bug，如果故意输入大于100的字符串就会溢出了...
			if (copyString(&str1, ch1)) {
				printf("字符串复制成功！\n");
			}
			else {
				printf("字符串复制失败！\n");
			}
			break;
		}
		case 4: {
			char ch2[100];
			printf("请输入需要与原字符串比较字符串S2(小于或等于100的字符串)：\n"); //这里有个bug，如果故意输入大于100的字符串就会溢出了...
			scanf("%s", ch2);//输入参数是已经定义好的“字符数组名”，不用加&，因为在C语言中数组名表示数组的起始地址
			if (InitString(&str2, ch2)) {
				printf("初始化字符串S2成功！\n");
			}
			else {
				break;
			}
			int a = compareString(&str1, &str2);
			switch (a)
			{
			case 0: {
				printf("请重新再试！\n");
				break;
			}
			case 2 : {
				printf("字符串S2小于S1\n");
				printf("字符串S1为：");
				traverseString(&str1);
				printf("字符串S2为：");
				traverseString(&str2);
				break;
			}
			case 3: {
				printf("字符串S2等于S1\n");
				printf("字符串S1为：");
				traverseString(&str1);
				printf("字符串S2为：");
				traverseString(&str2);
				break;
			}
			case 4: {
				printf("字符串S2大于S1\n");
				printf("字符串S1为：");
				traverseString(&str1);
				printf("字符串S2为：");
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
			printf("请输入需要拼接到S后面的字符串(小于或等于100的字符串)：\n");
			scanf("%s", ch3);
			if (InitString(&str3, ch3)) {
				printf("初始化字符串S3成功！\n");
			}
			if (concatString(&str1, &str3)) {
				printf("字符串拼接成功！\n");
			}
			else {
				printf("请重新尝试！\n");
			}
			break;
		}
		case 6: {
			int a, b;
			char *ch4;
			printf("例如：S为“friend”,输入pos为4，长度len为3，则得到输出为“end”\n");
			printf("请输入pos的值：");
			scanf("%d", &a);
			printf("请输入len的值：");
			scanf("%d", &b);
			ch4 = getSubString(&str1, a, b);
			if (InitString(&str4, ch4)) {
				printf("返回的子串为：");
				traverseString(&str4);
			}
			break;
		}
		case 7: {
			char ch5[100];
			int a, b;
			printf("请输入需要查找的子串(小于或等于100的字符串)：\n");
			scanf("%s", ch5);
			printf("请输入pos的值：");
			scanf("%d", &a);
			b = locateSubString(&str1, ch5, a);
			switch (b)
			{
			case 0: {
				printf("请重新尝试！\n");
				break;
			}
			case -1: {
				printf("未查找到符和条件的子串!\n");
				break;
			}
			default:
				printf("该子串的位置为：%d", b);
				break;
			}
			break;
		}
		case 8: {
			char ch6[100];
			int a;
			printf("请输入需要插入的字符串(小于或等于100的字符串)：\n");
			printf("请输入pos的值：");
			scanf("%d", &a);
			if (stringInsert(&str1, a, ch6)) {
				printf("字符串插入成功！\n");
			}
			else {
				printf("请重新再试！\n");
			}
			break;
		}
		case 9: {
			int a, b;
			printf("请输入pos的值：");
			scanf("%d", &a);
			printf("请输入len的值：");
			scanf("%d", &b);
			if (stringDelete(&str1, a-1, b)) {
				printf("删除成功！\n");
			}
			else {
				printf("请重新再试！\n");
			}
			break;
		}
		case 10: {
			char newStr[100], oldStr[100];
			printf("请输入newString：");
			scanf("%s", newStr);
			printf("请输入需要替换的oldString：");
			scanf("%s", oldStr);
			replaceString(&str1, oldStr, newStr);
			printf("替换成功！\n");
			break;
		}
		case 11: {
			clearString(&str1);
			printf("字符串S1清空成功！\n");
			break;
		}
		case 12: {
			if (destoryString(&str1)) {
				printf("销毁字符串S1成功！\n");
			}
			if (destoryString(&str2)) {
				printf("销毁字符串S2成功！\n");
			}
			if (destoryString(&str3)) {
				printf("销毁字符串S3成功！\n");
			}
			if (destoryString(&str4)) {
				printf("销毁字符串S4成功！\n");
			}
			break;
		}
		case 13: {
			printf("遍历字符串：");
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
			printf("程序退出！！\n");
			k = 0;
			break;
		}
		default: {
			printf("请在0-13之间选择！\n");
			break;
		}
		}
	}
	system("pause");
	return 0;
}