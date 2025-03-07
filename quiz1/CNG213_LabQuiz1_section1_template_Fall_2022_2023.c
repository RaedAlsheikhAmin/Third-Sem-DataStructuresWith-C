#include <stdio.h>
#include <stdlib.h>

//Node decleration of a linked list

	struct postNode
	{
		char name[20];
		int year;
		char applicationname[40];
		int numoflikes[5];
		struct postNode *next;

	};

struct postNode * addPost(struct postNode *p);
void displayHighestLikes(struct postNode *p);

int main(){
	int command;
	struct postNode * publicationsList = NULL;

	do{
		printf("1. Add a a new post\n");
		printf("2. Display the post with highest number of Likes\n");
		printf("3. Exit\n");
		printf("Enter command: ");
		scanf("%d", &command);
		switch (command){

			case(1):
			publicationsList= addPost(publicationsList);
			break;
			case(2):
			    displayHighestLikes(publicationsList);
			    break;

		}
	} while (command != 3);
	return 0;
}


struct postNode * addPost(struct postNode *p){
	struct postNode *head=NULL,*first,*last;
	int numposts,i;
	printf("how many posts do you want to add: ");
	scanf("%d",&numposts);
	do
	{
	p=(struct postNode*)malloc(sizeof(struct postNode));
	p->next=NULL;
	printf("post name: ");
	scanf("%s",p->name);
	printf("Application: ");
	scanf("%s",p->applicationname);
	printf("Creation year: ");
	scanf("%d",&(p->year));
	printf("The number of likes in the last five months: ");
	for(i=0;i<5;i++)
	{
		scanf("%d",&(p->numoflikes[i]));
	}


	if(head==NULL)
	{
		head=p;
		last=p;
    }
	else
	{
		last->next=p;
		last=first=p;
    }
numposts--;
}while(0<numposts);
first=head;
return head;

}

void displayHighestLikes(struct postNode *p){
	struct postNode *temp=p;
	int i,max=0;
	while(temp!=NULL)
    {

        for(i=0;i<5;i++)
        {
            if(max<temp->numoflikes[i])
                max=temp->numoflikes[i];
        }
        temp=temp->next;
    }
    printf("the maximum likes is %d\n",max);
}
