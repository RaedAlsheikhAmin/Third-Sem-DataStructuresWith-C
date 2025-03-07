//
//  main.c
//  PackagesDeliveryServiceSimulator
//
//  Created by Farnaz Rezaee No'ee on 12/8/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node
{
    char label;
    int Atime;
    int Stime;
    int SStime;
    int employee;
    int Priority;
    struct Node *next;
    struct Node *prev;
};

struct Employee
{
    int availability;
    int freetime;
};

struct ListRecord
{
    struct Node *head;
    struct Node *last;
    int size;
};

struct QueueRecord
{
    struct Node *front;
    struct Node *rear;
    int size;
};

typedef struct ListRecord *List;
typedef struct QueueRecord *QueueList;

void ParseInput(char *[], int *, int *, int *, int *);
List CreatePackageList(List, int , int , int , int );
void InitialiseSimulator(QueueList, struct Employee *, int );
void NewPackage(List, QueueList);
List deliverPackage(struct Employee *, int, int, int , QueueList, List);
void ReportStatistics(int , int , List, int);

// Extra Functions I made due to the need of my code
List CreateEmptyList(List);
QueueList CreateEmptyQueue(QueueList);


int main (int argc, char *argv[])
{
    List Packages, delivered;

    QueueList Queue;

    struct Employee *E;
	int numberP, numberE, maxArrival, maxService, clock = 0, End = 0, available, j;
    srand(time(NULL));

    Packages = CreateEmptyList(Packages);

    delivered = CreateEmptyList(delivered);
    ParseInput(argv, &numberP, &numberE, &maxArrival, &maxService);

    Packages = CreatePackageList (Packages, numberP, numberE, maxArrival, maxService);

    InitialiseSimulator(Queue, E, numberE);

    while(End != 1)
    {
        available = 0;
        if(Packages->head->Atime == clock)
        {
            NewPackage(Packages, Queue);
        }

        for(j = 0; j < numberE; j++)
        {
            available += E[j].availability;
        }

        if(Queue->size != 0 && available != 0)
        {
            delivered = deliverPackage(E, clock, available, numberE, Queue, delivered);
        }
        clock++;
    }


    ReportStatistics(numberE, numberP, delivered, clock);

    return 0;
}


void ParseInput( char *argv[], int *numberP, int *numberE, int *maxArrival, int *maxService)
{
    *numberP = atoi(argv[1]);
    *numberE = atoi(argv[2]);
    *maxArrival = atoi(argv[3]);
    *maxService = atoi(argv[4]);
}

List CreatePackageList(List Packages, int numberP, int numberE, int maxArrival, int maxService)
{
    int i, inserted = 0;

    struct Node *t;
    for(i = 1; i <= numberP; i++)
    {
        struct Node *tmp;
        tmp = (struct Node *) malloc (sizeof(struct Node));

        tmp->Atime = rand() % maxArrival;

        tmp->Stime = rand() % maxService;

        tmp->Priority = 1 + rand() % 4;

        tmp->employee = 0;

        tmp->SStime = 0;

        if(Packages->head->next == NULL)
        {
            Packages->head->next = tmp;
            tmp->prev = Packages->head;
            tmp->next = NULL;
            Packages->last = tmp;
            Packages->size++;
            inserted = 1;
        }

        else
        {
            for(t = Packages->head->next; t != NULL; t = t->next)
            {
                if(tmp->Atime < t->Atime)
                {
                    tmp->next = t;
                    t->prev->next = tmp;
                    tmp->prev = t->prev;
                    t->prev = tmp;
                    Packages->size++;
                    inserted = 1;
                }
            }
        }

        if(inserted == 0)
        {
            Packages->last->next = tmp;
            tmp->prev = Packages->last;
            tmp->next = NULL;
            Packages->last = tmp;
            Packages->size++;
        }
    }
    return Packages;
}


void InitialiseSimulator(QueueList Queue, struct Employee *E, int Employeenum)
{
    int i;

    Queue = CreateEmptyQueue(Queue);

    E = (struct Employee *) malloc (sizeof(struct Employee)*(Employeenum));
    if(E==NULL)
    {
        printf("memory is not allocated");
        exit(1);
    }

    for(i = 0; i < Employeenum; i++)
    {
        E[i].availability = 1;
        E[i].freetime = 0;
    }
}


