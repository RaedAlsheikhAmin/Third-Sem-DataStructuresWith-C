#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct patient_information
{
    int patient_type;//
    int arrivel_time;
    int service_time;
    int service_start_time;
    int ventilator_ID;
    int patient_gender;
    int patient_age_group;
}info;

typedef struct node
{
    info p_info;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct vent_info
{
    int ID;
    int final_time;
    int noOFpatient;
}vent;
typedef struct queue
{
    NODE* front;
    NODE* rear;
    int size;
}patient_queue;

typedef struct LISTrecord
{
    NODE* head;
    NODE* tail;
    int size;
}patient_listrecord;



patient_queue* initialiseSimulator(vent *ventilator_array,int capactiy)
{
    /*This function  create an empty queue, and also an structure array to keep the availability of the ventilators.
    finishing time and number of time used*/
    patient_queue* Q;int i;
    Q=(patient_queue *)malloc(sizeof(patient_queue));
    if (Q==NULL){printf("\nERROR COULDNT CREATE QUEUE");exit(1);}
    Q->front=(NODE *)malloc(sizeof(NODE));
    if (Q->front==NULL){printf("\nERROR COULDNT CREATE QUEUE");exit(1);}

    Q->front->next=NULL;
    Q->front->prev=NULL;
    Q->rear=Q->front;
    Q->size=0;
    for(i=0;i<capactiy;i++)
    {
        ventilator_array[i].ID=0;
        ventilator_array[i].final_time=0;
        ventilator_array[i].noOFpatient=0;
    }
    return Q;
}

void newpatient(patient_queue* queueList,NODE* temp)
{
        /* this function is responsible in en queuing the patient to the queue */
        NODE* queue1,*current;
        int check=0;
        if (! (queue1=(NODE*)malloc(sizeof(NODE)))) {
                printf("Unsuccessful memory allocation!");
                exit(1);
            }

        queue1->p_info=temp->p_info;
        if (queueList->size==0)
        {
            queue1->next=NULL;
            queue1->prev=queueList->front;
            queueList->front->next=queue1;
            queueList->rear=queue1;
            (queueList->size)++;
        }
        else
        {
            current=queueList->front->next;


            while(current!=NULL)
            {

                if(queue1->p_info.patient_type<current->p_info.patient_type)
                {
                     queue1->prev=current->prev;
                     current->prev->next=queue1;
                     queue1->next=current;
                     current->prev=queue1;
                     check=1;
                }
                else if(check==0)
                {
                    queueList->rear->next=queue1;
                    queue1->prev=queueList->rear;
                    queueList->rear=queue1;
                    queueList->rear->next=NULL;
                }
                if (check==1)break;
                current=current->next;
            }
            (queueList->size)++;

        }
}

info serve_patient(patient_queue* queueList)
{
    //this function will dequeue from the queue and return the info of the patiend
    info p_info;
    (queueList->size)--;
    p_info=queueList->front->next->p_info;
    queueList->front->next=queueList->front->next->next;
    if (queueList->size!=0)
        queueList->front->next->prev=queueList->front;


    return p_info;
}

