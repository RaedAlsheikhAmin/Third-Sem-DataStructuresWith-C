//Muhammad Amin Guluzade ID : 2545952 Practical assignment 2

//Important remark regarding node declaration:
/*queue and package list have identical elements in them, so in this program
I used the node that I created in queue.h for creating a package list */

/*
Functions of this program and what they do:

"parseinput" function

Input : input from command line, address of packages number, address of employees number,
address of maximum arrival time, and address of maximum service time.
It transforms the command line input into integers and then uses the addresses
passed to it in order to store those integers in the main function.

"createpackagelist" function

Creates linked list of packages based on the restriction from command line.

"initialiseSimulator" function

Takes the number of employees and creates an array of employees and sets all to available.
Also, creates an empty queue.

"newpackage" function

Every time this function is called, it takes one package from linked list of packages
and adds to the queue based on the priority of the package. So, queue is modified
to have correct order of packages based on their priorities in this function.

"deliverPackage" function

Takes the id of employee who was available to deliver the package.
Takes the time when this package was started to be served by that employee.
Takes the head of the linked list of packages to modify it, in particular,
assign the id of employee who handles particular package and assign the 
service start time to that package.

"report" function

It takes all of the data that is needed to be reported to the user and 
using this data it calculates each employee's number of delivered packages
and the number of package of each label. Everything else is ready to be displayed.
After this, it displays the data as the report.

"whoisfree" function

This is an additional function I created to know whether there are available 
employees and if there are, I receive the id of available employee from this
function.

"whoisbusy" function

This is an additional function I created to know whether some employee is busy
and if there is a busy one, I received the id of that employee.


*/
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <time.h>
void parseinput(int,char*[],int*,int*,int*,int*);
struct node* createpackagelist(struct node*,int,int,int);
int* initialiseSimulator(int,queue);
struct node* newpackage(queue,struct node*);
struct node* deliverPackage(struct node*,int,struct node*,int);
void report(int,int,struct node*,int,float,int);
int whoisfree(int*,int);
int whoisbusy(int*,int);
int main(int argc, char *argv[])
{
	srand(time(NULL));
	queue q;//queue is declared and memory is allocated to it
	q=(struct Queue*) malloc(sizeof(struct Queue));
	q->front=NULL;
	q->rear=NULL;
	int packnum,empnum,maxartime,maxsertime,*array;//array - array of employees
	parseinput(argc,argv,&packnum,&empnum,&maxartime,&maxsertime);
	struct node *head,*head2;
	//head - to create a linked list
	//head2 - to keep the head of the linked list
	//head2 is needed because "newpackage" function, when taking the package from the list,
	//moves the head one step forward. So, head2 is needed to preserve the entire linked list.
	struct node *temp;//to traverse the linked list of packages
	struct node *temp2;//to receive a package from dequeue function when the package is served by available employee
	temp2=NULL;
	head=(struct node*) malloc(sizeof(struct node));
	head->next=NULL;
	head=createpackagelist(head,packnum,maxartime,maxsertime);//linked list of packages created using head
	array=initialiseSimulator(empnum,q);//empty queue and array of employees are created
	head2=head;//head2 is assigned to head to not lose the linked list of packages
	temp=head2;//temp is assigned to constant head2 to traverse linked list of packages properly
	int time=0,totwait=0,empty=-1,i=0,indx=-1,busy=-1,maxwait=0;
	int *timearr,*timeser,*wait;
	//Arrays to keep time arrived, time served and waiting time
	//for each employee, based on the index of the array (id of employee - 1)
	timearr=(int*) malloc(sizeof(int)*empnum);//memory allocation
	if(timearr==NULL)
	{
		printf("Memory allocation failure.");
		exit(1);
	}
	while(i<empnum)
	{
		*(timearr+i)=0;
		i++;
	}
	i=0;
	timeser=(int*) malloc(sizeof(int)*empnum);
	if(timeser==NULL)
	{
		printf("Memory allocation failure.");
		exit(1);
	}
	while(i<empnum)
	{
		*(timeser+i)=0;
		i++;
	}
	i=0;
	wait=(int*) malloc(sizeof(int)*empnum);
	if(wait==NULL)
	{
		printf("Memory allocation failure.");
		exit(1);
	}
	while(i<empnum)
	{
		*(wait+i)=0;
		i++;
	}
	i=0;
	while(temp!=NULL || !isempty(q))
	{
		if(temp!=NULL)
		{
			if(time>=temp->arrtime)
			{
				if(temp->next!=NULL)//package is taken from the list and added to queue
				{
					if(temp->arrtime==temp->next->arrtime)//the case when two or more packages arrived at the same time
					{
						head=newpackage(q,head);
						temp=temp->next;
						continue;
					}
				}
				head=newpackage(q,head);
				temp=temp->next;
			}
		}
		empty=whoisfree(array,empnum);
		if(empty!=-1 && !isempty(q))//if employee is empty, assign the package to him/her
		{
			indx=empty;//preserving the index of that employee
			array[indx]=0;//making that employee unavailable
			temp2=dequeue(q);//take the package from the queue to give to that employee
			wait[indx]=time-temp2->arrtime;//calculate the time the package waited for that employee
			if(wait[indx]>maxwait)//to give maximum waiting time in the end
			{
				maxwait=wait[indx];
			}
			timearr[indx]=temp2->arrtime;//preserving the arrival time of the package assigned to that employee
			timeser[indx]=temp2->sertime;//preserving the service time of the package assigned to that employee
			head2=deliverPackage(temp2,indx,head2,time);//modify the linked list using "deliverPackage" function
			totwait=totwait+wait[indx];//calculating total waiting time to calculate average time spent in the queue
		}
		busy=whoisbusy(array,empnum);
		while(i<empnum)//checks for every employee each time
		{
			//check if the employee with index i is done using the values that were
			//assigned to him/her in the previous if condition
			if(busy!=-1 && time>=wait[i]+timeser[i]+timearr[i])//free employee if he/she is done
			{
				array[i]=1;
				if(empty==-1)//to prevent infinite loop
				{
					time--;
				}
				break;
			}
			i++;
		}
		i=0;
		time++;
	}
	float total=totwait/packnum;//calculating the average waiting time in the queue
	report(empnum,packnum,head2,time,total,maxwait);
}
void report(int emp,int packnum,struct node *head2, int time, float total, int maxwait)
{
	struct node *temp;
	temp=head2;
	int *array,i=0,r=0,o=0,y=0,g=0;
	//array - to calculate the number of packages served by each employee based on his/her id
	//r - red, o - orange, y - yellow, g - green
	//these 4 are used to count the number of labels for each package
	array=(int*) malloc(sizeof(int)*emp);
	if(array==NULL)
	{
		printf("Memory allocation failure.");
		exit(1);
	}
	while(i<emp)//initialise to zero to count the number of packages for each employee after
	{
		array[i]=0;
		i++;
	}
	i=0;
	while(temp!=NULL)//counting number of labels for each package and number of packages for each employee
	{
		array[temp->id-1]++;
		switch(temp->imp)
		{
			case 'R':
				r++;
				break;
			case 'O':
				o++;
				break;
			case 'Y':
				y++;
				break;
			case 'G':
				g++;
				break;
		}
		temp=temp->next;
	}
	//printing out the report
	printf("******Report******\n");
	printf("The number of delivery employees : %d\n",emp);
	printf("The number of packages : %d\n",packnum);
	printf("Number of packages for each label\n");
	printf("	Red : %d\n	Orange : %d\n	Yellow : %d\n	Green : %d\n",r,o,y,g);
	printf("Number of packages for each delivery employee\n");
	while(i<emp)
	{
		printf("	Delivery employee %d delivered : %d\n",i+1,array[i]);
		i++;
	}
	printf("Completion time : %d\n",time);
	printf("Average time spent in the queue : %.1f\n",total);
	printf("Maximum waiting time : %d\n",maxwait);
}
int whoisbusy(int *array, int emp)//takes the array of employees to check who is busy
{
	int i=0;
	while(i<emp)
	{
		if(array[i]==0)
		{
			return i;
		}
		i++;
	}
	return -1;
}
struct node* deliverPackage(struct node *temp,int dec, struct node *head2,int start)
{
	struct node *temp2;//to trace the linked list until the correct package is found to modify id and service start time
	temp2=head2;
	while(temp2!=NULL)
	{
		if(temp2->arrtime==temp->arrtime && temp2->sertime==temp->sertime && temp2->imp==temp->imp)
		{
			break;
		}
		temp2=temp2->next;
	}
	temp2->id=dec+1;//modifying the id of correct package
	temp2->serstime=start;//modifying the service start time of correc package
	return head2;
}
int whoisfree(int *array,int emp)//takes the array of employees to check who is available
{
	int i=0;
	while(i<emp)
	{
		if(*(array+i)==1)
		{
			return i;
		}
		i++;
	}
	return -1;
}
struct node* newpackage(queue q, struct node *head)
{
	struct node *temp;//temp - to store the info from the package that is added to the queue
	temp=(struct node*) malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("Memory allocation failure.");
		exit(1);
	}
	temp->next=NULL;
	if(isempty(q))//if queue is empty, special case
	{
		temp->imp=head->imp;
		temp->arrtime=head->arrtime;
		temp->sertime=head->sertime;
		temp->serstime=head->serstime;
		temp->id=head->id;
		q->rear=temp;
		q->rear->next=NULL;
		q->front=q->rear;
		head=head->next;
		return head;
	}
	struct node *temp2;//to modify the front of the queue using the values obtained from temp
	temp->imp=head->imp;
	temp->arrtime=head->arrtime;
	temp->sertime=head->sertime;
	temp->serstime=head->serstime;
	temp->id=head->id;
	head=head->next;//moving the head next to have next package when "newpackage" function is executed again
	temp2=q->front;
	//below all of the if conditions are used to store the new package
	//in the queue based on the priority and arrival time of the package.
	//color code is more important than arrival time in this function.
	if(temp->imp=='R')
	{
		if(temp2->imp=='O' || temp2->imp=='Y' || temp2->imp=='G')
		{
			temp->next=q->front;
			q->front=temp;
			return head;
		}
		while(temp2->next!=NULL && temp2->next->imp=='R')
		{
			temp2=temp2->next;
		}
		temp->next=temp2->next;
		temp2->next=temp;
	}
	if(temp->imp=='O')
	{
		if(temp2->imp=='Y' || temp2->imp=='G')
		{
			temp->next=q->front;
			q->front=temp;
			return head;
		}
		while(temp2->next!=NULL && temp2->next->imp=='R')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='O')
		{
			temp2=temp2->next;
		}
		temp->next=temp2->next;
		temp2->next=temp;
	}
	if(temp->imp=='Y')
	{
		if(temp2->imp=='G')
		{
			temp->next=q->front;
			q->front=temp;
			return head;
		}
		while(temp2->next!=NULL && temp2->next->imp=='R')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='O')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='Y')
		{
			temp2=temp2->next;
		}
		temp->next=temp2->next;
		temp2->next=temp;
	}
	if(temp->imp=='G')
	{
		while(temp2->next!=NULL && temp2->next->imp=='R')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='O')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='Y')
		{
			temp2=temp2->next;
		}
		while(temp2->next!=NULL && temp2->next->imp=='G')
		{
			temp2=temp2->next;
		}
		temp->next=temp2->next;
		temp2->next=temp;
	}
	return head;
}
int* initialiseSimulator(int emp,queue q)
{
	q->front=NULL;//creating empty queue
	q->rear=NULL;
	int *array,i=0;//array - array of employees
	array=(int*) malloc(sizeof(int)*emp);
	if(array==NULL)
	{
		printf("\nMemory allocation failed.");
		exit(1);
	}
	while(i<emp)//initialise all employees to available
	{
		*(array+i)=1;
		i++;
	}
	return array;
}
void parseinput(int argc, char *argv[],int *pack,int *emp,int *maxar, int *maxser)
{
	//using pass by reference to pass the values to main function
	*pack=atoi(argv[1]);
	*emp=atoi(argv[2]);
	*maxar=atoi(argv[3]);
	*maxser=atoi(argv[4]);
}
struct node* createpackagelist(struct node *head,int pack,int maxar,int maxser)
{
	struct node *temp;//temp - to traverse and create a linked list
	temp=head;
	int i=0,val;
	char c;
	while(i<pack)
	{
		switch(rand()%4)//random color code assignment to each package
		{
			case 0:
				temp->imp='R';
				break;
			case 1:
				temp->imp='O';
				break;
			case 2:
				temp->imp='Y';
				break;
			case 3:
				temp->imp='G';
				break;
		}
		temp->arrtime=rand()%maxar+1;//random arrival time assignment
		temp->sertime=rand()%maxser+1;//random service time assignment
		temp->id=0;//id is 0 for every package when it is not served yet
		temp->serstime=0;//service start time is 0 for every package when it is not served yet
		if(i==pack-1)//to prevent the creation of unnecessary node in the end of the list
		{
			temp->next=NULL;
			break;
		}
		temp->next=(struct node*) malloc(sizeof(struct node));
		temp=temp->next;
		i++;
	}
	i=0;
	temp=head;
	while(i<pack)//this loop sorts the packages according to their arrival time
	{
		while(temp->next!=NULL)
		{
			if(temp->arrtime>temp->next->arrtime)
			{
				val=temp->arrtime;
				temp->arrtime=temp->next->arrtime;
				temp->next->arrtime=val;
				val=temp->sertime;
				temp->sertime=temp->next->sertime;
				temp->next->sertime=val;
				c=temp->imp;
				temp->imp=temp->next->imp;
				temp->next->imp=c;
			}
			temp=temp->next;
		}
		temp=head;
		i++;
	}
	return head;
}
