#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include "q.h"


void parseInput(char **,int *,int *,int *,int *);//is going to change the input from string to integer
node * createpackagelist(node *,int,int,int,int);//is going to create a package list based on the arrival time
int * initialiseSimulator(queue *,int);//is going to make empty queue and array for the employee
node* newpackage(queue *,node*);//is going to add the package from the list to the queue
node* deliverPackage(queue *, node*,int );//is going to assign a package to the employee from the queue
void reportStatistics(node*,int,int*,int*,int,int,int);//is going to report some calculations
int main(int argc, char *argv[])
{
    srand(time(NULL));//to change the random values based on system time.
    int packagenum=0,employeenum=0,maxarrivaltime=0,maxservicetime=0;
    node *mylist;//creating my list node
    parseInput(argv,&packagenum,&employeenum,&maxarrivaltime,&maxservicetime);//sending the strings with addresses to change them to integers
    mylist=(node*)malloc(sizeof(node));//allocate memory to my list
    mylist->next=NULL;
    mylist=createpackagelist(mylist,packagenum,employeenum,maxarrivaltime,maxservicetime);//creating a list and assiging it to my list in the main
    node *temp=mylist;//creating temporary variable to hold my list not to lose it later
    /*for(temp;temp!=NULL;temp=temp->next)//it should be deleted
    {
        printf("%c %d %d\n",temp->packetlabel,temp->arrivaltime,temp->servicetime);
    }*/
    temp=mylist;
    queue *q;//declaring my queue
    q=(queue*)malloc(sizeof(queue));//allocating memory to my queue
     if(q==NULL)//checking if the memory allocation is done or not
    {
        printf("memory is not allocated correctly");
        exit(1);
    }
    int *emparray;//this is going to hold my employee info whether they are busy or free.
    emparray=initialiseSimulator(q,employeenum);//calling the function and assiging the return value to the employee array
    int time=0,i,j,*startt,waitingtime=0,totalwaitingtime=0,*employeepackage,*servicet,arrivalt=0,busycheck=0,*maxwaiting;
    employeepackage=(int*)malloc(sizeof(int)*employeenum);//to check how many package each employee delivered
    if(employeepackage==NULL)//checking memory allocation
    {
        printf("memory not allocated correctly");
        exit(1);
    }
    for(i=0;i<employeenum;i++)//assigning the values to zero
    {
        employeepackage[i]=0;
    }
    servicet=(int*)malloc(sizeof(int)*employeenum);//this array is going to hold my service time for each employee
    if(servicet==NULL)//checking memory allocation
    {
        printf("memory not allocated correctly");
        exit(1);
    }
    for(i=0;i<employeenum;i++)//assiging servicetime at the beginning to zero(not necessary i guess)
    {
        servicet[i]=0;
    }
    maxwaiting=(int*)malloc(sizeof(int)*packagenum);//this is going to hold the values from waiting time that i can use it later to find the maximum waiting time.
    if(maxwaiting==NULL)
    {
        printf("memory not allocated correctly");
        exit(1);
    }
    for(i=0;i<packagenum;i++)//intializing the values to zero
    {
        maxwaiting[i]=0;
    }
    startt=(int*)malloc(sizeof(int)*employeenum);//this is going to hold each start working time for each employee
    if(startt==NULL)
    {
        printf("memory not allocated correctly");
        exit(1);
    }
    for(i=0;i<employeenum;i++)
    {
        startt[i]=0;
    }
    while(!isempty(q) || temp!=NULL)//this loop works if my list is not empty or my q is not empty
    {
        for(i=0;i<employeenum;i++)//this is going to check all the employeenum
        {
            if(time>=temp->arrivaltime && emparray[i])//this checks if time is bigger or equal to the arrival time of some packages and the emplyee is free
            {
                emparray[i]=0;//setting the employee to be busy
                employeepackage[i]++;//incrementing the value of this will let us know how manytimes this employee delivered packages
                startt[i]=time;//this is the starting time for each package
                servicet[i]=temp->servicetime;//servicetime for each package
                arrivalt=temp->arrivaltime;//arrivaltime that i can calculate the waiting time.
                waitingtime=startt[i]-arrivalt;
                maxwaiting[j]=waitingtime;//this will help me to report the max waiting time later in the report function
                j++;
                totalwaitingtime+=waitingtime;
                temp=temp->next;//moving in the list
                if(temp==NULL){//this condition to stop my list if i reach the end
                    break;
                }

                   /* if(emparray[i]==0)this condition to stop my list and start using queue
                    {
                        busycheck++;
                    if(busycheck==employeenum)
                       {
                        temp=NULL;
                       }
                    }*/
            }
        }
        for(i=0;i<employeenum;i++){

            if(startt[i]+servicet[i]==time && !emparray[i])//checking if the starting time for that emplyee and servicetime for that package is equal to the time and employee is busy that mean the job is done
            {
                emparray[i]=1;//job is done employee is free again
                time--;//decrementing the time because it is going to increase after this
            }
        }
        time++;//incrementing the time for each 1 = minute

    }
    time--;//because the time will increase for the last time

reportStatistics(mylist,packagenum,employeepackage,maxwaiting,totalwaitingtime,time,employeenum);//this function will take multiple parameter to display the report

    return 0;
}

