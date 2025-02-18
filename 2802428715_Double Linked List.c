#include<stdio.h>
#include<stdlib.h>

struct tnode
{
	int x;
	struct tnode *next;
	struct tnode *prev;
}*head, *tail;

void push_front(int value)
{
	struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
	node->x = value;
	node->next = NULL;
	node->prev = NULL;
	
	if(head==NULL)
	{
		head = tail = node;
	}
	else
	{
		struct tnode *prevHead = head;
		head = node;
		head->next = prevHead;
		prevHead->prev = head;
	}
}

void push_back(int value)
{
	struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
	node->x = value;
	node->next = NULL;
	node->prev = NULL;
	
	if(head==NULL)
	{
		head = tail = node;
	}
	else
	{
		struct tnode *prevTail = tail;
		tail = node;
		tail->prev = prevTail;
		prevTail->next = tail;
	}
}

void push_mid(int value, int searchKey)
{	
	struct tnode *node = (struct tnode*) malloc(sizeof(struct tnode));
	node->x = value;
	node->next = NULL;
	node->prev = NULL;
	
	if(head==NULL)
	{
		head = tail = node;
	}
	else
	{
		struct tnode *curr = head;
		while(curr!=NULL)
		{
			if(curr->x == searchKey)
			{
				if(curr == head)
				{
					push_front(value);
					free(node);
				}
				else if(curr == tail)
				{
					push_back(value);
					free(node);
				}
				else
				{
					struct tnode *leftNode = curr->prev;
					struct tnode *rightNode = curr;
					leftNode->next = node;
					node->prev = leftNode;
					node->next = rightNode;
					rightNode->prev = node;
				}
				break;
			}
			curr = curr->next;
		}
		if(curr==NULL)
		{
			printf("Data %d is not found in the linked list\n", searchKey);
		}
	}
}

void delete_front()
{
	if(head==NULL)
	{
		printf("There is no data\n");
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = head;
			head = head->next;
			head->prev = NULL;
			free(del);
		}
	}
}

void delete_back()
{
	if(tail==NULL)
	{
		printf("There is no data\n");
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = tail;
			tail = tail->prev;
			tail->next = NULL;
			free(del);
		}
	}
}

void delete_mid(int searchKey)
{
	if(head==NULL)
	{
		printf("There is no data\n");
	}
	else
	{
		struct tnode *curr = head;
		while(curr!=NULL)
		{
			if(curr->x == searchKey)
			{
				if(curr == head)
				{
					delete_front();
				}
				else if(curr == tail)
				{
					delete_back();
				}
				else
				{
					struct tnode *leftNode = curr->prev;
					struct tnode *deleteNode = curr;
					struct tnode *rightNode = curr->next;
					leftNode->next = rightNode;
					rightNode->prev = leftNode;
					free(deleteNode);
				}
				break;
			}
			curr = curr->next;
		}
		if(curr==NULL)
		{
			printf("Data %d is not found in the linked list\n", searchKey);
		}
	}
}

void printList()
{
	if (head==NULL)
	{
		printf("List kosong\n");
		return;
	}
	
	struct tnode *curr = head;
	
	while(curr!=NULL)
	{
		printf("%d ", curr->x);
		curr = curr->next;
	}
	printf("\n");
}

int main()
{
	printf("Linked list\n");
	
	push_front(13);
	printList();
	
	push_front(10);
	printList();
	
	push_back(1);
	printList();
	
	push_back(3);
	printList();
	
	push_mid(100, 1);
	printList();
	
	delete_front();
	printList();
	
	delete_back();
	printList();
	
	delete_mid(100);
	printList();
	
	delete_mid(1000);
	printList();
	
	return 0;
}

