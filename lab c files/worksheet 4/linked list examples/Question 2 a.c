#include <stdio.h>
#include <stdlib.h>

struct Node{
	int val;
	struct Node* next;};

struct Node *BuildLinkedList(void);
void PrintList(struct Node *);

int main()
{
    struct Node *L1, *L2;

    printf("\nL1: \n");
    L1 = BuildLinkedList();
    printf("\nL2: \n");
    L2 = BuildLinkedList();

	printf("\nL1    :");
    PrintList(L1);
	printf("\nL2    :");
    PrintList(L2);

    printf("\nL1=L2:");
    L1=L2;
	printf("\nL1    :");
    PrintList(L1);
	printf("\nL2    :");
    PrintList(L2);

    printf("\n\n");
    return 0;
}

struct Node *BuildLinkedList(void)
{
	struct Node *tmp, *head=NULL, *last;

	int num;
	char c;

	do
	{
	  	printf("Enter value to insert: ");
	  	scanf("%d",&num);

	  	tmp = (struct Node *) malloc(sizeof(struct Node));
	  	tmp->val = num;
	  	tmp->next = NULL;

	  	if (head == NULL)
		{
		    head = tmp;
		    last = tmp;
		}
	    else
		{
			last->next = tmp;
			last = tmp;
		}

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
		printf(" %d -->",p->val);
		p = p->next;
	}
	printf("\n");
}