void parseInput(char *argv[],int *packagenum,int *employeenum,int *maxarrivaltime,int *maxservicetime)//this function will take the arguement from the command line and use the input directly.
{
    *packagenum=atoi(argv[1]);//using atoi function to change the data from string to integer.
    *employeenum=atoi(argv[2]);//using atoi function to change the data from string to integer.
    *maxarrivaltime=atoi(argv[3]);//using atoi function to change the data from string to integer.
    *maxservicetime=atoi(argv[4]);//using atoi function to change the data from string to integer.

}
node *createpackagelist(node *mylist,int packagenum,int employeenum,int maxarrivaltime,int maxservicetime)
{
    node *last=mylist;//last is going to be my temp but will point to the last node.

    int i=0;
    int label;

    while(i<packagenum)//RANDOMISING THE LABELS ACCORDING TO THE PRIORITY
    {
        label=1+rand()%4;
        if(label==4)
            last->packetlabel='R';
        else if(label==3)
            last->packetlabel='O';
        else if(label==2)
            last->packetlabel='Y';
        else if(label==1)
            last->packetlabel='G';

    last->arrivaltime=1+rand()%maxarrivaltime;//we add one because the formula is a+rand()%a+b-1
    last->servicetime=1+rand()%maxservicetime;
    last->employee=0;
    last->servicestarttime=0;
        if(i==packagenum-1)//to avoid creating not needed node.
        {
            last->next=NULL;
            break;

            }

    last->next=(node*)malloc(sizeof(node));//to create node and connect them;
    last=last->next;
    i++;

    }
    //this loop will help me to change the values of arrival time that i can sort them.
    node *sort=mylist;//this will be equal to min in selection sort.
    last=mylist;
    int temp1,temp2;
    char templabel;
    while(sort!=NULL)//this sorting is going to compare the first value with everything, then moving forward.
        {
            last=sort;
            while(last->next!=NULL)
            {
                if(sort->arrivaltime >(last->next->arrivaltime))//here the swapping is going to happen.
                {
                    temp1=sort->arrivaltime;
                    sort->arrivaltime=last->next->arrivaltime;
                    last->next->arrivaltime=temp1;
                    temp2=sort->servicetime;
                    sort->servicetime=last->next->servicetime;
                    last->next->servicetime=temp2;
                    templabel=sort->packetlabel;
                    sort->packetlabel=last->next->packetlabel;
                    last->next->packetlabel=templabel;

                }
            last=last->next;
            }
            sort=sort->next;


        }


 return mylist;

}

int * initialiseSimulator(queue *q,int employeenum)
{
    int i, *emparray;//declaring an array pointer to hold my employee
    q->front=NULL;
    q->rear=NULL;
    q->size=0;
    emparray=(int*)malloc(sizeof(int)*employeenum);//allocating memory according to the employee number
    if(emparray==NULL)
    {
        printf("not allocated for the array");
        exit(1);
    }
    for(i=0;i<employeenum;i++)
    {
        emparray[i]=1;
    }
    return emparray;//returning my array of employee


}
node* newpackage(queue *q,node* mylist)
{
    node *temp=mylist;
    q->front=temp;
    return q;
}

node* deliverPackage(queue *q, node *mylist,int packagenum)
{
    node *temp=mylist;
    temp->employee=1;
    for(temp;temp!=NULL;temp=temp->next)
    {
        if(temp->employee==temp->next->employee)
        {
            temp->next->employee=temp->employee+1;
        }
    }
    return mylist;

}

void reportStatistics(node *mylist,int packagenum,int *employeepackage,int *maxwaiting,int totalwaitingtime,int time,int employeenum)
{
    node *temp=mylist;
    printf("****************Report*****************\n");
    printf("*The number of Delivery Employees: %d\n",employeenum);
    printf("*The number of Packages: %d\n",packagenum);

    int red=0,orange=0,yellow=0,green=0,i;
    float averagetime;
    for(temp;temp!=NULL;temp=temp->next)
    {
        if(temp->packetlabel=='R')
            red++;
        else if(temp->packetlabel=='O')
            orange++;
        else if(temp->packetlabel=='Y')
            yellow++;
        else if(temp->packetlabel=='G')
            green++;
    }
    printf("*Number of Packages for each Package Label:\n\tRed: %d\n\tOrange: %d\n\tYellow: %d\n\tGreen: %d\n",red,orange,yellow,green);
    printf("*Number of packages for each Delivery Employee:\n");
    for(i=0;i<employeenum;i++)
    {
        printf("\tDelivery Employee %d delivered: %d\n",i+1,employeepackage[i]);
    }
    printf("*Completion time: %d\n",time);
    averagetime=totalwaitingtime*1.0/packagenum*1.0;
    printf("*Average time spent in the queue: %.2f\n",averagetime);

    int findmax;
    findmax=maxwaiting[0];//finding the maxwaiting time using iteration inside the array
    for(i=0;i<packagenum;i++)
    {
        if(findmax<maxwaiting[i])
            findmax=maxwaiting[i];
    }
    printf("*Maximum waiting time: %d",findmax);


}
