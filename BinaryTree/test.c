#include "Queue.h"

typedef char BTDataType;
typedef struct BinaryTree
{
	struct BinaryTree* left;
	struct BinaryTree* right;
	BTDataType data;
}BTNode;

BTNode* BuyNode(BTDataType x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		printf("malloc failed\n");
		exit(-1);
	}
	newnode->data = x;
	newnode->left = newnode->right = NULL;
	return newnode;
}
BTNode* CreateBinaryTree()
{
	BTNode* nodeA = BuyNode('A');
	BTNode* nodeB = BuyNode('B');
	BTNode* nodeC = BuyNode('C');
	BTNode* nodeD = BuyNode('D');
	BTNode* nodeE = BuyNode('E');
	BTNode* nodeF = BuyNode('F');
	BTNode* nodeG = BuyNode('G');
	nodeA->left = nodeB;
	nodeA->right = nodeC;
	nodeB->left = nodeD;
	nodeC->left = nodeE;
	nodeC->right = nodeF;
	nodeF->right = nodeG;

	return nodeA;
}

//二叉树前序遍历
void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}
//二叉树的中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	InOrder(root->left);
	printf("%c ", root->data);
	InOrder(root->right);
}
//二叉树的后序遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%c ", root->data);
}

//计算二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}
//二叉树叶子节点的个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL) //空树返回0
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) //当前节点的左右子树都是空的话，即为叶子节点，返回1
	{
		return 1;
	}
	//既不为空也不是叶子节点，继续往下递归
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
//二叉树第K层节点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	//相对于整个二叉树的第1层的第K层 == 整个二叉树的第2层的第K-1层 == 整个二叉树的第3层的第K-2层
	//那么到K==1的时候 计算出当前层数所有节点的个数 即可
	if (k == 1)
	{
		return 1;
	}
	return BinaryTreeLevelKSize(root->right, k - 1) + BinaryTreeLevelKSize(root->left, k - 1);
}
//二叉树深度/高度
int BinaryTreeDepth(BTNode* root)
{
	if (root == NULL)
	{
		return 0; //节点为空 返回0
	}
	//如果节点不为空，则递归计算左右子树的深度
	int leftDepth = BinaryTreeDepth(root->left);
	int rightDepth = BinaryTreeDepth(root->right);

	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}
//二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	if (root == NULL)
		return NULL;
	if (root->data == x)
		return root;
	
	BTNode*leftRet = BinaryTreeFind(root->left, x);
	if (leftRet)
		return leftRet;
	
	BTNode* rightRet = BinaryTreeFind(root->right, x);
	if (rightRet)
		return rightRet;
	
	return NULL;

}
//层序遍历
void BinaryTreeLevelOrder(BTNode* root)
{
	assert(root);

	Queue q;
	QueueInit(&q);
	QueuePUsh(&q, root);
	while (!QueueIsEmpty(&q))
	{
		BTNode* front = QUeueBegin(&q);
		QueuePop(&q);
		printf("%c ", front->data);

		if (front->left)
		{
			QueuePUsh(&q, front->left);
		}
		if (front->right)
		{
			QueuePUsh(&q, front->right);
		}
	}
	printf("\n");
	QueueDestroy(&q);

}
//判断是否为完全二叉树
bool BinaryIsComplete(BTNode* root)
{
	assert(root);

	Queue q;
	QueueInit(&q);
	QueuePUsh(&q, root);
	while (!QueueIsEmpty(&q))
	{
		BTNode* front = QUeueBegin(&q);
		QueuePop(&q);
		if (front == NULL)
		{
			//遇到空节点跳出
			break;
		}
		else
		{
			QueuePUsh(&q, front->left);
			QueuePUsh(&q, front->right);
		}
	}
	while (!QueueIsEmpty(&q))
	{
		BTNode* front = QUeueBegin(&q);
		QueuePop(&q);
		if (front)//只要有一个不为空的节点 就不是完全二叉树
		{
			QueueDestroy(&q);
			return false;
		}
	}
	//如果队列为空，则是完全二叉树
	QueueDestroy(&q);
	return true;
}
//二叉树销毁
void BinaryTreeDestroy(BTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	BinaryTreeDestroy(root->left);
	BinaryTreeDestroy(root->right);
	free(root);

}
int main()
{
	BTNode* root = CreateBinaryTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");
	printf("BinaryTreeSize is %d\n", BinaryTreeSize(root));
	printf("BinaryTreeLeafSize is %d\n", BinaryTreeLeafSize(root));
	printf("BinaryTreeLevelKSize is %d\n", BinaryTreeLevelKSize(root,2));
	printf("BinaryTreeDepth is %d\n", BinaryTreeDepth(root));
	printf("BinaryTreeFind is %p\n", BinaryTreeFind(root,'E'));
	printf("BinaryIsComplete is %d\n", BinaryIsComplete(root));
	BinaryTreeLevelOrder(root);
	BinaryTreeDestroy(root);
	root = NULL;


	return 0;
}