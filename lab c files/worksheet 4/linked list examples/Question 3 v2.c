#include <stdio.h>
#include <stdlib.h>

struct Node{
	int val;
	struct Node* next;};

struct Node *BuildLinkedList(void);
void PrintList(struct Node *);

int main()
{
    struct Node * myList;
    myList = BuildLinkedList();
    PrintList(myList);
    printf("\n\n");
    return 0;
}

struct Node *BuildLinkedList(void)
{
	struct Node *tmp, *head=NULL, *last, *first;
	int num;
	char c;

	do
	{
	  	printf("Enter value to insert: ");
	  	scanf("%d",&num);

	  	tmp = (struct Node *) malloc(sizeof(struct Node));
	  	tmp->val = num;
	  	tmp->next = NULL;

	  	if (head == NULL) {
		    head = tmp;
		    first = last = tmp; }
	    else {
			last->next = tmp;
			last = tmp; }

		printf("Do you want to continue? (y/n): ");
		fflush(stdin);
		scanf("%c", &c);

	} while(c=='y');

	return head;
}

void PrintList(struct Node* p)
{
    while (p != NULL)
	{
		printf("address: %u \t val: %d \t next: %u \n", p, p->val, p->next);
		p = p->next;
	}
}









