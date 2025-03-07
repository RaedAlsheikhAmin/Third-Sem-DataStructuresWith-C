/*This is a header file created to add the functions needed to implement 
queue ADT to my main program.
This header file also contains the node declaration that is used to create
and implement a linked list inside my main program. 
I kept the node here because queue and linked list in our program have identical
elements and there is no need to declare another node to implement linked list of
packages.

This header file contains the following functions.

enqueue - to add the element to the rear of the queue
dequeue - to remove an element from the front of the queue
isempty - to check whether the queue is empty or not
*/
#include <stdio.h>
#include <stdlib.h>
struct node
{
	char imp;//importance
	int arrtime;//arrival time
	int sertime;//service time
	int serstime;//service start time
	int id;//employee id
	struct node *next;//next pointer
};
struct Queue
{
	struct node *front;
	struct node *rear;
};
typedef struct Queue *queue;//Declare Queue ADT as a pointer to have front and rear
void enqueue(queue q, struct node *temp)
{
	if(q->rear==NULL)
	{
		q->rear=(struct node*) malloc(sizeof(struct node));
		q->rear->imp=temp->imp;
		q->rear->arrtime=temp->arrtime;
		q->rear->sertime=temp->sertime;
		q->rear->serstime=temp->serstime;
		q->rear->id=temp->id;
		q->rear->next=NULL;
		q->front=q->rear;
		return;
	}
	q->rear->next=(struct node*) malloc(sizeof(struct node));
	q->rear=q->rear->next;
	q->rear->imp=temp->imp;
	q->rear->arrtime=temp->arrtime;
	q->rear->sertime=temp->sertime;
	q->rear->serstime=temp->serstime;
	q->rear->id=temp->id;
	q->rear->next=NULL;
}
int isempty(queue q)
{
	if(q->rear==NULL && q->front==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
struct node* dequeue(queue q)
{
	if(isempty(q))
	{
		printf("\nThe queue is empty\n");
		return q->front;
	}
	struct node *temp;
	struct node *val;
	temp=q->front;
	val=temp;
	if(q->front==q->rear)
	{
		q->rear=q->rear->next;
	}
	q->front=q->front->next;
	return val;
}
