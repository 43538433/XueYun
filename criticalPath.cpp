#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;                //顶点类型应由用户定义
typedef int EdgeType;                  //边上的权值类型应由用户定义
typedef int QElemType;                 //*ElemType类型根据实际情况而定，这里假设为int *
typedef int Status;
#define OK 1
#define ERROR 0

#define MAXVEX 100                     //最大顶点数，应由用户定义
#define INFINITY 65535                 //用65535来代表无穷大，当有权值时，用无穷表示两个顶点没有边，而不是0

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

//声明全局变量
int *etv, *ltv;             //事件最早发生时间和最迟发生时间数组
int *stack2;                //用于存储拓扑排序的栈
int top2;                   //用于stack2的指针

typedef struct EdgeNode {   //边表结点
	int adjvex;             //邻接点域，存储该顶点对应得下标
	EdgeType weight;        //用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;  //链接，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode { //顶点表结点
	int in;                 //拓扑排序，用于存储顶点的入度
	VertexType data;        //顶点域，存储顶点信息
	EdgeNode *firstedge;    //边表头指针
}VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;            //顶点表结点
	int numVertexes, numEdges;  //图中当前顶点数和边数
}GraphAdjList;

void CreateGraph(GraphAdjList *g) {
	int i, j, k, w;
	EdgeNode *e;
	printf("Please enter the number of vertexes:");
	scanf("%d", &g->numVertexes);
	printf("Please enter the number of edges:");
	scanf("%d", &g->numEdges);             //读入顶点的信息，建立顶点表
	for (i = 0; i < g->numVertexes; i++) {
		printf("Please enter the value of vertexes[%d]:", i);
		getchar();
		scanf("%d", &g->adjList[i].data);  //输入顶点信息
		g->adjList[i].firstedge = NULL;    //将边表置为空表
	}
	for (i = 0; i < g->numVertexes; i++) { //初始化所有顶点的in（入度域）
		g->adjList[i].in = 0;
	}
	printf("\n");
	printf("For example：edge(Vi,Vj),i=1,j=2,wight:3;the right enter is:1,2,3\n");
	for (k = 0; k < g->numEdges; k++) {
		printf("Please enter the value of edge[%d]:", k);
		scanf("%d,%d,%d", &i, &j, &w);

		//顶点j的入度加一
		g->adjList[j].in++;

		//单链表的头插法
		e = (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间，生成边表结点
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = j;                          //邻接序号为j
		e->weight = w;
		e->next = g->adjList[i].firstedge;      //将e指针指向当前顶点指向得结点
		g->adjList[i].firstedge = e;            //将当前顶点得指针指向e

		//如果是无向图就需要下面的这一段代码，因为无向图是对称的
		/*e = (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间，生成边表结点
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = i;                          //邻接序号为i
		e->next = g->adjList[j].firstedge;      //将e指针指向当前顶点指向得结点
		g->adjList[j].firstedge = e;            //将当前顶点得指针指向e*/
	}
}

void showGraph(GraphAdjList g) {
	int i = 0;
	printf("\n");
	printf("Vertexes:%d    Edges:%d\n", g.numVertexes, g.numEdges);
	printf("The adjacency list is as follows:\n");

	//如果是无向图下面改为while(g.adjList[i].firstedge != NULL && i < g.numVertexes)
	//现在表示的是有向图，结点的入度可能为零，所以不需判断边表是否为空
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

//优化拓扑排序，用于关键路径计算
Status TopologicalSort(GraphAdjList g) {
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;                  //用于栈顶指针下标
	int count = 0;                //用于统计输出顶点的个数
	int *stack;                   //建栈将入度为0的顶点入栈
	stack = (int *)malloc(g.numVertexes * sizeof(int));
	for (i = 0; i < g.numVertexes; i++) {
		if (g.adjList[i].in == 0) {
			stack[++top] = i;     //stack从1开始，而不是0
		}
	}
	top2 = 0;
	etv = (int *)malloc(g.numVertexes * sizeof(int));    //事件最早发生的时间
	for (i = 0; i < g.numVertexes; i++) {
		etv[i] = 0;               //初始化为0
	}
	stack2 = (int *)malloc(g.numVertexes * sizeof(int)); //初始化
	while (top != 0) {
		gettop = stack[top--];
		printf("%d ", g.adjList[gettop].data);
		count++;
		stack2[++top2] = gettop;  //将弹出的顶点序号压入拓扑序列的栈
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//对此顶点弧表遍历
			k = e->adjvex;
			if (!(--g.adjList[k].in)) {  //将k号顶点邻接点的入度减1
				stack[++top] = k;
			}
			if ((etv[gettop] + e->weight) > etv[k]) {    //求各顶点事件最早发生时间值
				etv[k] = etv[gettop] + e->weight;
			}
		}
		if (count < g.numVertexes) {
			printf("->");
		}
	}
	if (count < g.numVertexes) {  //如果count小于顶点数，说明存在环
		return ERROR;
	}
	else {
		return OK;
	}
}

//求关键路径，g为有向网，输出g的各项关键活动
void CriticalPath(GraphAdjList g) {
	EdgeNode *e;
	int i, gettop, k, j;
	int ete, lte;         //声明活动最早发生时间和最迟发生时间变量
	if (TopologicalSort(g)) {
		printf("\n该图不存在回路，拓扑排序成功！!\n");
	}
	else {
		printf("\n该图存在回路，拓扑排序不成功！！\n");
		return;
	}
	ltv = (int*)malloc(g.numVertexes * sizeof(int));//事件最晚发生时间
	for (i = 0; i < g.numVertexes; i++) {
		ltv[i] = etv[g.numVertexes - 1];            //初始化ltv
	}
	printf("\n关键路径如下：\n");
	while (top2 != 0) {
		gettop = stack2[top2--];                    //将拓扑序列出栈，后进先出
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//求各顶点事件的最迟发生时间ltv值
			k = e->adjvex;
			if (ltv[k] - e->weight < ltv[gettop]) { //求各顶点事件最晚发生时间ltv
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
				printf("<V%d，V%d>  length:%d\n", g.adjList[j].data, g.adjList[k].data, e->weight);
			}
		}
	}
}

int main() {
	GraphAdjList g;
	CreateGraph(&g);
	showGraph(g);
	printf("\n");
	printf("拓扑排序:\n");
	CriticalPath(g);
	system("pause");
	return 0;
}