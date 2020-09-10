#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;                //��������Ӧ���û�����
typedef int EdgeType;                  //���ϵ�Ȩֵ����Ӧ���û�����
typedef int QElemType;                 //*ElemType���͸���ʵ������������������Ϊint *
typedef int Status;
#define OK 1
#define ERROR 0
#define OVER -1

#define MAXVEX 100                     //��󶥵�����Ӧ���û�����
#define INFINITY 65535                 //��65535����������󣬵���Ȩֵʱ���������ʾ��������û�бߣ�������0
									   //���´���û���õ�����Ҫֻ���ǲ���Ȩֵ�����#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)

//���е���ʽ�洢�ṹ
typedef struct QNode {
	QElemType data;   //������
	struct QNode *next;  //�ṹ��
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;  //��ͷָ��
	QueuePtr rear;   //��βָ��
}LinkQueue;


typedef struct EdgeNode {   //�߱���
	int adjvex;             //�ڽӵ��򣬴洢�ö����Ӧ���±�
	//EdgeType weight;      //���ڴ洢Ȩֵ�����ڷ���ͼ���Բ���Ҫ
	struct EdgeNode *next;  //���ӣ�ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode { //�������
	int in;                 //�����������ڴ洢��������
	VertexType data;        //�����򣬴洢������Ϣ
	EdgeNode *firstedge;    //�߱�ͷָ��
}VertexNode,AdjList[MAXVEX];

typedef struct {
	AdjList adjList;            //�������
	int numVertexes, numEdges;  //ͼ�е�ǰ�������ͱ���
}GraphAdjList;

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

//�ڽӱ��������ȵݹ��㷨
void DFS(GraphAdjList g, int i) {
	EdgeNode *p;
	visited[i] = TRUE;
	printf("%d ", g.adjList[i].data);  //��ӡ���㣬Ҳ������������
	p = g.adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex])
			DFS(g, p->adjvex);        //�Է��ʵ��ڽӶ���ݹ����
		p = p->next;
	}
}

//�ڽӱ����ȱ�������
void DFSTraverse(GraphAdjList g) {
	int i;
	for (i = 0; i < g.numVertexes; i++) {
		visited[i] = FALSE;           //��ʼ���ж���״̬����δ���ʹ���״̬
	}
	for (i = 0; i < g.numVertexes; i++) {
		if (!visited[i]) {            //��δ���ʹ��Ķ������DFS��������ͨͼ��ֻ��ִ��һ��
			DFS(g, i);
		}
	}
}

//�ڽӱ�Ĺ�ȱ����㷨
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
			printf("%d ", g.adjList[i].data);      //��ӡ���㣬Ҳ��������������
			EnterQueue(&Q, i);
			while (!EmptyQueue(&Q)) {
				DeleteQueue(&Q, i);
				p = g.adjList[i].firstedge;        //�ҵ���ǰ����߱�����ͷָ��
				while (p) {
					if (!visited[p->adjvex]) {     //���˶���δ������
						visited[p->adjvex] = TRUE;
						printf("%d ", g.adjList[p->adjvex].data);
						EnterQueue(&Q, p->adjvex); //���˶������
					}
					p = p->next;                   //ָ��ָ����һ���ڽӵ�
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

//����������ͼ�޻�·������������������в�����OK�����л�·����ERROR
Status TopologicalSort(GraphAdjList g) {
	EdgeNode *e;
	int temp;
	int i, k, gettop;
	int top = 0;     //����ջָ���±�
	int count = 0;   //����ͳ���������ĸ���
	int *stack;      //��ջ���洢���Ϊ0�Ķ���
	stack = (int*)malloc(g.numVertexes * sizeof(int));
	for (i = 0; i < g.numVertexes; i++) {
		if (g.adjList[i].in == 0) {
			stack[++top] = i;   //�����Ϊ0�Ķ�����ջ
		}
	}
	while (top != 0) {
		gettop = stack[top--];  //��ջ
		printf("%d ", g.adjList[gettop].data);
		count++;                //ͳ�����������
		for (e = g.adjList[gettop].firstedge; e; e = e->next) {
			//�Դ˶��㻡�����
			k = e->adjvex;
			if (!(--g.adjList[k].in)) {  //��k�Ŷ����ڽӵ����ȼ�1
				stack[++top] = k;
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

void CreateGraph(GraphAdjList *g) {
	int i, j, k;
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
	printf("For example��edge(Vi,Vj),i=1,j=2,the right enter is:1,2.That means vertex 1 points to vertex 2.\n");
	for (k = 0; k < g->numEdges; k++) {
		printf("Please enter the value of edge[%d]:", k);
		scanf("%d,%d", &i, &j);

		//����j����ȼ�һ
		g->adjList[j].in++;

		//�������ͷ�巨
		e = (EdgeNode*)malloc(sizeof(EdgeNode));//���ڴ�����ռ䣬���ɱ߱���
		if (e == NULL) {
			printf("malloc() error.\n");
			return;
		}
		e->adjvex = j;                          //�ڽ����Ϊj
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
	printf("������ȱ���:\n");
	DFSTraverse(g);
	printf("\n");
	printf("--------------------------\n");
	printf("������ȱ���:\n");
	BFSTraverse(g);
	printf("\n");
	printf("--------------------------\n");
	printf("��������:\n");
	if (TopologicalSort(g)) {
		printf("\n��ͼ�����ڻ�·����������ɹ���!\n");
	}
	else {
		printf("\n��ͼ���ڻ�·���������򲻳ɹ�����\n");
	}
	system("pause");
	return 0;
}