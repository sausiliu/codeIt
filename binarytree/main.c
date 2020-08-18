#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
	char ch;
	struct TreeNode *lchild;
	struct TreeNode *rchild;
};

void createBTree(struct TreeNode **root)
{
	char ch;
	ch = getchar();
	//getchar();
	if(ch == '#')
		*root = NULL;
	else {
		*root = (struct TreeNode *) malloc(sizeof(struct TreeNode));
		(*root)->ch = ch;
		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
		createBTree(&(*root)->lchild);
		createBTree(&(*root)->rchild);
	}
}

void preOrder(struct TreeNode *root)
{
	if(root == NULL)
		return;
	printf("%-3c", root->ch);
	preOrder(root->lchild);
	preOrder(root->rchild);
}

int main(int argc, const char *argv[])
{

	int temp ;

	temp = 10;
	temp = 20;
	temp = 30;
	struct TreeNode * root = NULL;

	//int aray[1024 * 8];

	//aray[0] = 100;
	//aray[1024 * 8 -1 ] = 12;
	createBTree(&root);
	preOrder(root);
	return 0;
}
