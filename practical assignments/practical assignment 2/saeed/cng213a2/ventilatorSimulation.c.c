#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include"queue.h"

patient_listrecord* create_empty_listrecord()
{
    /*this function will create and return empty reocrd list and allocate the memory for head and assign tail to it*/
    patient_listrecord* list0;
    list0=(patient_listrecord *)malloc(sizeof(patient_listrecord));
    if(list0==NULL){printf("\nERROR couldn't create list");exit(1);}
    list0->head=(NODE *)malloc(sizeof(NODE));
    list0->head->next=NULL;
    list0->head->prev=NULL;
    list0->tail=list0->head;
    list0->size=0;
    return list0;
}
void swap(NODE *a, NODE *b)
{//function that will swap the p_info between the linked list
    info temp = a->p_info;
    a->p_info = b->p_info;
    b->p_info = temp;
}
void sort_linkedlist(patient_listrecord* PatientList)
{//this function is responsible for sorting the linked list
    NODE *temp1,*temp2;
    temp1=PatientList->head->next;
    while (temp1!=NULL)
    {
        temp2=temp1->next;
        while(temp2!=NULL)
        {
            if(temp1->p_info.arrivel_time>temp2->p_info.arrivel_time)
            {

                swap(temp1,temp2);
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }
}
void createPatientList(patient_listrecord* PatientList,int noOfPatients,int noOfVentilators,int maxArrivalTime,int maxServiceTime)
{
    /*This function  randomly create patients based on the input
    placing them in a linked list, patients should will be in a linked list in ascending order based on their arrival time using the function
    sort_linkedlist.*/
    srand(time(NULL));
    NODE* temp;

    for (;noOfPatients>0;noOfPatients--)
    {
        if (! (temp=(NODE*)malloc(sizeof(NODE)))) {
                printf("Unsuccessful memory allocation!");
                exit(1);
            }

        temp->p_info.arrivel_time=rand()%(maxArrivalTime)+1;
        temp->p_info.service_time=rand()%(maxServiceTime)+1;
        temp->p_info.patient_age_group=rand()%3;
        temp->p_info.patient_gender=rand()%2;
        temp->p_info.patient_type=rand()%3;
        temp->p_info.service_start_time=0;
        temp->p_info.ventilator_ID=0;
        temp->next=NULL;
        temp->prev=NULL;

        if (PatientList->head->next==NULL)
        {
            PatientList->head->next=temp;
            PatientList->tail=temp;
            PatientList->tail->next=NULL;
            PatientList->tail->prev=PatientList->head;
            (PatientList->size)++;
        }
        else
        {
                PatientList->tail->next=temp;
                temp->prev=PatientList->tail;
                PatientList->tail=temp;
                (PatientList->size)++;
        }
    }
    //after creating the function
    sort_linkedlist(PatientList);
}
void parseInput(char **arguments,int *noOfPatients,int *noOfVentilators,int *maxArrivalTime,int *maxServiceTime)
{
    /*This function  parse the input and set the
    values of the number of patients, the number of ventilators,
    the maximum arrival time and the maximum service time.*/
    //atoi change the string to an integer
    *noOfPatients=atoi(arguments[1]),
    *noOfVentilators=atoi(arguments[2]),
    *maxArrivalTime=atoi(arguments[3]),
    *maxServiceTime=atoi(arguments[4]);
}



void printlist(patient_listrecord* PatientList)
{
    NODE* first;
    first=PatientList->head->next;
    while(first!=NULL)
    {
        printf("\n%d %5d %5d %5d %5d %3d %3d",first->p_info.patient_type,first->p_info.arrivel_time,first->p_info.service_time,first->p_info.service_start_time,first->p_info.ventilator_ID,first->p_info.patient_gender,first->p_info.patient_age_group);
        first=first->next;
    }
}
int vent_not_empty(vent* ventilator_array,int index,int time_clock)
{
    /*this function will check if the ventilator is empty at a giving arrival time
    and return 1 if there is an available vent*/
    for(index--;index>=0;index--)
    {
        if(time_clock>=ventilator_array[index].final_time)
            {
                ventilator_array[index].ID=0;
                return 1;}
    }
    return 0;
}
int assign_ventilator(vent* ventilator_array,int noOfVentilators,NODE* temp)
{
    /*this function will randomly assign the patient to an available ventilator
    and update the vent final time with a new finishing time */
    int ID,index;
    while(1)
    {
        index=rand()%noOfVentilators;
        if(ventilator_array[index].ID==0)
        {
            ID=index;
            ventilator_array[index].ID=1;
            ventilator_array[index].final_time=temp->p_info.arrivel_time+temp->p_info.service_time;
            break;
        }
    }
    return ID+1;
}

int nearest_vent_ava(vent* ventilator_array,int size)
{
    //this function will return the nearest available time for a ventilator to be
    //available
    int min=ventilator_array[0].final_time;
    int i;
    for(i=1;i<size;i++)
    {
        if(ventilator_array[i].final_time<min)
            min=ventilator_array[i].final_time;
    }
    return min;
}

int assign_nearest_ventilator(vent* ventilator_array,int size)
{
    //this function will return the nearest available vent ID
    int min_idex=0;
    int min=ventilator_array[0].final_time;
    int i;
    for(i=0;i<size;i++)
    {
        if(ventilator_array[i].final_time<min)
            min_idex=i;
    }
    return min_idex+1;
}
void printqueue(patient_queue* queueList)
{
        NODE* first;
        first=queueList->front->next;
        while(first!=NULL)
        {
                    printf("\n%d %5d %5d %5d %5d %3d %3d",first->p_info.patient_type,first->p_info.arrivel_time,first->p_info.service_time,first->p_info.service_start_time,first->p_info.ventilator_ID,first->p_info.patient_gender,first->p_info.patient_age_group);
            first=first->next;
        }
}
void updateclock(vent* ventilator_array,int size,int time)
{
        //this function will update the availability of the ventilator an a giving arrival time
        int i=0;
        for(i=0;i<size;i++)
        {
            if(ventilator_array[i].final_time<time)
                ventilator_array[i].ID=0;
        }
}
void process(patient_queue* queueList,vent* ventilator_array,int noOfVentilators,patient_listrecord* PatientList,patient_listrecord* PatientList1)
{
    /*this function will first check the availabliy of the ventilator at a giving arrival time of the patient
    if the there is an empty vent it will just update the patient info and more it to another list
    then if no vent is available it will start the process of enqueue using new patient and it will keep enqueueing
    until the next patient arrival time is less than the nearest available time,next it will start dequeueing and
    updating the ventilator array final time to be checked by the next arrival time*/
    NODE* temp,*temp2;
    temp=PatientList->head->next;
    temp2=PatientList1->head->next;
    info p_info;

    printf("\n");
    while(temp!=NULL)
    {

        updateclock(ventilator_array,noOfVentilators,temp->p_info.arrivel_time);
        if(vent_not_empty(ventilator_array,noOfVentilators,temp->p_info.arrivel_time))
        {
            /*whenever we have an empty ventilator at a giving arrival time of the patient
              we wont need to dequeue so we just take the patient from one the first patient list to
              the other patient list and the patient info will be updated*/

            if (! (temp2=(NODE*)malloc(sizeof(NODE)))) {
                printf("Unsuccessful memory allocation!");
                exit(1);
                }
            temp->p_info.ventilator_ID=assign_ventilator(ventilator_array,noOfVentilators,temp);
            (ventilator_array[temp->p_info.ventilator_ID-1].noOFpatient)++;
            temp->p_info.service_start_time=temp->p_info.arrivel_time;
            temp2->p_info=temp->p_info;
            temp2->next=NULL;
            temp2->prev=PatientList1->tail;
            PatientList1->tail->next=temp2;
            PatientList1->tail=temp2;

        }
        else
        {
            /*if the ventilators aren't available then we start the process of queueing */
            newpatient(queueList,temp);
            //after having the first patient in the queue we can check for the next patient if there arrival time is also less than the nearest available ventilators
            while(queueList->size!=0)
            {
                if (temp->next!=NULL)
                    {

                         while((temp->next!=NULL) &&(temp->next->p_info.arrivel_time<nearest_vent_ava(ventilator_array,noOfVentilators)))
                        {
                            temp=temp->next;

                            newpatient(queueList,temp);

                            if (temp->next==NULL)
                                break;
                        }
                    }
                if (! (temp2=(NODE*)malloc(sizeof(NODE)))) {
                    printf("Unsuccessful memory allocation!");
                    exit(1);
                    }
                p_info=serve_patient(queueList);
                p_info.ventilator_ID=assign_nearest_ventilator(ventilator_array,noOfVentilators);
                (ventilator_array[(p_info.ventilator_ID)-1].noOFpatient)++;
                p_info.service_start_time=ventilator_array[p_info.ventilator_ID-1].final_time;
                ventilator_array[p_info.ventilator_ID-1].final_time=p_info.service_start_time+p_info.service_time;
                temp2->p_info=p_info;
                temp2->next=NULL;
                temp2->prev=PatientList1->tail;
                PatientList1->tail->next=temp2;
                PatientList1->tail=temp2;
            }
        }
        temp=temp->next;
    }

}
int find_compliTime(patient_listrecord* PatientList1)
{
    NODE* temp;
    temp=PatientList1->head->next;
    int max=0;
    while (temp != NULL)
    {
        if((temp->p_info.service_start_time+temp->p_info.service_time)>max)
            max=(temp->p_info.service_start_time+temp->p_info.service_time);
        temp=temp->next;
    }
    return max;
}
int find_totat_time(patient_listrecord* PatientList1)
{
    NODE* temp;
    temp=PatientList1->head->next;
    int total=0;
    while (temp != NULL)
    {
        total+=((temp->p_info.service_start_time)-(temp->p_info.arrivel_time));
        temp=temp->next;
    }
    return total;
}
int find_maxWAITINGtime(patient_listrecord* PatientList1)
{
    NODE* temp;
    temp=PatientList1->head->next;
    int max=0;
    while (temp != NULL)
    {
        if(((temp->p_info.service_start_time)-(temp->p_info.arrivel_time))>max)
            max=((temp->p_info.service_start_time)-(temp->p_info.arrivel_time));
        temp=temp->next;
    }
    return max;
}
int find_Mostgenderusage(patient_listrecord* PatientList1)
{
    NODE* temp;
    temp=PatientList1->head->next;
    int gender[2];
    gender[0]=0;
    gender[1]=0;
    while (temp != NULL)
    {
        if(temp->p_info.patient_gender==0)
            gender[0]++;
        else
            gender[1]++;
        temp=temp->next;
    }

    if (gender[0]>gender[1])
        return 0;
    else if (gender[0]<gender[1])
        return 1;
    else
        return 2;
}
int find_Mage(patient_listrecord* PatientList1)
{
    NODE* temp;
    temp=PatientList1->head->next;
    int max=0,ageGroup[3],i;
    ageGroup[0]=0;ageGroup[1]=0;ageGroup[2]=0;
     while (temp != NULL)
    {
        switch (temp->p_info.patient_age_group)
        {
        case 0:
            {
                ageGroup[0]++;
                break;
            }
        case 1:
            {
                ageGroup[1]++;
                break;
            }
        case 2:
            {
                ageGroup[2]++;

            }
        }
        temp=temp->next;
    }

    for (i=0;i<3;i++)
    {
        if(ageGroup[max]<=ageGroup[i])
            max=i;
    }

    return max;
}
void reportStatistics(int noOfPatients,int noOfVentilators,vent* ventilator_array,patient_listrecord* PatientList1)
{
    /*this function is responsible for printing out all the information*/

    int patient_typeCOUNTER[3],Completion_time,totalTime,maxwaitngT,Most_gender,Most_age,i;
    float avgtime;
    for (i=0;i<3;i++)
    {
        patient_typeCOUNTER[i]=0;
    }
    NODE* temp;
    temp=PatientList1->head->next;
    while (temp!=NULL)
    {
        switch (temp->p_info.patient_type)
        {
        case 0:
            {
                patient_typeCOUNTER[0]++;
                break;
            }
        case 1:
            {
                patient_typeCOUNTER[1]++;
                break;
            }
        default:
            {
                patient_typeCOUNTER[2]++;
            }
        }
        temp=temp->next;
    }

    Completion_time=find_compliTime(PatientList1);
    totalTime=find_totat_time(PatientList1);
    avgtime=(totalTime*1.0)/(noOfPatients*1.0);
    maxwaitngT=find_maxWAITINGtime(PatientList1);
    Most_gender=find_Mostgenderusage(PatientList1);
    Most_age=find_Mage(PatientList1);
    printf("\n****************Report*****************\n");
    printf("Enter the number of Patients: %d\n",noOfPatients);
    printf("Enter the number of Ventilators: %d\n",noOfVentilators);
    printf("Number of patients for each patient type:\n");
    printf("\tsevere: %d\n\tmoderate: %d\n\tmild: %d\n",patient_typeCOUNTER[0],patient_typeCOUNTER[1],patient_typeCOUNTER[2]);
    printf("Completion time: %d\n",Completion_time);
    printf("Average time spent in the queue: %.1f\n",avgtime);
    printf("Maximum waiting time: %d\n",maxwaitngT);
    printf("Most gender usage: ");
    if (Most_gender==0)
        printf("male");
    else
        printf("female");
    printf("\nMost age usage: ");
    switch (Most_age)
    {
    case 0:
        {
            printf("Young");
            break;
        }
    case 1:
        {
            printf("Adult");
            break;
        }
    case 2:
        {
            printf("Elderly");
        }
    }
}
int main(int argc,char **argv)
{
    int noOfPatients,noOfVentilators,maxArrivalTime,maxServiceTime;

    /*the ventilator array will keep track of the availability ,final time of being busy and also how many times it has been used
    it will be created dynimally with the size of noOfVentilators */
    vent *ventilator_array;

    patient_listrecord* PatientList,* PatientList1;

    /*creating 2 record list PatientList will hold the linked list before we process the patient and the other one is after we process it*/
    patient_queue* queueList;

    /*queueList will be used to for organinzing the queue
     create and empty record list for 2 patient list */
    PatientList=create_empty_listrecord();

    PatientList1=create_empty_listrecord();

    parseInput(argv,&noOfPatients,&noOfVentilators,&maxArrivalTime,&maxServiceTime);

    createPatientList(PatientList ,noOfPatients ,noOfVentilators , maxArrivalTime ,maxServiceTime);

    printlist(PatientList);

    ventilator_array=(vent *)malloc(noOfPatients*sizeof(vent));

    queueList=initialiseSimulator(ventilator_array,noOfVentilators);

    process(queueList,ventilator_array,noOfVentilators,PatientList,PatientList1);

    printlist(PatientList1);

    reportStatistics(noOfPatients, noOfVentilators, ventilator_array, PatientList1);

    free(ventilator_array);
    free(queueList);
    free(PatientList);
    free(PatientList1);
    printf("\nend");
    return 0;
}
