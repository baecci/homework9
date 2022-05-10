#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;  //����� key(������)
	struct node *left;  //���� �ڽĳ��
	struct node *right;  //������ �ڽĳ��
} Node;

int initializeBST(Node** h);  /* �����(root) ���� �Լ� */  

void inorderTraversal(Node* ptr);  /* ������ȸ ��� */
void preorderTraversal(Node* ptr);  /* ������ȸ ��� */
void postorderTraversal(Node* ptr);  /* ������ȸ ��� */
int insert(Node* head, int key);   /* ���ο� ��� ���� �Լ� */
int deleteLeafNode(Node* head, int key);  /* �Է¹��� key�� ������� ���� */
Node* searchRecursive(Node* ptr, int key);  /* Recursive��� Ž�� */
Node* searchIterative(Node* head, int key);  /* Interative��� Ž�� */
int freeBST(Node* head);  /* ��� ����� �޸� ���� �Լ� */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
		printf("\n\n");
		printf("---------------------- [����] [2021041081] --------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			/* �����(root) ���� �Լ� ȣ�� */
			initializeBST(&head);  
			break;
		case 'q': case 'Q':
			/* Ʈ���� ��� ��� ���� */
			freeBST(head);
			break;
		case 'n': case 'N':
			/* �Է¹��� Ű�� ���� ��� ���� */
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			/* �Է¹��� Ű�� ������� ���� */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			/* �Է¹��� Ű�� ��带 Interative������� Ž�� �� ã���� �ش� ��� �ּҸ��� */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			/* ã���� �ش� ��� �ּҸ���, �ƴϸ� �������� ��� */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			/* �Է¹��� Ű�� ��带 Recursive������� Ž�� */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			/* ã���� �ش� ��� �ּҸ���, �ƴϸ� �������� ��� */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			/* ������ȸ Ʈ�� ���� */
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			/* ������ȸ Ʈ�� ���� */
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			/* ������ȸ Ʈ�� ���� */
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* Ʈ���� �̹� ��尡 �����ϸ� freeBST�Լ� ȣ�� */
	if(*h != NULL)
		freeBST(*h);

	/* �����(root) �޸� �Ҵ� */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	/* ������ȸ ������� Ʈ�� ���� */
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	/* ������ȸ ������� Ʈ�� ���� */
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	/* ������ȸ ������� Ʈ�� ���� */
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* root�ּ� ���� */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* ���� Ű�� ���� ��尡 �̹� �����Ѵٸ�, �Լ� ���� */
		if(ptr->key == key) return 1;

		parentNode = ptr;

		/* �Է� key���� ���� ����� key���� ũ�� ������ ����, ������ ���� ���� ���� */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* �θ��忡 ���� �����ڽĳ�� or �������ڽĳ��� ���� */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{	
	/* ����尡 ���ų� �ڽĳ�尡 ���ٸ� ���� ���� ��� */
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* root�ּ� ���� */
	Node* ptr = head->left;


	/* �ڽĳ�带 ã�� ���� ��� */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root ����� ��� */
				if(parentNode == head)
					head->left = NULL;

				/* ����or������ �ڽĳ�带 ���� */
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		parentNode = ptr;

		/* ���� ��尡 �Է��� key���� ���� ������, ū ��� �������� �̵� */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}
	
	/* �Է��� key�� ��尡 ������ ���� ���� ��� */
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	/* �Է� key�� ���� ����� key���� ũ�� ���������� �̵�, �ƴϸ� �������� �̵� */
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* key�� ������ �ּ� ���� */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root�� �ּ� ���� */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		/* key�� ������ �ּ� ���� */
		if(ptr->key == key)
			return ptr;

		/* �Է� key�� ���� ����� key���� ũ�� ���������� �̵�, �ƴϸ� �������� �̵� */
		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	/* ��/��, ������ ����Ʈ�� �޸� ���� �� �������� ���� */
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	/* Ʈ���� ����常 �����Ѵٸ� ����� �޸� ���� */
	if(head->left == head)
	{
		free(head);
		return 1;
	}
	
	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}





