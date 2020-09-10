#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;                //��������Ӧ���û�����
typedef int EdgeType;                  //���ϵ�Ȩֵ����Ӧ���û�����
typedef int QElemType;                 //*ElemType���͸���ʵ������������������Ϊint *
typedef int Status;
#define OK 1
#define ERROR 0

#define MAXVEX 100                     //��󶥵�����Ӧ���û�����
#define INFINITY 65535                 //��65535����������󣬵���Ȩֵʱ���������ʾ��������û�бߣ�������0

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

//����ȫ�ֱ���
int *etv, *ltv;             //�¼����緢��ʱ�����ٷ���ʱ������
int *stack2;                //���ڴ洢���������ջ
int top2;                   //����stack2��ָ��

typedef struct EdgeNode {   //�߱���
	int adjvex;             //�ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeType weight;        //���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode *next;  //���ӣ�ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode { //�������
	int in;                 //�����������ڴ洢��������
	VertexType data;        //�����򣬴洢������Ϣ
	EdgeNode *firstedge;    //�߱�ͷָ��
}VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;            //�������
	int numVertexes, numEdges;  //ͼ�е�ǰ�������ͱ���
}GraphAdjList;

void CreateGraph(GraphAdjList *g) {
	int i, j, k, w;
	EdgeNode *e;
	printf("Please enter the number of vertexes:");
	scanf("%d", &g->numVertexes);
	printf("Please enter the number of edges:");
	scanf("%d", &g->numEdges);             //���붥�����Ϣ�����������
	for (i = 0; i < g->numVertexes; i++) {
		printf("Please enter the value of vertexes[%d]:", i);
		getchar();
		scanf("%d", &g->adjList[i].data);  //���붥����Ϣ
		g->adjList[i].firstedge = NULL;    //���߱���Ϊ�ձ�
	}
	for (i = 0; i < g->numVertexes; i++) { //��ʼ�����ж����in�������
		g->adjList[i].in = 0;
	}
	printf("\n");
	printf("For example��edge(Vi,Vj),i=1,j=2,wight:3;the right enter is:1,2,3\n");
	for (k = 0; k < g->numEdges; k++) {
		printf("Please enter the value of edge[%d]:", k);
		scanf("%d,%d,%d", &i, &j, &w);

		//����j����ȼ�һ
		g->adjList[j].in++;

		//�������ͷ�巨
		e = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ䣬���ɱ߱���
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = j;                          //�ڽ����Ϊj
		e->weight = w;
		e->next = g->adjList[i].firstedge;      //��eָ��ָ��ǰ����ָ��ý��
		g->adjList[i].firstedge = e;            //����ǰ�����ָ��ָ��e

		//���������ͼ����Ҫ�������һ�δ��룬��Ϊ����ͼ�ǶԳƵ�
		/*e = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ䣬���ɱ߱���
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = i;                          //�ڽ����Ϊi
		e->next = g->adjList[j].firstedge;      //��eָ��ָ��ǰ����ָ��ý��
		g->adjList[j].firstedge = e;            //����ǰ�����ָ��ָ��e*/
	}
}

void showGraph(GraphAdjList g) {
	int i = 0;
	printf("\n");
	printf("Vertexes:%d    Edges:%d\n", g.numVertexes, g.numEdges);
	printf("The adjacency list is as follows:\n");

	//���������ͼ�����Ϊwhile(g.adjList[i].firstedge != NULL && i < g.numVertexes)
	//���ڱ�ʾ��������ͼ��������ȿ���Ϊ�㣬���Բ����жϱ߱��Ƿ�Ϊ��
	while (i < g.numVertexes) {
		printf("vertexes[%d]:%d", i, g.adjList[i].data);
		EdgeNode *e = NULL;
		e = g.adjList[i].firstedge;
		while (e != NULL) {
			printf("-->");
			printf("%d(weight:%d)", e->adjvex,e->weight);
			e = e->next;
		}
		printf("\n");
		i++;
	}
}

//�Ż������������ڹؼ�·������
Status TopologicalSort(GraphAdjList g) {
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;                  //����ջ��ָ���±�
	int count = 0;                //����ͳ���������ĸ���
	int *stack;                   //��ջ�����Ϊ0�Ķ�����ջ
	stack = (int *)malloc(g.numVertexes * sizeof(int));
	for (i = 0; i < g.numVertexes; i++) {
		if (g.adjList[i].in == 0) {
			stack[++top] = i;     //stack��1��ʼ��������0
		}
	}
	top2 = 0;
	etv = (int *)malloc(g.numVertexes * sizeof(int));    //�¼����緢����ʱ��
	for (i = 0; i < g.numVertexes; i++) {
		etv[i] = 0;               //��ʼ��Ϊ0
	}
	stack2 = (int *)malloc(g.numVertexes * sizeof(int)); //��ʼ��
	while (top != 0) {
		gettop = stack[top--];
		printf("%d ", g.adjList[gettop].data);
		count++;
		stack2[++top2] = gettop;  //�������Ķ������ѹ���������е�ջ
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//�Դ˶��㻡�����
			k = e->adjvex;
			if (!(--g.adjList[k].in)) {  //��k�Ŷ����ڽӵ����ȼ�1
				stack[++top] = k;
			}
			if ((etv[gettop] + e->weight) > etv[k]) {    //��������¼����緢��ʱ��ֵ
				etv[k] = etv[gettop] + e->weight;
			}
		}
		if (count < g.numVertexes) {
			printf("->");
		}
	}
	if (count < g.numVertexes) {  //���countС�ڶ�������˵�����ڻ�
		return ERROR;
	}
	else {
		return OK;
	}
}

//��ؼ�·����gΪ�����������g�ĸ���ؼ��
void CriticalPath(GraphAdjList g) {
	EdgeNode *e;
	int i, gettop, k, j;
	int ete, lte;         //��������緢��ʱ�����ٷ���ʱ�����
	if (TopologicalSort(g)) {
		printf("\n��ͼ�����ڻ�·����������ɹ���!\n");
	}
	else {
		printf("\n��ͼ���ڻ�·���������򲻳ɹ�����\n");
		return;
	}
	ltv = (int*)malloc(g.numVertexes * sizeof(int));//�¼�������ʱ��
	for (i = 0; i < g.numVertexes; i++) {
		ltv[i] = etv[g.numVertexes - 1];            //��ʼ��ltv
	}
	printf("\n�ؼ�·�����£�\n");
	while (top2 != 0) {
		gettop = stack2[top2--];                    //���������г�ջ������ȳ�
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//��������¼�����ٷ���ʱ��ltvֵ
			k = e->adjvex;
			if (ltv[k] - e->weight < ltv[gettop]) { //��������¼�������ʱ��ltv
				ltv[gettop] = ltv[k] - e->weight;
			}
		}
	}
	for (j = 0; j < g.numVertexes; j++) {
		for (e = g.adjList[j].firstedge; e; e = e->next) {
			k = e->adjvex;
			ete = etv[j];
			lte = ltv[k] - e->weight;
			if (ete == lte) {
				printf("<V%d��V%d>  length:%d\n", g.adjList[j].data, g.adjList[k].data, e->weight);
			}
		}
	}
}

int main() {
	GraphAdjList g;
	CreateGraph(&g);
	showGraph(g);
	printf("\n");
	printf("��������:\n");
	CriticalPath(g);
	system("pause");
	return 0;
}