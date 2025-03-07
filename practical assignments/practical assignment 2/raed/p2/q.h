#ifndef Q_H_INCLUDED
#define Q_H_INCLUDED



#endif // Q_H_INCLUDED
struct linkedlistq
{
    struct linkedlistq *next;
    char packetlabel;
    int arrivaltime;
    int servicetime;
    int servicestarttime;
    int employee;

};
struct queuerecord
{
    struct linkedlistq *front;
    struct linkedlistq *rear;
    int size;
};
typedef struct linkedlistq node;
typedef struct queuerecord queue;

void enqueue(queue *q, node *temp)
{
	if(q->rear==NULL)
	{
		q->rear=(node*)malloc(sizeof(node));
		if(q->rear==NULL)
        {
            printf("memory is not allocated succefully");
            exit(1);
        }
		q->rear->packetlabel=temp->packetlabel;
		q->rear->arrivaltime=temp->arrivaltime;
		q->rear->servicetime=temp->servicetime;
		q->rear->servicestarttime=temp->servicestarttime;
		q->rear->employee=temp->employee;
		q->rear->next=NULL;
		q->front=q->rear;
	}
	q->rear->next=(node*) malloc(sizeof(node));
	if(q->rear->next==NULL)
        {
            printf("memory is not allocated succefully");
            exit(1);
        }
	q->rear=q->rear->next;
	q->rear->packetlabel=temp->packetlabel;
	q->rear->arrivaltime=temp->arrivaltime;
	q->rear->servicetime=temp->servicetime;
	q->rear->servicestarttime=temp->servicestarttime;
	q->rear->employee=temp->employee;
	q->rear->next=NULL;
	q->size++;
}
int isempty(queue *q)
{
	if((q->rear==NULL && q->front==NULL )|| q->size==0)
		return 1;
    return 0;
}
node* dequeue(queue *q)
{
	if(isempty(q))
	{
		printf("\nThe queue is empty\n");
		return q->front;
	}
	node *temp;
	node *val;
	temp=q->front;
	val=temp;
	if(q->front==q->rear)
	{
		q->rear=q->rear->next;
	}
	q->front=q->front->next;
	q->size--;
	return val;
}



