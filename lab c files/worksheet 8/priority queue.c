#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

/*A Node declaration to store a value, pointer to the next node and a priority value*/
struct Node
{
        int priority;
        int val;
        struct Node *next;
};

/*Queue Record that will store the following:
  size: total number of elements stored in the list
  front: it shows the front node of the queue (front of the queue)
  rear: it shows the rare node of the queue (rear of the queue)*/
struct QueueRecord
{
        struct Node *front;   /* pointer to front of queue */
        struct Node *rear;    /* pointer to rear of queue */
        int size;             /* number of items in queue */
};

typedef struct QueueRecord *Queue;

Queue CreateQueue(int);
void MakeEmptyQueue(Queue);
int QueueSize(Queue);
int FrontOfQueue(Queue);
int RearOfQueue(Queue);
int IsEmptyQueue(Queue);
void DisplayQueue(Queue);
void InsertWithPriority(Queue,int,int);
void DeleteWithPriority(Queue);
int main()
{
    int queueSize;
    Queue myQueue;
    int exit, val, priority;
    char command;

    myQueue = CreateQueue(0);
    exit = FALSE;

    while (!exit)
    {
          fflush(stdin);
          printf("Menu:\n i)nitialize\n f)ront queue\n r)ear queue\n e)xit \nEnter command:");
          scanf("%c", &command);
          fflush(stdin);

          switch(command)
          {
                  case 'i':
                       MakeEmptyQueue(myQueue);
                       break;
                  case 'f':
                       val = FrontOfQueue(myQueue);
                       if (val != -1)
                          printf("front element is %d\n", val);
                       break;
                  case 'r':
                       val = RearOfQueue(myQueue);
                       if (val != -1)
                          printf("rear element is %d\n", val);
                       break;
                  case 'e':
                       exit = TRUE;
                       break;
                                  case 'p':
                                              InsertWithPriority(myQueue,4,1);
                                                InsertWithPriority(myQueue,3,2);
                                                InsertWithPriority(myQueue,2,2);
                                                break;
                                  case 'd':
                                               DeleteWithPriority(myQueue);
                                               break;

                  default:
                       printf("command not recognized\n");
                       break;
          }
          DisplayQueue(myQueue);

    }
    printf("\n\n");
    system("PAUSE");
    return 0;
}

/*This function initialises the queue*/
Queue CreateQueue(int maxElements)
{
        Queue q;

    q = (struct QueueRecord *) malloc(sizeof(struct QueueRecord));
    if (q == NULL)
        printf("Out of memory space\n");
    else
       MakeEmptyQueue(q);
    return q;
}

/*This function sets the queue size to 0, and creates a dummy element
and sets the front and rear point to this dummy element*/
void MakeEmptyQueue(Queue q)
{
        q->size = 0;
        q->front = (struct Node *) malloc(sizeof(struct Node));//because we have a dummy node
    if (q->front == NULL)
               printf("Out of memory space\n");
    else{
            q->front->next = NULL;
                q->rear = q->front;
    }
}

/*Shows if the queue is empty*/
int IsEmptyQueue(Queue q)
{
        return (q->size == 0);
}


/*Returns the queue size*/
int QueueSize(Queue q)
{
        return (q->size);
}

/*Returns the value stored in the front of the queue*/
int FrontOfQueue(Queue q)
{
    if (!IsEmptyQueue(q))
                return q->front->next->val;
    else
    {
        printf("The queue is empty\n");
            return -1;
    }
}

/*Returns the value stored in the rear of the queue*/
int RearOfQueue(Queue q)
{
        if (!IsEmptyQueue(q))
            return q->rear->val;
     else
     {
         printf("The queue is empty\n");
         return -1;
     }
}

/*Displays the content of the queue*/
void DisplayQueue(Queue q)
{
    struct Node *pos;

    pos=q->front->next;
    printf("Queue content:\n");

    printf("-->Priority   Value\n");
    while (pos != NULL)
    {
        printf("--> %d\t     %d\n", pos->priority, pos->val);
        pos = pos->next;
    }
}
void InsertWithPriority(Queue q,int val,int priority)
{
        struct Node *temp;
        temp=(struct Node *) malloc(sizeof(struct Node));
        temp->val=val;
        temp->priority=priority;
        temp->next=q->front->next;
        if(q->front->next==NULL)
        {
                q->rear=temp;
        }
        q->front->next=temp;
        q->size++;

}
void DeleteWithPriority(Queue q)
{
        struct Node *pos, *del;
        int min=1000;
        pos=q->front->next;
        while(pos!=NULL)
        {
                if(pos->priority<min)
                {
                        min=pos->priority;
                }
                pos=pos->next;
        }
        pos=q->front->next;
        if(pos->next==NULL)
        {
                q->front->next=NULL;
                q->size=0;
        }

        else
        {
                while(pos->next!=NULL)
                {
                        if(pos->next->priority==min)
                        {
                                del=pos->next;
                                pos->next=pos->next->next;
                                q->size--;
                                break;
                        }
                        pos=pos->next;
                }
        }
}
