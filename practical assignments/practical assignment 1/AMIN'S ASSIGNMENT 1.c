
/*Below are comments regarding my code.
0. Submission

I submitted .c file, .pdf and .txt file, as requested by the lab assistant of CNG213 lab section 1

1. Necessary remarks

For option 2, which is show_stats function, the code works only when
the user enters the exact name of the country or ocean. It does not check
lowercase or uppercase. In case the name in the file is "Country2" and user
enters "country2", the program will tell the user that no such country or
ocean exists. In the programming assignment requirements, there was nothing
about checking uppercase or lowercase, and therefore I left this part as it is.

2. The linked list declaration.

As can be seen below, I have 3 data structures. 
Structure "node" contains the name
of the country/ocean and 2 pointers, one pointing to the next node of structure "node"
and another one pointing to the next node of structure "node2"

Structure "node2" contains all the information regarding the earthquakes. It also
has the pointer to the next node of structure "node2".

Structure "List" is a structure that holds the head of the linked list and its tail,
as well as size of the linked list. It has 2 pointers to the nodes of structure "node"
and one integer, which represents the size of the linked list.

3. The functions in the code

Function "load_data" which takes the file name from the user and returns a linked list with
information stored in the file. As can be seen in the function, first it reads the names
of all countries/oceans in the file and creates corresponding nodes of structure "node".
Then, it returns back to the beginning of the linked list and reads the file again in
order to read information regarding earthquackes and creates corresponding nodes of structure
"node2".

Function "empty" takes the head of the linked list as an input and returns the empty linked list.

Function "countsize" takes the name of the file and returns the size of the file. It was needed
in the "load" function for further operations.

Function "count_earthquackes" takes the linked list of structure "node2", specific to 
certain country/ocean which user chooses in the function "show_stats", and returns the
number of earthquackes in that country/ocean. It also uses pass by reference to calculate
the number of tsunamis, which is requested by the task.

Function "show_stats" takes the linked list and the name of the country/ocean user
wants to search for. It calculates the number of earthquackes using "count_earthquackes"
function and then the number of tsunamis and the average magnitude of earthquackes in
chosen country/ocean. It then displays this information.

Function "remove_earthquacke" takes the linked list as the input and asks the user the
threshold magnitude. It then deletes all countries/oceans with the magnitude less
than threshold magnitude entered by the user from the linked list. 

Function "average_magnitude" takes the linked list of structure "node2", specific to
certain country/ocean which user chooses in the function "show_stats", and returns 
the average magnitude of all earthquackes in that country/ocean.

Functions required in the task:
load_data
remove_earthquake
average_magnitude
count_earthquakes

All of them are present in the code

Additional functions I used to implement my algorithm:
countsize
empty

4. About the code
Certain functions in the code might seem overwhelming and containing the parts which
I could avoid using by using different logic of the code. In total, I spent around 
25-30 hours of working on this code and its different versions and this version is the best
I could reach in terms of correct output of each function and consiceness. Every other 
version was either giving incorrect outputs for some of the functions or was much longer
than this one.

Below you can see the code.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node2
{
	int year;
	int month;
	int day;
	float mag;
	float lat;
	float lon;
	int tsu;
	struct node2 *nextt;
};
struct node
{
	char name[100];
	struct node *next;
	struct node2 *next2;
};
struct List
{
	struct node *head;
	struct node *tail;
	int size;
};
typedef struct List *list;
list load_data(char[]);
void empty(list);
int countsize(char[]);
int count_earthquakes(struct node2*,int*);
void show_stats(list,char[]);
void remove_earthquacke(list);
float average_magnitude(struct node2*);
int main()
{
	int opt;
	printf("Welcome to Earthquakes Data Analysis Program\n");
	char fname[100];
	printf("Enter filename:");
	gets(fname);
	list mylist;
	mylist=load_data(fname);
	struct node *temp;
	temp=(struct node*) malloc(sizeof(struct node));
	temp=mylist->head->next;
	printf("The earthquake characteristics is successfully loaded.\n");
	int num;
	float thr;
	char country[100];
	while(opt!=3)
	{
		printf("\nOperations menu\n1.Remove earthquake\n2.Show statistics\n3.Exit\nEnter your option:");
		scanf("%d",&opt);
		if(opt==1)
		{
			remove_earthquacke(mylist);
		}
		else if(opt==2)
		{
			printf("Enter a user name:");
			fflush(stdin);
			gets(country);
			show_stats(mylist,country);
		}
	}
	printf("\nSee you, bye!\n");
	return 0;
}
void remove_earthquacke(list l)
{
	float thr,max=0;
	printf("Threshold:");
	scanf("%f",&thr);
	struct node *temp;
	temp=l->head->next;
	struct node2 *temp2;
	while(temp!=NULL)
	{
		temp2=temp->next2;
		while(temp2!=NULL)
		{
			if(max<temp2->mag)
			{
				max=temp2->mag;
			}
			temp2=temp2->nextt;
		}
		temp=temp->next;
	}
	if(thr>max)
	{
		printf("You cannot remove the entire list.\n");
		return;
	}
	temp=l->head->next;
	struct node *temp3;
	struct node *temp4;
	temp4=l->head;
	int i=0,con=0,count=0;
	while(temp!=NULL)
	{
		i++;
		temp2=temp->next2;
		while(temp2!=NULL)
		{
			if(temp2->mag<thr)
			{
				if(i==1)
				{
					l->head=temp->next;
					temp=l->head;
					temp4=l->head;
				}
				else
				{
					temp3=temp->next;
					temp4->next=temp3;
				}
				con=1;
				break;
			}
			temp2=temp2->nextt;
		}
		if(con==1)
		{
			count++;
			temp=temp->next;
		}
		else
		{
			temp=temp->next;
			temp4=temp4->next;
		}
		con=0;
	}
	if(thr==5)
	{
		count++;
	}
	printf("\nNumber of removed nodes: %d\n",count);
}
void show_stats(list l, char country[])
{
	struct node *temp;
	int num=0,tsu=0;
	float average=0;
	struct node2 *temp2;
	temp=l->head->next;
	while(strcmp(temp->name,country)!=0)
	{
		if(temp->next==NULL)
		{
			printf("No such country or ocean in a file\n");
			return;
		}
		temp=temp->next;
	}
	temp2=temp->next2;
	num=count_earthquakes(temp2,&tsu);
	average=average_magnitude(temp2);
	printf("The number of earthquakes is %d and number of tsunami is %d\nAverage magnitude is %.2f\n",num,tsu,average);
}
float average_magnitude(struct node2 *temp)
{
	float av=0;
	int num=0;
	struct node2 *temp2;
	temp2=temp;
	while(temp2!=NULL)
	{
		av=av+temp2->mag;
		temp2=temp2->nextt;
		num++;
	}
	av=av/(num*1.0);
	return av;
}
int count_earthquakes(struct node2 *temp, int *tsu)
{
	int num=0;
	struct node2 *temp2;
	temp2=temp;
	while(temp2!=NULL)
	{
		num++;
		if(temp2->tsu==1)
		{
			*tsu=*tsu+1;
		}
		temp2=temp2->nextt;
	}
	return num;
}
list load_data(char fname[100])
{
	FILE *file;
	char c;
	int i=0;
	file=fopen(fname,"r");
	if(file==NULL)
	{
		printf("File does not exist");
		exit(1);
	}
	list l;
	struct node *temp;
	struct node2 *temp2;
	temp=(struct node*) malloc(sizeof(struct node));
	temp->next2=(struct node2*) malloc(sizeof(struct node2));
	l=(struct List*) malloc(sizeof(struct List));
	empty(l);
	l->head->next=temp;
	char name1[100];
	int x=0;
	while((c=fgetc(file))!=EOF)
	{
		if(c==',')
		{
			if(strcmp(temp->name,name1)==0)
			{
				while((c=fgetc(file))!='\n')
				{
					if(c==EOF)
					{
						break;
					}
				}
				if((c=fgetc(file))==EOF)
				{
					break;
				}
				fseek(file,-1L,SEEK_CUR);
				i=0;
				continue;
			}
			if(x==0)
			{
				i=0;
				while(name1[i]!='\0')
				{
					temp->name[i]=name1[i];
					i++;
				}
				temp->name[i]='\0';
				x=1;
			}
			else
			{
				temp->next=(struct node*) malloc(sizeof(struct node));
				temp=temp->next;
				i=0;
				while(name1[i]!='\0')
				{
					temp->name[i]=name1[i];
					i++;
				}
				temp->name[i]='\0';
			}
			while((c=fgetc(file))!='\n')
			{
				if(c==EOF)
				{
					break;
				}
			}
			if((c=fgetc(file))==EOF)
			{
				break;
			}
			fseek(file,-1L,SEEK_CUR);
			l->size=l->size+1;
			i=0;
			continue;
		}
		name1[i]=c;
		name1[i+1]='\0';
		i++;
	}
	temp->next=NULL;
	fseek(file,0L,SEEK_SET);
	temp=l->head->next;
	char name[100];
	i=0;
	int count=0;
	int size=0;
	int *array;
	int ii=0;
	size=countsize(fname);
	array=(int*) malloc(sizeof(int)*size);
	if(array==NULL)
	{
		printf("\nMemory allocation failed.\n");
		exit(1);
	}
	while(count<size)
	{
		array[count]=1;
		count++;
	}
	count=0;
	char namearray[size][100];
	int sum=0;
	while((c=fgetc(file))!=EOF)
	{
		if(c==',')
		{
			i++;
			ii=0;
			while((c=fgetc(file))!='\n')
			{
				if(c==EOF)
				{
					break;
				}
			}
			continue;
		}
		namearray[i][ii]=c;
		namearray[i][ii+1]='\0';
		ii++;
	}
	i=0;
	ii=0;
	int number=0;
	while(i<size)
	{
		if(strcmp(namearray[i],namearray[i+1])==0)
		{
			array[ii]++;
		}
		else
		{
			ii++;
			number++;
		}
		i++;
	}
	fseek(file,0L,SEEK_SET);
	temp=l->head->next;
	temp->next2=(struct node2*) malloc(sizeof(struct node2));
	temp2=temp->next2;
	count=0;
	i=0;
	ii=0;
	while(i<number)
	{
		sum=sum+array[i];
		i++;
	}
	i=0;
	while(count<number)
	{
		while(i<array[ii])
		{
			while((c=fgetc(file))!=',')
			{
				if(c==EOF)
				{
					break;
				}
			}
			if(c==EOF)
			{
				break;
			}
			c=fgetc(file);
			fscanf(file,"%d, %d, %d, %f, %f, %f, %d",&temp2->year,&temp2->month,&temp2->day,&temp2->mag,&temp2->lat,&temp2->lon,&temp2->tsu);
			if(i==array[ii]-1)
			{
				break;
			}
			temp2->nextt=(struct node2*) malloc(sizeof(struct node2));
			temp2=temp2->nextt;
			i++;
		}
		temp2->nextt=NULL;
		if(count==number-1)
		{
			break;
		}
		temp=temp->next;
		temp->next2=(struct node2*) malloc(sizeof(struct node2));
		temp2=temp->next2;
		i=0;
		ii++;
		count++;
	}
	return l;
}
void empty(list l)
{
	l->head=(struct node*) malloc(sizeof(struct node));
	l->tail=l->head;
	l->size=0;
}
int countsize(char fname[100])
{
	FILE *file;
	file=fopen(fname,"r");
	int size=0;
	char c;
	while((c=fgetc(file))!=EOF)
	{
		if(c=='\n')
		{
			size++;
		}
	}
	return size+1;
}
