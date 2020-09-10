#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;               //��������Ӧ���û�����
typedef int EdgeType;                  //���ϵ�Ȩֵ����Ӧ���û�����
typedef int QElemType;                 //*ElemType���͸���ʵ������������������Ϊint *
typedef int Status;

#define OK 1
#define ERROR 0
#define OVER -1

#define MAXVEX 100                     //��󶥵�����Ӧ���û�����
#define INFINITY 65535                 //��65535����������󣬵���Ȩֵʱ���������ʾ��������û�бߣ�������0
                                       //���´���û���õ�����Ҫֻ���ǲ���Ȩֵ�����
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)


//Dijkstra�㷨�����·��
typedef int Pathmatirx[MAXVEX];        //���ڴ洢���·���±������
//����P={0,0,1,1,2,2,0,0,0,}��ʾ����Դ�㵽V4��V5������·�����ǵ�ǰ������V2
typedef int ShortPathTable[MAXVEX];    //���ڴ洢���������·����Ȩֵ��

//Froyd�㷨�����·��
typedef int Pathmatirx02[MAXVEX][MAXVEX];
typedef int ShortPathTable02[MAXVEX][MAXVEX];

//Kruskal�㷨���Ա߼�����Edge�ṹ�Ķ���
typedef struct Edge {
	int begin;
	int end;
	int weight;
}Edge;

//���е���ʽ�洢�ṹ
typedef struct QNode {
	QElemType data;   //������
	struct QNode *next;  //�ṹ��
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;  //��ͷָ��
	QueuePtr rear;   //��βָ��
}LinkQueue;


typedef struct
{
	VertexType vexs[MAXVEX];            //�����
	EdgeType   arc[MAXVEX][MAXVEX];     //�ڽӾ��󣬿ɿ����߱�
	int numVertexes, numEdges;          //ͼ�е�ǰ�Ķ������ͱ���
}Graph;

typedef int Boolean;    //Boolean�ǲ������ͣ���ֵ��TRUE��FALSE
Boolean visited[MAXVEX];//���ʱ�־������
#define TRUE 1;
#define FALSE 0;

//��ʼ��һ���յĶ���
Status InitQueue(LinkQueue *Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front) {
		printf("initialization failed!!");
		exit(OVER);  //�洢����ʧ��
	}
	Q->front->next = NULL;
	return OK;
}

//���ٶ���
Status DestroyQueue(LinkQueue *Q) {
	while (Q->front) {
		Q->rear = Q->front->next;
		free(Q->front);    //�Ӷ�ͷȡ��ÿһ��Ԫ�ز��ͷ��ڴ棬Q->rear��Ϊһ����ʱָ��ʹ��
		Q->front = Q->rear;
	}
	return OK;
}

//�����п�
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear) {
		return OK;
	}
	return ERROR;
}

//��β����Ԫ��
Status EnterQueue(LinkQueue *Q, QElemType e) {
	QNode *p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) {
		return ERROR;
	}
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;  //��ǰ��βָ���nextָ����Ԫ��
	Q->rear = p;        //�޸�βָ��
	return OK;
}

//ɾ����ͷԪ�أ������ظ�Ԫ��
Status DeleteQueue(LinkQueue *Q, QElemType &e) {
	if (Q->front == Q->rear) {
		return ERROR;
	}
	QNode *p = Q->front->next;  //front��ָ��ͷ���ģ�ͷ��㲻�洢���ݣ�front��next�Ƕ�ͷ��㣬��p��Ϊ��ͷ���
	e = p->data;                //��ȡ��ͷ����
	Q->front->next = p->next;   //Q->front->next��ָͷ����nextָ��ȥ����p����һ����㣬���ǰ�ͷ���p�����ȥ��
	if (Q->rear == p) {         //����ö���ǡ��ֻ��һ��Ԫ�أ�ɾ��֮����о�Ϊ���ˣ�����front=near
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

//�ڽӾ����������ȵݹ��㷨
void DFS(Graph g, int i) {
	int j;
	visited[i] = TRUE;
	printf("%c ", g.vexs[i]);  //��ӡ���㣬Ҳ������������
	for (j = 0; j < g.numVertexes; j++) {
		if (g.arc[i][j] == 1 && !visited) { //���ĳ�������i�������б��һ�δ�����ʵ����ͽ��еݹ�
			DFS(g, j);       //��δ���ʵ��ڽӶ���ݹ����
		}
	}
}

//�ڽӾ������ȱ�������
void DFSTraverse(Graph g) {
	int i;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;  //��ʼ���ж���״̬����δ���ʹ���״̬
	}
	for (i = 0; i < g.numVertexes; i++) {
		if (!visited[i]) {   //��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
			DFS(g, i);
		}
	}
}

//�ڽӾ���Ĺ�����ȱ����㷨
void BFSTraverse(Graph g) {
	int i, j;
	LinkQueue Q;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;
	}
	InitQueue(&Q);                       //��ʼ��һ�����õĶ���
	for (i = 0; i < g.numVertexes; i++) {//��ÿһ��������ѭ��
		if (!visited[i]) {               //����δ���ʹ����ͽ��д���
			visited[i] = TRUE;           //��������Ϊ�ѷ��ʹ�
			printf("%c ", g.vexs[i]);    //��ӡ���㣬Ҳ��������������
			EnterQueue(&Q, i);           //���˶��������
			while (!EmptyQueue(&Q)) {
				DeleteQueue(&Q, i);      //��������Ԫ�س����У���ֵ��i
				for (j = 0; j < g.numVertexes; j++) {
					//�ж������������뵱ǰ������ڱ���δ���ʹ�
					if (g.arc[i][j] != INFINITY && !visited[j]) {
						visited[j] = TRUE;//���ҵ��Ĵ������Ϊ�ѷ���
						printf("%c ", g.vexs[j]);//��ӡ����
						EnterQueue(&Q, j);//���ҵ��Ĵ˶��������
					}
				}
			}
		}
	}
	DestroyQueue(&Q);
}

