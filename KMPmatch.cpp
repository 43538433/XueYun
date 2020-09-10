#include<stdio.h>
#include<stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

//获取某个字符串的长度
int getCharLength(char *string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

// 通过计算返回子串T的next数组
void get_next(char *strSub, int *next) {
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;
	int lenSub = getCharLength(strSub);
	while (i < lenSub) {
		if (j == 0 || strSub[i] == strSub[j]) { //strSub[i]表示后缀的单个字符，strSub[j]表示前缀的单个字符
			i++;
			j++;
			next[i] = j;
		}
		else {
			j = next[j];    //若字符不相同，则j值回溯
		}
	}
}

/*
求模式串T的next函数修正值并存入数组nextval，next数组的升级
使用时，只需把Index_KMP中的get_next(strSub, next); 改为get_nextval(strSub, next); 即可
*/
void get_nextval(char *strSub, int *nextval) {
	int i, j;
	i = 1;
	j = 0;
	nextval[1] = 0;
	int lenSub = getCharLength(strSub);
	while (i < lenSub) {
		if (j == 0 || strSub[i] == strSub[j]) { //strSub[i]表示后缀的单个字符，strSub[j]表示前缀的单个字符
			i++;
			j++;
			if (strSub[i] != strSub[j]) {       //若当前字符与前缀字符不同
				nextval[i] = j;                 //则当前的j为nextval在i位置的值
			}
			else {
				nextval[i] = nextval[j];        //如果与前缀字符相等，则将前缀字符的nextval值赋值给nextval[i]
			}
		}
		else {
			j = nextval[j];                     //若字符不相同，则j值回溯
		}
	}
}

//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0
int Index_KMP(char *strMain, char *strSub, int pos) {
	int i = pos;   //i用于主串strMain中当前位置下标值
	int j = 1;     //j用于子串strSub 中当前位置下标值
	int lenMain = getCharLength(strMain);  //主串长度
	int lenSub = getCharLength(strSub);    //子串长度
	int next[100];                 //定义一个next数组
	get_next(strSub, next);        //分析得到next数组
	while (i <= lenMain && j <= lenSub) {
		if (j == 0 || strMain[i] == strSub[j - 1]) {
			i++;
			j++;
		}
		else {
			j = next[j];   //指针后退重新开始匹配，j退回合适的位置，i值不变
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