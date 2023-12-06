//2023.12.5

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#define MAX_SIZE 20

typedef struct {
	int vertices[MAX_SIZE];//节点
	int graph_mat[MAX_SIZE][MAX_SIZE];//节点关系
	int size;//节点数量
}Graph;//图

Graph* InitGraph()//初始化图
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	assert(graph);
	graph->size = 0;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			graph->graph_mat[i][j] = 0;
		}
	}
	return graph;
}

void DeGraph(Graph* graph)
{
	free(graph);
}

bool AddVertice(Graph* graph, int val)
{
	if (graph->size >= MAX_SIZE)//判断是否已满
		return false;
	for (int i = 0; i < MAX_SIZE; i++)//行,列初始化
	{
		graph->graph_mat[i][graph->size] = graph->graph_mat[graph->size][i] = 0;
	}
	graph->vertices[graph->size++] = val;//节点加入到图
	return true;
}

bool DeleteVertice(Graph* graph, int index)
{
	if (graph->size == 0)
		return false;
	int n = 0;
	for (; n < MAX_SIZE; n++)//找到要删除的节点
	{
		if (graph->vertices[n] == index)
			break;
	}
	for (int i = n; i < graph->size; i++)//把要删除的节点往前移
	{
		graph->vertices[i] = graph->vertices[i + 1];
	}
	for (int i = n; i < graph->size; i++)//行上移
		for (int j = 0; j < graph->size; j++)
		{
			graph->graph_mat[i][j] = graph->graph_mat[i + 1][j];
		}
	for (int i = 0; i < graph->size; i++)//列左移
		for (int j = n; j < graph->size; j++)
		{
			graph->graph_mat[i][j] = graph->graph_mat[i][j + 1];
		}
	graph->size--;
	return true;
}

bool AddEdge(Graph* graph, int i, int j)
{
	if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j)
		return false;
	graph->graph_mat[i][j] = 1;
	graph->graph_mat[j][i] = 1;
	return true;
}

bool DeleteEdge(Graph* graph, int i, int j)
{
	if (i < 0 || j < 0 || i >= graph->size || j >= graph->size || i == j)
		return false;
	graph->graph_mat[i][j] = 0;
	graph->graph_mat[j][i] = 0;
	return true;
}

void PrintGraph(Graph* graph)
{
	printf("节点：");
	for (int i = 0; i < graph->size; i++)
	{
		printf("%d ", graph->vertices[i]);
	}
	printf("\n");
	printf("邻接矩阵：\n");
	for (int i = 0; i < graph->size; i++)
	{
		for (int j = 0; j < graph->size; j++)
		{
			printf("%d  ", graph->graph_mat[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	Graph* graph = InitGraph();
	AddVertice(graph, 1);
	AddVertice(graph, 2);
	AddVertice(graph, 3);
	AddVertice(graph, 4);
	AddVertice(graph, 5);
	AddEdge(graph, 0, 2);
	AddEdge(graph, 0, 4);
	AddEdge(graph, 0, 1);
	AddEdge(graph, 2, 1);
	AddEdge(graph, 1, 4);
	AddEdge(graph, 3, 4);
	AddEdge(graph, 1, 3);
	DeleteVertice(graph, 3);
	AddVertice(graph, 3);
	AddEdge(graph, 0, 4);
	PrintGraph(graph);
	return 0;
}