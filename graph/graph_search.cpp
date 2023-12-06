#define MAX_SIZE 10
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct GraphNode {
	int val;
	GraphNode* next = NULL;
}GraphNode;

typedef struct {
	GraphNode* head[MAX_SIZE];
	int size;
}Graph;


void Add(GraphNode* graphnode, int i)//在i处添加
{
	GraphNode* tmp = (GraphNode*)malloc(sizeof(GraphNode));
	tmp->val = i;
	tmp->next = graphnode->next;
	graphnode->next = tmp;
}

void DelNext(GraphNode* graphnode)//删除节点后的节点
{
	GraphNode* tmp = graphnode->next;
	graphnode->next = tmp->next;
	free(tmp);
}

Graph* InitGraph()
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	for (int i = 0; i < MAX_SIZE; i++)
		graph->head[i] = NULL;
	graph->size = 0;
	return graph;
}

bool AddEdge(Graph* graph, int i, int j)
{
	if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j)
		return false;
	Add(graph->head[i], j);//在i处添加
	Add(graph->head[j], i);//在j处添加
	return true;
}

bool AddNode(Graph* graph, int x)
{
	if (graph->size == MAX_SIZE)
		return false;
	GraphNode* cur = (GraphNode*)malloc(sizeof(GraphNode));
	cur->val = x;
	cur->next = NULL;
	graph->head[graph->size++] = cur;
	return true;
}

bool DelEdge(Graph* graph, int i, int j)//i，j是索引
{
	if (i < 0 || i >= graph->size)
		return false;
	GraphNode* cur = graph->head[i]->next;
	GraphNode* pre = graph->head[i];
	while (cur)//删除i里对应的j节点
	{
		if (graph->head[j] == graph->head[cur->val])
			DelNext(pre);
		break;
		pre = cur;
		cur = cur->next;
	}
	cur = graph->head[j]->next;
	pre = graph->head[j];
	while (cur)//删除j里对应的i节点
	{
		if (graph->head[i] == graph->head[cur->val])
		{
			DelNext(pre);
			break;
		}
		pre = cur;
		cur = cur->next;
	}
	return true;
}

bool DelNode(Graph* graph, int i)//为了保证数组索引，所以没有对i之后的节点进行上移
{
	if (i < 0 || i >= graph->size)
		return false;
	while (graph->head[i]->next)//删除i里所有的边
	{
		GraphNode* cur = graph->head[i]->next;
		DelEdge(graph, i, cur->val);
	}
	free(graph->head[i]);
	graph->size--;
}

void DelGraph(Graph* graph)
{
	for (int n = 0; n < graph->size; n++)
	{
		DelNode(graph, n);
	}
	free(graph);
}




typedef struct {
	int queue[MAX_SIZE];
	int front, rear, size;
}Queue;

void InQueue(Queue* queue, Graph* graph, int x)
{
	queue->queue[queue->rear] = x;
	queue->rear = (queue->rear + 1) % MAX_SIZE;
	queue->size++;
}

void Dequeue(Queue* queue, Graph* graph, int* x)
{
	*x = queue->queue[queue->front];
	queue->front = (queue->front + 1) % MAX_SIZE;
	queue->size--;
}

void InitQueue(Queue* queue)
{
	queue->rear = 0;
	queue->front = 0;
	queue->size = 0;
}

int* Graph_BFS(Graph* graph, int x)//从节点x（x是索引）开始BFS
{
	Queue queue;
	InitQueue(&queue);
	int* visit = (int*)malloc(sizeof(int));
	int visit_n = 0;
	bool is_visit[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		is_visit[i] = false;
	}
	InQueue(&queue, graph, x);
	is_visit[x] = true;
	while (queue.size > 0)//队列已满或队列已空
	{
		assert(visit);
		Dequeue(&queue, graph, &visit[visit_n]);
		GraphNode* n = graph->head[visit[visit_n++]]->next;
		assert(n);
		while (n)//遍历与出队节点连接的节点，并让他们进队
		{
			if (!is_visit[n->val])
			{
				InQueue(&queue, graph, n->val);
				is_visit[n->val] = true;
			}
			n = n->next;
		}
	}
	return visit;
}

void Graph_DFS(Graph* graph, int* visit, bool* is_visit, int x, int* visit_n)//从节点x（x是索引）开始BFS
{
	is_visit[x] = true;
	visit[(*visit_n)++] = x;
	GraphNode* n = graph->head[x];
	while (true)//判断结束
	{
		if (!is_visit[x])
		{
			Graph_DFS(graph, visit, is_visit, x, visit_n);
		}
		n = n->next;
		if (!n)
			break;
		x = n->val;
	}

}



int main()
{
	Graph* graph = InitGraph();
	AddNode(graph, 1);
	AddNode(graph, 2);
	AddNode(graph, 3);
	AddNode(graph, 4);
	AddNode(graph, 5);
	AddEdge(graph, 0, 1);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 0, 4);
	AddEdge(graph, 1, 2);
	AddEdge(graph, 1, 4);
	AddEdge(graph, 3, 4);
	AddEdge(graph, 3, 1);
	int* visit = Graph_BFS(graph, 0);
	for (int i = 0; i < graph->size; i++)
	{
		printf("%d ", graph->head[visit[i]]->val);
	}
	printf("\n");
	int* visit_dfs = (int*)malloc(sizeof(int));
	int visit_n = 0;
	bool is_visit[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		is_visit[i] = false;
	}
	Graph_DFS(graph, visit_dfs, is_visit, 0, &visit_n);
	for (int i = 0; i < graph->size; i++)
	{
		printf("%d ", graph->head[visit_dfs[i]]->val);
	}
	return 0;
}