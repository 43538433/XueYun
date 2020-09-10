#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;               //顶点类型应由用户定义
typedef int EdgeType;                  //边上的权值类型应由用户定义
typedef int QElemType;                 //*ElemType类型根据实际情况而定，这里假设为int *
typedef int Status;

#define OK 1
#define ERROR 0
#define OVER -1

#define MAXVEX 100                     //最大顶点数，应由用户定义
#define INFINITY 65535                 //用65535来代表无穷大，当有权值时，用无穷表示两个顶点没有边，而不是0
                                       //以下代码没有用到，主要只考虑不带权值的情况
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)


//Dijkstra算法求最短路径
typedef int Pathmatirx[MAXVEX];        //用于存储最短路径下标的数组
//例如P={0,0,1,1,2,2,0,0,0,}表示所求源点到V4、V5点的最短路径它们的前驱均是V2
typedef int ShortPathTable[MAXVEX];    //用于存储到各点最短路径的权值和

//Froyd算法求最短路径
typedef int Pathmatirx02[MAXVEX][MAXVEX];
typedef int ShortPathTable02[MAXVEX][MAXVEX];

//Kruskal算法，对边集数组Edge结构的定义
typedef struct Edge {
	int begin;
	int end;
	int weight;
}Edge;

//队列的链式存储结构
typedef struct QNode {
	QElemType data;   //数据域
	struct QNode *next;  //结构域
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;  //队头指针
	QueuePtr rear;   //队尾指针
}LinkQueue;


typedef struct
{
	VertexType vexs[MAXVEX];            //顶点表
	EdgeType   arc[MAXVEX][MAXVEX];     //邻接矩阵，可看作边表
	int numVertexes, numEdges;          //图中当前的顶点数和边数
}Graph;

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

//邻接矩阵的深度优先递归算法
void DFS(Graph g, int i) {
	int j;
	visited[i] = TRUE;
	printf("%c ", g.vexs[i]);  //打印顶点，也可以其他操作
	for (j = 0; j < g.numVertexes; j++) {
		if (g.arc[i][j] == 1 && !visited) { //如果某顶点与第i个顶点有边且还未被访问到，就进行递归
			DFS(g, j);       //对未访问的邻接顶点递归调用
		}
	}
}

//邻接矩阵的深度遍历操作
void DFSTraverse(Graph g) {
	int i;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;  //初始所有顶点状态都是未访问过的状态
	}
	for (i = 0; i < g.numVertexes; i++) {
		if (!visited[i]) {   //对未访问过的顶点调用DFS，若是连通图，只会执行一次
			DFS(g, i);
		}
	}
}

//邻接矩阵的广度优先遍历算法
void BFSTraverse(Graph g) {
	int i, j;
	LinkQueue Q;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;
	}
	InitQueue(&Q);                       //初始化一辅助用的队列
	for (i = 0; i < g.numVertexes; i++) {//对每一个顶点做循环
		if (!visited[i]) {               //若是未访问过，就进行处理
			visited[i] = TRUE;           //将顶点标记为已访问过
			printf("%c ", g.vexs[i]);    //打印顶点，也可以是其他操作
			EnterQueue(&Q, i);           //将此顶点入队列
			while (!EmptyQueue(&Q)) {
				DeleteQueue(&Q, i);      //将队列中元素出队列，赋值给i
				for (j = 0; j < g.numVertexes; j++) {
					//判断其他顶点若与当前顶点存在边且未访问过
					if (g.arc[i][j] != INFINITY && !visited[j]) {
						visited[j] = TRUE;//将找到的此项顶点标记为已访问
						printf("%c ", g.vexs[j]);//打印顶点
						EnterQueue(&Q, j);//将找到的此顶点入队列
					}
				}
			}
		}
	}
	DestroyQueue(&Q);
}

//Prim算法生成最小生成树
void MinSpanTree_Prim(Graph g) {
	int min, i, j, k;
	int adjvex[MAXVEX];  //保存相关顶点下标，该边/弧指向的顶点的位置
	int lowcost[MAXVEX]; //保存相关顶点间边的权值
	lowcost[0] = 0;      //初始化第一个权值为0，即V0加入生成树。lowcost的值为0，在这里就是此下标的顶点已经加入生成树
	adjvex[0] = 0;       //初始化第一个顶点下标为0
	for (i = 1; i < g.numVertexes; i++) { //循环除下标为0外的全部顶点
		lowcost[i] = g.arc[0][i];         //将V0顶点与之有边的权值存入数组
		adjvex[i] = 0;                    //初始化都为V0的下标
	}
	for (i = 1; i < g.numVertexes; i++) {
		min = INFINITY;                   //初始化最小权值为∞
		j = 1;
		k = 0;
		while (j < g.numVertexes) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];         //则让当前权值成为最小值
				k = j;                    //将当前最小值的下标存入k
			}
			j++;
		}
		printf("V%d----V%d=%d\n", adjvex[k], k, min);//打印当前顶点边中权值最小边
		lowcost[k] = 0;                   //将当前顶点的权值设置为0，表示此顶点已完成任务
		for (j = 1; j < g.numVertexes; j++) {//循环所有顶点
			if (lowcost[j] != 0 && g.arc[k][j] < lowcost[j]) {
				//若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
				lowcost[j] = g.arc[k][j]; //将较小权值存入lowcost
				adjvex[j] = k;            //将下标为k的顶点存入adjvex
			}
		}
	}
}
int maxNum(int i, int j) {
	if (i > j) {
		return i;
	}
	else {
		return j;
	}
}