//Prim�㷨������С������
void MinSpanTree_Prim(Graph g) {
	int min, i, j, k;
	int adjvex[MAXVEX];  //������ض����±꣬�ñ�/��ָ��Ķ����λ��
	int lowcost[MAXVEX]; //������ض����ߵ�Ȩֵ
	lowcost[0] = 0;      //��ʼ����һ��ȨֵΪ0����V0������������lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ�����������
	adjvex[0] = 0;       //��ʼ����һ�������±�Ϊ0
	for (i = 1; i < g.numVertexes; i++) { //ѭ�����±�Ϊ0���ȫ������
		lowcost[i] = g.arc[0][i];         //��V0������֮�бߵ�Ȩֵ��������
		adjvex[i] = 0;                    //��ʼ����ΪV0���±�
	}
	for (i = 1; i < g.numVertexes; i++) {
		min = INFINITY;                   //��ʼ����СȨֵΪ��
		j = 1;
		k = 0;
		while (j < g.numVertexes) {
			if (lowcost[j] != 0 && lowcost[j] < min) {
				min = lowcost[j];         //���õ�ǰȨֵ��Ϊ��Сֵ
				k = j;                    //����ǰ��Сֵ���±����k
			}
			j++;
		}
		printf("V%d----V%d=%d\n", adjvex[k], k, min);//��ӡ��ǰ�������Ȩֵ��С��
		lowcost[k] = 0;                   //����ǰ�����Ȩֵ����Ϊ0����ʾ�˶������������
		for (j = 1; j < g.numVertexes; j++) {//ѭ�����ж���
			if (lowcost[j] != 0 && g.arc[k][j] < lowcost[j]) {
				//���±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ
				lowcost[j] = g.arc[k][j]; //����СȨֵ����lowcost
				adjvex[j] = k;            //���±�Ϊk�Ķ������adjvex
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

//�������߶����β���±�
int Find(int *parent, int f) {
	while (parent[f] > 0) {
		f = parent[f];
	}
	return f;
}

//Kruskal�㷨������С������
void MinSpanTree_Kruskal(Graph g) {
	int i, j, n, m;
	int k, r;
	r = 0;
	k = 0;
	Edge temp;
	Edge edges[MAXVEX];   //����߼�����
	int parent[MAXVEX];   //����һ���������жϱ�����Ƿ��γɻ�·
	for (i = 0; i < g.numVertexes; i++) {
		for (j = r; j < g.numVertexes; j++) {  //��Ϊ����Ϊ�Գƾ������Ի����ظ��ģ����Բ���j=0
			if (g.arc[i][j] != INFINITY) {
				edges[k].weight = g.arc[i][j];
				edges[k].begin = minNum(i, j);
				edges[k].end = maxNum(i, j);
				k++;
			}
		}
		r++;
	}
	//��ð�������Edge��������
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
		parent[i] = 0;    //��ʼ������ֵΪ0
	}
	for (i = 0; i < g.numEdges; i++) {  //ѭ��ÿһ����
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if (n != m) {
			parent[n] = m;                 //����n��m���ȣ�˵���˱�û�������е��������γɻ�·����ʾ�˶����Ѿ�������������
			printf("V%d----V%d=%d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}

//Dijkstra�㷨����������G��V0�����ඥ��V���·�����Ⱥ�
//P[V]��ֵΪǰ�������±꣬D]V]��ʾV0��V�����·�����Ⱥ�
void ShortestPath_Dijkstra(Graph g, int v0, Pathmatirx *P, ShortPathTable *D) {
	int v, w, k, min;
	int final[MAXVEX];            //final[w]=1��ʾ��ö���V0��Vw�����·��
	for (v = 0; v < g.numVertexes; v++) {
		final[v] = 0;             //ȫ�������ʼ��Ϊδ֪���·��״̬
		(*D)[v] = g.arc[v0][v];   //����v0�������ߵĶ������Ȩֵ
		(*P)[v] = 0;              //��ʼ��·������PΪ0
	}
	(*D)[v0] = 0;                 //v0��v0·��Ϊ0
	final[v0] = 1;                //v0��v0����Ҫ��·��
	/*��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��*/
	for (v = 1; v < g.numVertexes; v++) {
		min = INFINITY;           //��ǰ��֪��v0�������̾���
		for (w = 0; w < g.numVertexes; w++) { //Ѱ����v0����Ķ���
			if (!final[w] && (*D)[w] < min) {
				k = w;
				min = (*D)[w];    //w������v0�������
			}
		}
		final[k] = 1;             //��Ŀǰ�ҵ�������Ķ�����Ϊ1
		for (w = 0; w < g.numVertexes; w++) { //������ǰ���·��������
			//�������v�����·������������·���ĳ��ȶ̵Ļ�
			if (!final[w] && (min + g.arc[k][w] < (*D)[w])) {
				//˵���ҵ��˸��̵�·�����޸�D[w]��P[w]
				(*D)[w] = min + g.arc[k][w];  //�޸ĵ�ǰ·������
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
	printf("Dijkstra�㷨����������G��V0�����ඥ��V���·�����Ⱥ�\n");
	printf("������һ�����㣬��Ϊ������ö��㵽������������̾��룬�綥��V0�������롰0��\n");
	printf("�����룺");
	scanf("%d", &vk);
	ShortestPath_Dijkstra(g, vk, &P, &D);
	printf("Դ�㵽����������·������Ϊ��\n");
	for (i = 0; i < g.numVertexes; i++) {
		printf("V%c--->V%c:%d\n", g.vexs[vk], g.vexs[i], D[i]);
	}
	return;
}

//Floyd�㷨������ͼG�и�����v�����ඥ��w���·��P[v][w]����Ȩ����D[v][w]
void ShortestPath_Floyd(Graph g, Pathmatirx02 *P, ShortPathTable02 *D) {
	int v, w, k;
	for (v = 0; v < g.numVertexes; v++) {
		for (w = 0; w < g.numVertexes; w++) {
			(*D)[v][w] = g.arc[v][w];     //��ʼ��D[]
			(*P)[v][w] = w;               //��ʼ��P[]
		}
	}
	for (k = 0; k < g.numVertexes; k++) {
		for (v = 0; v < g.numVertexes; v++) {
			for (w = 0; w < g.numVertexes; w++) {
				if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
					//��������±�Ϊk����·����ԭ�����·�����̣�����ǰ�����Ȩֵ��Ϊ��С��һ��
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];      //·�����þ����±�Ϊk�Ķ���
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
			printf("v%d--->v%d��weight:%d\t", v, w, D[v][w]);
			k = P[v][w];             //��õ�һ��·�������±�
			printf("path:%d", v);    //��ӡԴ��
			while (k != w) {
				printf(" ->%d", k); //��ӡ·������
				k = P[k][w];         //�����һ��·�������±�
			}
			printf(" ->%d\n", w);   //��ӡ�յ�
		}
		printf("\n");
	}

}

/*��λ
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

//����һ��������ͼ���ڽӾ����ʾ
void CreateCraph(Graph *g) {
	int i, j, k, w;
	printf("Please enter the number of vertexes:");
	scanf("%d", &g->numVertexes);
	printf("Please enter the number of edges:");
	scanf("%d", &g->numEdges);  //���붥�����Ϣ�����������
	for (i = 0; i < g->numVertexes; i++) {
		printf("Please enter the value of vertexes[%d]:", i);
		getchar();
		scanf("%c",&g->vexs[i]);
	}
	for (i = 0; i < g->numVertexes; i++) {
		for (j = 0; j < g->numVertexes; j++) {
			g->arc[i][j] = INFINITY;   //�ڽӾ����ʼ��
		}
	}
	printf("\n");
	printf("For example��edge(Vi,Vj),i=1,j=2,weight=5,the right enter is:1,2,5\n");
	printf("If the edge has no weight,the value of weight is��1������\n");
	for (k = 0;k < g->numEdges; k++) {  //����numEdges���ߣ������ڽӾ���
		printf("Please enter the value of edge[%d]:",k);
		scanf("%d,%d,%d", &i, &j, &w);
		g->arc[i][j] = w;
		g->arc[j][i] = w;   //��Ϊ������ͼ������Գ�
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
				printf("\t��");
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
	printf("������ȱ���:\n");
	DFSTraverse(g);
	printf("\n--------------------------\n");
	printf("������ȱ���:\n");
	BFSTraverse(g);
	printf("\n--------------------------\n");
	printf("Prim�㷨������С������:\n");
	MinSpanTree_Prim(g);
	printf("--------------------------\n");
	printf("Kruskal�㷨������С������:\n");
	MinSpanTree_Kruskal(g);
	printf("--------------------------\n");
	showShortest01(g);
	printf("--------------------------\n");
	printf("Floyd�㷨������ͼG�и�����v�����ඥ��w���·��\n");
	showShortest02(g);
	system("pause");
	return 0;
}
