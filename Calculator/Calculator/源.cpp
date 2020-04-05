//����������ʽ
//����Դ�ڣ�https://blog.csdn.net/sijunzhang/article/details/75913583
#include"iostream"   
#include"cstdio"
#include"cmath"
#include"cstring"
#include"algorithm"
#include"stack"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996);

#define maxnum 100
using namespace std;
int flag;
char a[maxnum], b[maxnum], d[maxnum], e[maxnum];
double c[maxnum];
stack<char> p1;
stack<double> p2;

//�ж�һ���ַ��Ƿ�Ϊ���ֺ�С����
int pd(char ch)
{
	if ((ch >= '0'&&ch <= '9') || ch == '.')
		return 1;
	return 0;
}

// �жϲ����������ȼ�
int priority(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}

//��׺���׺
void zh(char a[], char b[])  //a���������׺��b��ź�׺
{
	int n, i, j;
	j = 0;
	for (i = 0; a[i] != 0; i++)
	{
		if (pd(a[i]))      //���a[i]Ϊ���ֻ�С���㣬��a[i]����b[i]
		{
			b[j] = a[i];
			j++;
		}
		else
		{
			if (p1.empty())    //���pl������������Ƿ�Ϊ�գ���Ϊtrue,��֮Ϊfalse
				p1.push(a[i]);
			else
			{
				if (a[i] == ')')       //������������ţ���ջ��Ԫ�����ε�����ֱ�����������ţ������Ų������
				{
					while (p1.top() != '(')
					{
						b[j] = p1.top();
						j++;
						p1.pop();
					}
					p1.pop();
				}
				else if (a[i] == '(' || priority(a[i]) > priority(p1.top()))      //����������Ż����ȼ�����ԭ��ջ����Ԫ�أ�ֱ����ջ
					p1.push(a[i]);
				else
				{
					while (!p1.empty() && p1.top() != '('&&priority(a[i]) <= priority(p1.top()))   //������������ţ������ȼ�С��ջ��Ԫ�أ�ջ��Ԫ�س�ջ�������Ƚϣ�
					{
						b[j] = p1.top();                                                           //ֱ�����ȼ���ջ������ջ
						j++;
						p1.pop();
					}
					p1.push(a[i]);
				}
			}
		}
	}
	while (!p1.empty())
	{
		b[j] = p1.top();
		j++;
		p1.pop();
	}
}

//������ʽ�����Ĵ�С�Լ�λ��
int fenjie(char a[])
{
	int i, j = 0, k = 0, t, n = 0;
	char num[10];
	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] == '(' || a[i] == ')')
			continue;
		if (pd(a[i]))
		{
			num[j] = a[i];
			if (a[i] == '.')
				n = j;
			j++;
		}
		else
		{
			if (n == 0)
			{
				for (t = 0; t < j; t++)
					c[k] = c[k] + (num[t] - '0')*pow(10, j - t - 1);
			}
			else
			{
				for (t = 0; t < n; t++)
					c[k] = c[k] + (num[t] - '0')*pow(10, n - t - 1);
				for (t = n + 1; t < j; t++)
					c[k] = c[k] + (num[t] - '0')*pow(10, n - t);
			}
			d[k] = j;
			j = 0;
			k++;
			n = 0;
			memset(num, 0, sizeof(num));
		}
	}
	if (n == 0)
	{
		for (t = 0; t < j; t++)
			c[k] = c[k] + (num[t] - '0')*pow(10, j - t - 1);
	}
	else
	{
		for (t = 0; t < n; t++)
			c[k] = c[k] + (num[t] - '0')*pow(10, n - t - 1);
		for (t = n + 1; t < j; t++)
			c[k] = c[k] + (num[t] - '0')*pow(10, n - t);
	}
	d[k] = j;
	j = 0;
	k++;
	n = 0;
	memset(num, 0, sizeof(num));
	return k;
}

//�ɺ�׺���ʽ������
double jg(char b[])
{
	int i, j = 0;
	double x, y, z;
	for (i = 0; b[i] != 0 && flag; i++)
	{
		if (pd(b[i]))
		{
			p2.push(c[j]);
			i = i + d[j] - 1;
			j++;
		}
		else
		{
			y = p2.top();
			p2.pop();
			x = p2.top();
			p2.pop();
			switch (b[i])
			{
			case '+':
				z = x + y;
				break;
			case '-':
				z = x - y;
				break;
			case '*':
				z = x * y;
				break;
			case '/':
				if (y == 0)
					flag = 0;
				else
					z = x / y;
				break;
			}
			p2.push(z);
		}
	}
	z = p2.top();
	while (!p2.empty())
		p2.pop();
	return z;
}

void print(double z)
{
	int x;
	z = z * 100;
	x = z;
	if (x % 10 == 0 && x / 10 % 10 == 0)
		printf("=%.0lf\n\n", z / 100);
	else
		printf("=%.2lf\n\n", z / 100);
}

int is_priority(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '.')
		return 1;
	else
		return 0;
}

int is_error(char a[])
{
	int i, n = 0;
	memset(e, 0, sizeof(e));
	if (is_priority(a[0]) || a[0] == ')')    //��һ���ַ�Ϊ���ţ�����
		return 1;
	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] != '('&&a[i] != ')')       
			e[i] = a[i];
	}
	if (is_priority(a[i - 1]))              //���һ���ַ�Ϊ���ţ�����
		return 1;
	for (i = 0; e[i] != 0; i++)
	{
		if (is_priority(e[i]) && is_priority(e[i + 1]))    //��һ�������һ���ַ�����Ϊ����
			return 1;
	}
	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] == '(' && ((is_priority(a[i + 1])) || a[i - 1] == '.'))
		{
			return 1;
		}
		if (a[i] == ')' && ((is_priority(a[i - 1])) || a[i + 1] == '.'))
		{
			return 1;
		}
	}
	for (i = 0; a[i] != 0; i++)
	{
		if (a[i] == '(')
			n++;
		else if (a[i] == ')')
			n--;
		if (n < 0)
			return 1;

	}
	if (n != 0)
		return 1;
	return 0;
}

int main()
{
	int i, j, k;
	double z;
	while (1)
	{
		memset(a, 0, sizeof(a));     //��a�������ֽڻ����ַ���0��,�ַ����ĳ�ʼ��
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		memset(d, 0, sizeof(d));
		flag = 1;
		printf("��������Ҫ����ı��ʽ��\n");
		scanf("%s", a);
		getchar();
		if (is_error(a))            //�ж�����ı��ʽ�Ƿ���Ϲ���
		{
			printf("���ʽ�����Ϲ���!����������\n\n");     
			continue;
		}
		k = fenjie(a);
		zh(a, b);
		printf("-------------------------------------\n");
		printf("���׺���ʽΪ��\n");
		for(i=0;b[i]!=0;i++)
			printf("%c",b[i]);
		printf("\n");              //������׺���ʽ
		z = jg(b);
		if (flag)
		{
			printf("���ʽ�Ľ��Ϊ��\n");
			printf("%s", a);
			print(z);
			printf("-------------------------------------\n");
		}
		else
			printf("���ʽ�����Ϲ���!����������\n\n");
	}
	return 0;
}