int minNum(int i, int j) {
	if (i < j) {
		return i;
	}
	else {
		return j;
	}
}

//查找连线顶点的尾部下标
int Find(int *parent, int f) {
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

//Kruskal算法生成最小生成树
void MinSpanTree_Kruskal(Graph g) {
	int i, j, n, m;
	int k, r;
	r = 0;
	k = 0;
	Edge temp;
	Edge edges[MAXVEX];   //定义边集数组
	int parent[MAXVEX];   //定义一数组用来判断边与边是否形成环路
	for (i = 0; i < g.numVertexes; i++) {
		for (j = r; j < g.numVertexes; j++) {  //因为矩阵为对称矩阵，所以会有重复的，所以不是j=0
			if (g.arc[i][j] != INFINITY) {
				edges[k].weight = g.arc[i][j];
				edges[k].begin = minNum(i, j);
				edges[k].end = maxNum(i, j);
				k++;
			}
		}
		r++;
	}
	//用冒泡排序对Edge数组排序
	for (i = 0; i < g.numEdges - 1; i++) {
		for (j = 0; j < g.numEdges - i - 1; j++) {
			if (edges[j].weight > edges[j + 1].weight) {
				temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
	for (i = 0; i < g.numVertexes; i++) {
		parent[i] = 0;    //初始化数组值为0
	}
	for (i = 0; i < g.numEdges; i++) {  //循环每一条边
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if (n != m) {
			parent[n] = m;                 //加入n与m不等，说明此边没有与现有的生成树形成环路，表示此顶点已经在生成树集合
			printf("V%d----V%d=%d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}

//Dijkstra算法，求无向网G的V0到其余顶点V最短路径长度和
//P[V]的值为前驱顶点下标，D]V]表示V0到V的最短路径长度和
void ShortestPath_Dijkstra(Graph g, int v0, Pathmatirx *P, ShortPathTable *D) {
	int v, w, k, min;
	int final[MAXVEX];            //final[w]=1表示求得顶点V0至Vw的最短路径
	for (v = 0; v < g.numVertexes; v++) {
		final[v] = 0;             //全部顶点初始化为未知最短路径状态
		(*D)[v] = g.arc[v0][v];   //将与v0点有连线的顶点加上权值
		(*P)[v] = 0;              //初始化路径数组P为0
	}
	(*D)[v0] = 0;                 //v0至v0路径为0
	final[v0] = 1;                //v0至v0不需要求路径
	/*开始主循环，每次求得v0到某个v顶点的最短路径*/
	for (v = 1; v < g.numVertexes; v++) {
		min = INFINITY;           //当前所知离v0顶点的最短距离
		for (w = 0; w < g.numVertexes; w++) { //寻找离v0最近的顶点
			if (!final[w] && (*D)[w] < min) {
				k = w;
				min = (*D)[w];    //w顶点离v0顶点更近
			}
		}
		final[k] = 1;             //将目前找到的最近的顶点置为1
		for (w = 0; w < g.numVertexes; w++) { //修正当前最短路径及距离
			//如果经过v顶点的路径比现在这条路径的长度短的话
			if (!final[w] && (min + g.arc[k][w] < (*D)[w])) {
				//说明找到了更短的路径，修改D[w]和P[w]
				(*D)[w] = min + g.arc[k][w];  //修改当前路径长度
				(*P)[w] = k;
			}
		}
	}
	return;
}

void showShortest01(Graph g) {
	int i, vk;
	Pathmatirx P;
	ShortPathTable D;
	printf("Dijkstra算法，求无向网G的V0到其余顶点V最短路径长度和\n");
	printf("请输入一个顶点，将为您计算该顶点到其余各顶点的最短距离，如顶点V0，即输入“0”\n");
	printf("请输入：");
	scanf("%d", &vk);
	ShortestPath_Dijkstra(g, vk, &P, &D);
	printf("源点到各顶点的最短路径长度为：\n");
	for (i = 0; i < g.numVertexes; i++) {
		printf("V%c--->V%c:%d\n", g.vexs[vk], g.vexs[i], D[i]);
	}
	return;
}

//Floyd算法，求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
void ShortestPath_Floyd(Graph g, Pathmatirx02 *P, ShortPathTable02 *D) {
	int v, w, k;
	for (v = 0; v < g.numVertexes; v++) {
		for (w = 0; w < g.numVertexes; w++) {
			(*D)[v][w] = g.arc[v][w];     //初始化D[]
			(*P)[v][w] = w;               //初始化P[]
		}
	}
	for (k = 0; k < g.numVertexes; k++) {
		for (v = 0; v < g.numVertexes; v++) {
			for (w = 0; w < g.numVertexes; w++) {
				if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
					//如果经过下标为k顶点路径比原两点间路径更短，将当前两点间权值设为更小的一个
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];      //路径设置经过下标为k的顶点
				}
			}
		}
	}
}

void showShortest02(Graph g) {
	Pathmatirx02 P;
	ShortPathTable02 D;
	int v, w, k;
	ShortestPath_Floyd(g, &P, &D);
	for (v = 0; v < g.numVertexes; v++) {
		for (w = v + 1; w < g.numVertexes; w++) {
			printf("v%d--->v%d，weight:%d\t", v, w, D[v][w]);
			k = P[v][w];             //获得第一个路径顶点下标
			printf("path:%d", v);    //打印源点
			while (k != w) {
				printf(" ->%d", k); //打印路径顶点
				k = P[k][w];         //获得下一个路径顶点下标
			}
			printf(" ->%d\n", w);   //打印终点
		}
		printf("\n");
	}

}

/*定位
int locates(Graph *g, char ch) {
	int i = 0;
	for (i = 0; i < g->numVertexes; i++) {
		if (g->vexs[i] == ch) {
			break;
		}
	}
	if (i >= g->numVertexes) {
		return 0;
	}
	return i;
}*/

//建立一个无向网图的邻接矩阵表示
void CreateCraph(Graph *g) {
	int i, j, k, w;
	printf("Please enter the number of vertexes:");
	scanf("%d", &g->numVertexes);
	printf("Please enter the number of edges:");
	scanf("%d", &g->numEdges);  //读入顶点的信息，建立顶点表
	for (i = 0; i < g->numVertexes; i++) {
		printf("Please enter the value of vertexes[%d]:", i);
		getchar();
		scanf("%c",&g->vexs[i]);
	}
	for (i = 0; i < g->numVertexes; i++) {
		for (j = 0; j < g->numVertexes; j++) {
			g->arc[i][j] = INFINITY;   //邻接矩阵初始化
		}
	}
	printf("\n");
	printf("For example：edge(Vi,Vj),i=1,j=2,weight=5,the right enter is:1,2,5\n");
	printf("If the edge has no weight,the value of weight is“1”！！\n");
	for (k = 0;k < g->numEdges; k++) {  //读入numEdges条边，建立邻接矩阵
		printf("Please enter the value of edge[%d]:",k);
		scanf("%d,%d,%d", &i, &j, &w);
		g->arc[i][j] = w;
		g->arc[j][i] = w;   //因为是无向图，矩阵对称
	}
}

void showGraph(Graph g) {
	int i, j;
	printf("\n");
	printf("Vertexes:%d    Edges:%d\n", g.numVertexes, g.numEdges);
	printf("The adjacent matrix is as follows:\n");
	for (i = 0; i < g.numVertexes; i++) {
		printf(" \t%c", g.vexs[i]);
	}
	printf("\n");
	for (i = 0; i < g.numVertexes; i++) {
		for (j = 0; j < g.numVertexes; j++) {
			if (j == 0) {
				printf("%c", g.vexs[i]);
			}
			if (g.arc[i][j] == INFINITY) {
				printf("\t∞");
			}
			else {
				printf("\t%d", g.arc[i][j]);
			}
		}
		printf("\n");
	}
}

int main() {
	Graph g;
	CreateCraph(&g);
	showGraph(g);
	printf("\n");
	printf("深度优先遍历:\n");
	DFSTraverse(g);
	printf("\n--------------------------\n");
	printf("广度优先遍历:\n");
	BFSTraverse(g);
	printf("\n--------------------------\n");
	printf("Prim算法生成最小生成树:\n");
	MinSpanTree_Prim(g);
	printf("--------------------------\n");
	printf("Kruskal算法生成最小生成树:\n");
	MinSpanTree_Kruskal(g);
	printf("--------------------------\n");
	showShortest01(g);
	printf("--------------------------\n");
	printf("Floyd算法，求网图G中各顶点v到其余顶点w最短路径\n");
	showShortest02(g);
	system("pause");
	return 0;
}
