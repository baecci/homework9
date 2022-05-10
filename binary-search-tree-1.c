#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;  //노드의 key(데이터)
	struct node *left;  //왼쪽 자식노드
	struct node *right;  //오른쪽 자식노드
} Node;

int initializeBST(Node** h);  /* 헤드노드(root) 생성 함수 */  

void inorderTraversal(Node* ptr);  /* 중위순회 방식 */
void preorderTraversal(Node* ptr);  /* 전위순회 방식 */
void postorderTraversal(Node* ptr);  /* 후위순회 방식 */
int insert(Node* head, int key);   /* 새로운 노드 삽입 함수 */
int deleteLeafNode(Node* head, int key);  /* 입력받은 key의 리프노드 삭제 */
Node* searchRecursive(Node* ptr, int key);  /* Recursive방식 탐색 */
Node* searchIterative(Node* head, int key);  /* Interative방식 탐색 */
int freeBST(Node* head);  /* 모든 노드의 메모리 해제 함수 */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	

	do{
		printf("\n\n");
		printf("---------------------- [배기원] [2021041081] --------------------\n");
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
			/* 헤드노드(root) 생성 함수 호출 */
			initializeBST(&head);  
			break;
		case 'q': case 'Q':
			/* 트리의 모든 노드 삭제 */
			freeBST(head);
			break;
		case 'n': case 'N':
			/* 입력받은 키에 따라 노드 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			/* 입력받은 키의 리프노드 삭제 */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			/* 입력받은 키의 노드를 Interative방식으로 탐색 후 찾으면 해당 노드 주소리턴 */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			/* 찾으면 해당 노드 주소리턴, 아니면 오류문구 출력 */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			/* 입력받은 키의 노드를 Recursive방식으로 탐색 */
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			/* 찾으면 해당 노드 주소리턴, 아니면 오류문구 출력 */
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			/* 중위순회 트리 추적 */
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			/* 전위순회 트리 추적 */
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			/* 후위순회 트리 추적 */
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

	/* 트리에 이미 노드가 존재하면 freeBST함수 호출 */
	if(*h != NULL)
		freeBST(*h);

	/* 헤드노드(root) 메모리 할당 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	/* 중위순회 방식으로 트리 추적 */
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	/* 전위순회 방식으로 트리 추적 */
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	/* 후위순회 방식으로 트리 추적 */
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

	/* root주소 전달 */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* 같은 키를 가진 노드가 이미 존재한다면, 함수 종료 */
		if(ptr->key == key) return 1;

		parentNode = ptr;

		/* 입력 key값이 현재 노드의 key보다 크면 오른쪽 노드로, 작으면 왼쪽 노드로 삽입 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* 부모노드에 따라 왼쪽자식노드 or 오른쪽자식노드로 삽입 */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{	
	/* 헤드노드가 없거나 자식노드가 없다면 오류 문구 출력 */
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* root주소 전달 */
	Node* ptr = head->left;


	/* 자식노드를 찾기 위한 노드 */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root 노드인 경우 */
				if(parentNode == head)
					head->left = NULL;

				/* 왼쪽or오른쪽 자식노드를 삭제 */
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

		/* 현재 노드가 입력한 key보다 작은 오른쪽, 큰 경우 왼쪽으로 이동 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}
	
	/* 입력한 key의 노드가 없으면 오류 문구 출력 */
	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	/* 입력 key가 현재 노드의 key보다 크면 오른쪽으로 이동, 아니면 왼쪽으로 이동 */
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* key가 같으면 주소 리턴 */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root의 주소 전달 */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		/* key가 같으면 주소 리턴 */
		if(ptr->key == key)
			return ptr;

		/* 입력 key가 현재 노드의 key보다 크면 오른쪽으로 이동, 아니면 왼쪽으로 이동 */
		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	/* 왼/족, 오른쪽 서브트리 메모리 해제 후 헤드노드까지 해제 */
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	/* 트리에 헤드노드만 존재한다면 헤드노드 메모리 해제 */
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





