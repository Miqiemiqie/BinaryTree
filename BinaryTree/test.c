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

//������ǰ�����
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
//���������������
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
//�������ĺ������
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

//����������ڵ����
int BinaryTreeSize(BTNode* root)
{
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}
//������Ҷ�ӽڵ�ĸ���
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL) //��������0
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL) //��ǰ�ڵ�������������ǿյĻ�����ΪҶ�ӽڵ㣬����1
	{
		return 1;
	}
	//�Ȳ�Ϊ��Ҳ����Ҷ�ӽڵ㣬�������µݹ�
	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
//��������K��ڵ����
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	//����������������ĵ�1��ĵ�K�� == �����������ĵ�2��ĵ�K-1�� == �����������ĵ�3��ĵ�K-2��
	//��ô��K==1��ʱ�� �������ǰ�������нڵ�ĸ��� ����
	if (k == 1)
	{
		return 1;
	}
	return BinaryTreeLevelKSize(root->right, k - 1) + BinaryTreeLevelKSize(root->left, k - 1);
}
//���������/�߶�
int BinaryTreeDepth(BTNode* root)
{
	if (root == NULL)
	{
		return 0; //�ڵ�Ϊ�� ����0
	}
	//����ڵ㲻Ϊ�գ���ݹ�����������������
	int leftDepth = BinaryTreeDepth(root->left);
	int rightDepth = BinaryTreeDepth(root->right);

	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}
//����������ֵΪx�Ľڵ�
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
//�������
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
//�ж��Ƿ�Ϊ��ȫ������
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
			//�����սڵ�����
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
		if (front)//ֻҪ��һ����Ϊ�յĽڵ� �Ͳ�����ȫ������
		{
			QueueDestroy(&q);
			return false;
		}
	}
	//�������Ϊ�գ�������ȫ������
	QueueDestroy(&q);
	return true;
}
//����������
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