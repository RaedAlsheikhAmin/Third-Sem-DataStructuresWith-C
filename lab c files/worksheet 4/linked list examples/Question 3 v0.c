//Note that you are not allowed to use global declarations!!!

#include <stdio.h>
#include <stdlib.h>

struct Node{
	int element;
	struct Node* next;};

struct Node *first,*last,*L;
int length;

void makeempty(void) {
	struct Node * tmp;
	tmp = (struct Node *) malloc(sizeof(struct Node));
	tmp->next = NULL;
	L = tmp; first = last = NULL;
}

void create(void) {

	int num; char c;
	do
	{
	  	printf("Enter value to insert: ");
	  	scanf("%d",&num);

		struct Node * tmp;
		tmp = (struct Node *) malloc(sizeof(struct Node *));
		tmp->element = num;
		tmp->next = NULL;

		if (L->next == NULL) {
			L->next = tmp;
			first = last = tmp; }
		else {
			last->next = tmp;
			last = tmp; }

		printf("Do you want to continue? (y/n): ");
		fflush(stdin);
		scanf("%c", &c);
	} while(c=='y');




}

void display(void) {
	struct Node * t;
	for(t=L->next; t!=NULL; t=t->next)
		printf("%d --> ", t->element);
}

int main()
{

	makeempty();
	create();
	display();


	return 0;
}








