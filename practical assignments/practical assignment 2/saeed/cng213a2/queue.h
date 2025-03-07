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

patient_queue* initialiseSimulator(vent *ventilator_array,int capactiy);

void newpatient(patient_queue* queueList,NODE* temp);

info serve_patient(patient_queue* queueList);

