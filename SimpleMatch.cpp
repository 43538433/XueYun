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

//返回子串strSub在主串strMain中第pos个字符后的位置，若不存在，则函数返回0
int Index(char *strMain, char *strSub, int pos) {
	int i = pos;  //i用于主串strMain中当前位置下标值
	int j = 1;    //j用于子串strSub 中当前位置下标值
	int lenMain = getCharLength(strMain); //主串长度
	int lenSub = getCharLength(strSub);   //子串长度
	while (i <= lenMain && j <= lenSub) {
		if (strMain[i] == strSub[j-1]) {  //两个字符相等继续向后比较
			++i;
			++j;
		}
		else {                //指针后退重新开始匹配
			i = i - j + 2;    //i回溯到上一次匹配首位的下一个
			j = 1;            //j退回到子串T的首位
		}
	}
	if (j > lenSub) {         //j大于子串的长度，说明主串中找到与子串完全匹配的字符串
		return i - lenSub + 1;//返回该字符串的首个字符在主串中的位置，加1是因为C中字符串是从0开始的，而习惯上是从1开始的，为了更直观地让操作者理解
	}
	else {                    //反之，没有找到匹配的字符串，返回0
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