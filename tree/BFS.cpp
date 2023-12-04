#include<stdlib.h>
#include<stdio.h>
#define MAX_SIZE 20

typedef struct TreeNode//定义一个节点
{
	int val;
	int height;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

TreeNode* NewTreeNode(int x)//创建一个新的节点
{
	TreeNode* treenode = (TreeNode*)malloc(sizeof(TreeNode));
	treenode->val = x;
	treenode->height = 0;
	treenode->left = NULL;
	treenode->right = NULL;
	return treenode;
}

int* BFS(TreeNode* root, int* size)//层次遍历（广度优先）
{
	int front, rear;
	int index, * visit;
	TreeNode** queue;
	TreeNode* node;
	front = 0;
	rear = 0;
	queue = (TreeNode**)malloc(sizeof(TreeNode*) * MAX_SIZE);
	visit = (int*)malloc(sizeof(int) * MAX_SIZE);
	queue[rear++] = root;
	index = 0;
	while (front < rear)
	{
		node = queue[front++];
		visit[index++] = node->val;
		if (node->left != NULL)
			queue[rear++] = node->left;
		if (node->right != NULL)
			queue[rear++] = node->right;
	}
	visit[index] = -1;
	free(queue);
	*size = index;
	return visit;
}


void PreOrder(TreeNode* root, int* visit, int* index)//先序遍历
{
	if (root != NULL)
		visit[(*index)++] = root->val;
	if (root != NULL)
		PreOrder(root->left, visit, index);
	if (root != NULL)
		PreOrder(root->right, visit, index);
}

void InOrder(TreeNode* root, int* visit, int* index)//中序遍历
{
	if (root != NULL)
		InOrder(root->left, visit, index);
	if (root != NULL)
		visit[(*index)++] = root->val;
	if (root != NULL)
		InOrder(root->right, visit, index);
}

void PostOrder(TreeNode* root, int* visit, int* index)//后序遍历
{
	if (root != NULL)
		PostOrder(root->left, visit, index);
	if (root != NULL)
		PostOrder(root->right, visit, index);
	if (root != NULL)
		visit[(*index)++] = root->val;
}


int main()
{
	//树的创建（连接节点）
	TreeNode* n1 = NewTreeNode(2);
	TreeNode* n2 = NewTreeNode(1);
	TreeNode* n3 = NewTreeNode(5);
	TreeNode* n4 = NewTreeNode(3);
	TreeNode* n5 = NewTreeNode(7);
	TreeNode* n6 = NewTreeNode(6);
	n1->left = n2;
	n1->right = n4;
	n1->height++;
	n2->right = n3;
	n4->left = n6;
	n4->right = n5;
	n1->height++;


	int num = 0;
	int visit_dfs[MAX_SIZE];
	int index = 0;

	int* visit = BFS(n1, &num);//层次遍历序列
	for (; *visit != -1; visit++)
		printf("%d ", *visit);
	printf("\n");

	PreOrder(n1, visit_dfs, &index);//先序遍历序列
	for (int* i = visit_dfs; *i > 0; i++)
		printf("%d ", *i);
	printf("\n");
	index = 0;

	InOrder(n1, visit_dfs, &index);//中序遍历序列
	for (int* i = visit_dfs; *i > 0; i++)
		printf("%d ", *i);
	printf("\n");
	index = 0;


	PostOrder(n1, visit_dfs, &index);//后序遍历序列
	for (int* i = visit_dfs; *i > 0; i++)
		printf("%d ", *i);
	printf("\n");

	printf("%d", num);//节点数
	return 0;
}