void NewPackage(List Packages, QueueList Queue)
{
    int inserted = 0;
    struct Node *tmp, *t, *traverse;
    t = Packages->head->next;

    tmp = (struct Node *) malloc (sizeof(struct Node));
    if(tmp == NULL)
    {
        printf("Out of memory!");
        exit(1);
    }

    tmp->Atime = t->Atime;
    tmp->Priority = t->Priority;
    tmp->Stime = t->Stime;
    tmp->SStime = 0;
    tmp->employee = 0;

    if(Queue->front->next == NULL)
    {
        Queue->front->next = tmp;
        tmp->next = NULL;
        tmp->prev = Queue->front;
        Queue->size++;
        Queue->rear = tmp;
        inserted = 1;
    }
    else
    {
        for(traverse = Queue->front->next; traverse != NULL; traverse = traverse->next)
        {
            if(tmp->Atime > traverse->Atime)
            {
                tmp->next = traverse;
                traverse->prev->next = tmp;
                tmp->prev = traverse->prev;
                traverse->prev = tmp;
                Queue->size++;
                inserted = 1;
            }
        }
    }
    if(inserted == 0)
    {
        Queue->rear->next = tmp;
        tmp->prev = Queue->rear;
        tmp->next = NULL;
        Queue->rear = tmp;
        Queue->size++;
    }
    if(t == Packages->last)
    {
        Packages->head->next = NULL;
        Packages->last = Packages->head;
        t->prev = NULL;
        Packages->size--;
        free(t);
    }
    else
    {
        Packages->head->next = t->next;
        t->next->prev = Packages->head;
        t->next = NULL;
        t->prev = NULL;
        Packages->size--;
        free(t);
    }
}


List deliverPackage(struct Employee *E, int clock, int available, int numberE, QueueList Queue, List delivered)
{

    int i, x;

    struct Node *tmp, *t;

    t = Queue->front->next;

    tmp = (struct Node*) malloc (sizeof(struct Node));

    tmp->Atime = t->Atime;
    tmp->Priority = t->Priority;
    tmp->Stime = t->Stime;
    tmp->SStime = clock;
    tmp->employee = 0;


    if(t == Queue->rear)
    {
        Queue->front->next = NULL;
        Queue->rear = Queue->front;
        t->prev = NULL;
        Queue->size--;
        free(t);
    }
    else
    {
        Queue->front->next = t->next;
        t->next->prev = Queue->front;
        t->next = NULL;
        t->prev = NULL;
        Queue->size--;
        free(t);
    }


    if(delivered->head->next == NULL)
    {
        delivered->head->next = tmp;
        tmp->prev = delivered->head;
        tmp->next = NULL;
        delivered->last = tmp;
        delivered->size++;
    }
    else
    {
        delivered->last->next = tmp;
        tmp->prev = delivered->last;
        delivered->last = tmp;
        delivered->size++;
    }


    if(available == numberE)
    {
        tmp->employee = rand() % numberE;
    }
    else if(available == (numberE-1))
    {
        for(i = 0; i < numberE; i++)
        {
            if(E[i].availability == 1)
            {
                tmp->employee = i;
            }
        }
    }
    else
    {
        while(tmp->employee == 0)
        {

            x = rand() % numberE;
            if(E[x].availability == 1)
            {
                tmp->employee = x;
            }
        }
    }



    return delivered;
}


void ReportStatistics(int numberE, int numberP, List delivered, int clock)
{
    int R = 0, O = 0, Y = 0, G = 0, i;
    float wait = 0;
    struct Node *t;
    int *Ecount;

    Ecount = (int *) malloc (sizeof(int) * (numberE));

    for(i = 0; i <numberE; i++)
    {
        Ecount[i] = 0;
    }

    printf("****************Report*****************\n");
    printf("The number of employees: %d\n", numberE);
    printf("The number of packages: %d\n", numberP);

    for(t = delivered->head->next; t != NULL; t = t->next)
    {
        if(t->Priority == 4)
        {
            R++;
        }
        else if(t->Priority == 3)
        {
            O++;
        }
        else if(t->Priority == 2)
        {
            Y++;
        }
        else if(t->Priority == 1)
        {
            G++;
        }

        wait += (t->SStime - t->Atime);

        Ecount[t->employee]++;
    }

    printf("Number of packages for each package type:\n");
    printf("\tRed: %d\n\tOrange: %d\n\tYellow: %d\n\tGreen: %d\n", R, O, Y, G);

    printf("Number of packages for each Employee:\n");
    for(i = 0; i < numberE; i++)
    {
        printf("\tEmployee %d: %d\n", i+1, Ecount[i]);
    }

    printf("Completion time: %d\n", clock);

    printf("Average time spent in the queue: %.1f\n", wait/(numberP));


}


List CreateEmptyList(List Listname)
{
    Listname = (List) malloc (sizeof(struct ListRecord));

    if(Listname == NULL)
    {
        printf("Out of memory!");
        exit(1);
    }

    Listname->head = (struct Node*) malloc(sizeof(struct Node));

    if(Listname->head == NULL)
    {
        printf("Out of memory!");
        exit(1);
    }

    Listname->head->next = NULL;
    Listname->head->prev = NULL;

    Listname->last = Listname->head;

    Listname->size = 0;

    return Listname;
}

QueueList CreateEmptyQueue(QueueList Queuename)
{
    Queuename = (QueueList) malloc (sizeof(struct QueueRecord));

    if(Queuename == NULL)
    {
        printf("Out of memory!");
        exit(1);
    }

    Queuename->front = (struct Node*) malloc(sizeof(struct Node));

    if(Queuename->front == NULL)
    {
        printf("Out of memory!");
        exit(1);
    }

    Queuename->front->next = NULL;
    Queuename->front->prev = NULL;

    Queuename->size = 0;

    Queuename->rear = Queuename->front;

    return Queuename;
}
