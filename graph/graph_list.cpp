//2023.12.6

#define MAX_SIZE 10
#include<assert.h>
#include<stdlib.h>

typedef struct GraphNode {
	int val;
	GraphNode* next = NULL;
}GraphNode;

typedef struct {
	GraphNode* head[MAX_SIZE];
	int size;
}Graph;


void Add(GraphNode* graphnode, int i)//��i�����
{
	GraphNode* tmp = (GraphNode*)malloc(sizeof(GraphNode));
	tmp->val = i;
	tmp->next = graphnode->next;
	graphnode->next = tmp;
}

void DelNext(GraphNode* graphnode)//ɾ���ڵ��Ľڵ�
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
	Add(graph->head[i], j);//��i�����
	Add(graph->head[j], i);//��j�����
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

bool DelEdge(Graph* graph, int i, int j)//i��j������
{
	if (i < 0 || i >= graph->size)
		return false;
	GraphNode* cur = graph->head[i]->next;
	GraphNode* pre = graph->head[i];
	while (cur)//ɾ��i���Ӧ��j�ڵ�
	{
		if (graph->head[j] == graph->head[cur->val])
			DelNext(pre);
		break;
		pre = cur;
		cur = cur->next;
	}
	cur = graph->head[j]->next;
	pre = graph->head[j];
	while (cur)//ɾ��j���Ӧ��i�ڵ�
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

bool DelNode(Graph* graph, int i)//Ϊ�˱�֤��������������û�ж�i֮��Ľڵ��������
{
	if (i < 0 || i >= graph->size)
		return false;
	while (graph->head[i]->next)//ɾ��i�����еı�
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
	DelNode(graph, 2);
	DelGraph(graph);
	return 0;
}