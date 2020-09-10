#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;                //顶点类型应由用户定义
typedef int EdgeType;                  //边上的权值类型应由用户定义
typedef int QElemType;                 //*ElemType类型根据实际情况而定，这里假设为int *
typedef int Status;
#define OK 1
#define ERROR 0
#define OVER -1

#define MAXVEX 100                     //最大顶点数，应由用户定义
#define INFINITY 65535                 //用65535来代表无穷大，当有权值时，用无穷表示两个顶点没有边，而不是0
									   //以下代码没有用到，主要只考虑不带权值的情况#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

//队列的链式存储结构
typedef struct QNode {
	QElemType data;   //数据域
	struct QNode *next;  //结构域
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;  //队头指针
	QueuePtr rear;   //队尾指针
}LinkQueue;


typedef struct EdgeNode {   //边表结点
	int adjvex;             //邻接点域，存储该顶点对应得下标
	//EdgeType weight;      //用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;  //链接，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode { //顶点表结点
	int in;                 //拓扑排序，用于存储顶点的入度
	VertexType data;        //顶点域，存储顶点信息
	EdgeNode *firstedge;    //边表头指针
}VertexNode,AdjList[MAXVEX];

typedef struct {
	AdjList adjList;            //顶点表结点
	int numVertexes, numEdges;  //图中当前顶点数和边数
}GraphAdjList;

typedef int Boolean;    //Boolean是布尔类型，其值是TRUE或FALSE
Boolean visited[MAXVEX];//访问标志的数组
#define TRUE 1;
#define FALSE 0;

//初始化一个空的队列
Status InitQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) {
		printf("initialization failed!!");
		exit(OVER);  //存储分配失败
	}
	Q->front->next = NULL;
	return OK;
}

//销毁队列
Status DestroyQueue(LinkQueue *Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);    //从队头取出每一个元素并释放内存，Q->rear作为一个临时指针使用
		Q->front = Q->rear;
	}
	return OK;
}

//队列判空
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear) {
		return OK;
	}
	return ERROR;
}

//队尾插入元素
Status EnterQueue(LinkQueue *Q, QElemType e) {
	QNode *p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) {
		return ERROR;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;  //当前队尾指针的next指向新元素
	Q->rear = p;        //修改尾指针
	return OK;
}

//删除队头元素，并返回该元素
Status DeleteQueue(LinkQueue *Q, QElemType &e) {
	if (Q->front == Q->rear) {
		return ERROR;
	}
	QNode *p = Q->front->next;  //front是指向头结点的，头结点不存储数据，front的next是队头结点，即p成为队头结点
	e = p->data;                //获取队头数据
	Q->front->next = p->next;   //Q->front->next是指头结点的next指针去连接p的下一个结点，就是把头结点p隔离出去了
	if (Q->rear == p) {         //如果该队列恰巧只有一个元素，删除之后队列就为空了，所以front=near
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

//邻接表的深度优先递归算法
void DFS(GraphAdjList g, int i) {
	EdgeNode *p;
	visited[i] = TRUE;
	printf("%d ", g.adjList[i].data);  //打印顶点，也可以其他操作
	p = g.adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex])
			DFS(g, p->adjvex);        //对访问的邻接顶点递归调用
		p = p->next;
	}
}

//邻接表的深度遍历操作
void DFSTraverse(GraphAdjList g) {
	int i;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;           //初始所有顶点状态都是未访问过的状态
	}
	for (i = 0; i < g.numVertexes; i++) {
		if (!visited[i]) {            //对未访问过的顶点调用DFS，若是连通图，只会执行一次
			DFS(g, i);
		}
	}
}

//邻接表的广度遍历算法
void BFSTraverse(GraphAdjList g) {
	int i;
	EdgeNode *p;
	LinkQueue Q;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;
	}
	InitQueue(&Q);
	for (i = 0; i < g.numVertexes; i++) {
		printf("%d#", visited[i]);
	}
	printf("\n");

	printf("numVertexes:%d\n", g.numVertexes);

	for (i = 0; i < g.numVertexes; i++) {
		printf("%d\n", i);
		printf("visited[%d]:%d\n", i, visited[i]);
		if (!visited[i]) {
			visited[i] = TRUE;
			printf("%d ", g.adjList[i].data);      //打印顶点，也可以是其他操作
			EnterQueue(&Q, i);
			while (!EmptyQueue(&Q)) {
				DeleteQueue(&Q, i);
				p = g.adjList[i].firstedge;        //找到当前顶点边表链表头指针
				while (p) {
					if (!visited[p->adjvex]) {     //若此顶点未被访问
						visited[p->adjvex] = TRUE;
						printf("%d ", g.adjList[p->adjvex].data);
						EnterQueue(&Q, p->adjvex); //将此顶点入队
					}
					p = p->next;                   //指针指向下一个邻接点
				}
			}
		}
		printf("\n");
		printf("i:%d\n", i);
	}
	printf("\n");
	for (i = 0; i < g.numVertexes; i++) {
		printf("%d#", visited[i]);
	}
	printf("\n");
	DestroyQueue(&Q);
}

//拓扑排序，若图无回路，则输出拓扑排序序列并返回OK，若有回路返回ERROR
Status TopologicalSort(GraphAdjList g) {
	EdgeNode *e;
	int temp;
	int i, k, gettop;
	int top = 0;     //用于栈指针下标
	int count = 0;   //用于统计输出顶点的个数
	int *stack;      //建栈，存储入度为0的顶点
	stack = (int*)malloc(g.numVertexes * sizeof(int));
	for (i = 0; i < g.numVertexes; i++) {
		if (g.adjList[i].in == 0) {
			stack[++top] = i;   //将入度为0的顶点入栈
		}
	}
	while (top != 0) {
		gettop = stack[top--];  //出栈
		printf("%d ", g.adjList[gettop].data);
		count++;                //统计输出顶点数
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//对此顶点弧表遍历
			k = e->adjvex;
			if (!(--g.adjList[k].in)) {  //将k号顶点邻接点的入度减1
				stack[++top] = k;
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

void CreateGraph(GraphAdjList *g) {
	int i, j, k;
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
	printf("For example：edge(Vi,Vj),i=1,j=2,the right enter is:1,2.That means vertex 1 points to vertex 2.\n");
	for (k = 0; k < g->numEdges; k++) {
		printf("Please enter the value of edge[%d]:", k);
		scanf("%d,%d", &i, &j);

		//顶点j的入度加一
		g->adjList[j].in++;

		//单链表的头插法
		e = (EdgeNode*)malloc(sizeof(EdgeNode));//向内存申请空间，生成边表结点
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = j;                          //邻接序号为j
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
		printf("vertexes[%d]:%d", i,g.adjList[i].data);
		EdgeNode *e = NULL;
		e = g.adjList[i].firstedge;
		while (e != NULL) {
			printf("-->");
			printf("%d", e->adjvex);
			e = e->next;
		}
		printf("\n");
		i++;
	}
}

int main() {
	GraphAdjList g;
	CreateGraph(&g);
	showGraph(g);
	printf("\n");
	printf("深度优先遍历:\n");
	DFSTraverse(g);
	printf("\n");
	printf("--------------------------\n");
	printf("广度优先遍历:\n");
	BFSTraverse(g);
	printf("\n");
	printf("--------------------------\n");
	printf("拓扑排序:\n");
	if (TopologicalSort(g)) {
		printf("\n该图不存在回路，拓扑排序成功！!\n");
	}
	else {
		printf("\n该图存在回路，拓扑排序不成功！！\n");
	}
	system("pause");
	return 0;
}