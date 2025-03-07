/*

In this code, all required functions from the task are implemented, as well as
2 additional functions.

----------------------------------------------------------------------------------------

About functions:



main - This function takes the input from the command line, and passes this input
in the form of the string to readData function (the input is the name of the file). 
Then, it maintains the menu for the user and asks the user what he/she wants to do.

readData - This function takes the input as a string, and using that string, it 
tries to open a file. If a file does not exist, it prints appropriate message
to the user. If it exists, it continues with a loop designed to read data from
the file and store it into the binary tree. To store the data from the file,
it uses insertEarthquacke function, which stores the needed information in the
node and if BST tree is not balanced, it automatically balances it. So, after readData
function is implemented, it returns a complete AVL tree to main function.

insertEarthquacke - This function takes the tree and all of the information that
needs to be stored into that tree. It creates new node of a tree, and immediately
after that it checks whether the tree is still balanced or not. If it is not, it
refers to the rotation functions declared in avltree.h header file. So, every time 
this function is called, a binary tree remains balanced. 

displayIndex - This function takes an avl tree as an input and uses in-order traversal
to display countries in alphabetical order. 

countmax - This is one of the two additional functions I used in my code. It takes an avl tree
and the address of the int variable. This function uses post-order traversal and that int variable
counts the maximum number of earthquackes among all of nodes.

countmin - This is one of the two additional functins I used in my code. It takes an avl tree
and the address of the float variable. This function also uses post-order traversal
That float variable is first equal to the magnitude of the earthquacke of the root 
node of the tree. Then, after its address is passed to countmin function, it is compared 
to other earthquackes, and if the earthquacke which is smaller than float variable 
is found, that float variable is replaced by that earthquacke. It therefore finds
the weakest earthquacke that exists in the tree. 

dangerousPlace - This function takes the maximum calculated in countmax and an avl tree.
It traverses the entire tree using post-order traversal, and while traversing, it counts
the earthquackes of each country. If it finds a country which has the same number of 
earthquackes as maximum variable counted in countmax, it then prints the information
about this country as the most dangerous place.

weakestEarthquacke - This function takes the minimum earthquakce magnitude calculated
in countmin function and an avl tree. It then traverses the entire tree using post-order
traversal to find the country that has an earthquacke of that magnitude. If it finds such
country, it prints the information about that country as a country with the weakest earthquacke.

--------------------------------------------------------------------------------------------------

Important remark about time complexity of weakestEarthquacke and dangerousPlace functions:

I provided the time complexity of these two functions, but they will not work if min and max
values are not calculated in countmin and countmax respectively beforehand. When you come to
weakestEarthquacke and dangerousPlace functions in this code, you will see the time complexity 
of them seperated from the time complexity of countmin and countmax functions, because assignment
requested to discuss the complexity of only weakestEarthquacke and dangerousPlace functions.

Discussion of time complexity of dangerousPlace function - line 176
Discussion of time complexity of weakestEarthquacke function - line 126
Discussion of how could I reduce the time complexity of dangerousPlace function? - line 238
Discussion of how could I reduce the time complexity of weakestEarthquacke function? - line 245

Below you can see the code.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"
tree readData(char[]);
tree insertEarthquacke(tree,char[],float,float,float,int);
void displayIndex(tree);
void countmax(tree,int*);
void countmin(tree,float*);
void dangerousPlace(tree t,int);
void weakestEarthquacke(tree,float);
int main(int argc, char *argv[])
{
	int ch=0,max=0;
	float min=0;
	//ch - variable to keep track of the choice of the user
	//max - this one will store the number maximum earthquackes that some country has
	//min - this one will store the magnitude of the weakest earthquacke among all
	tree t=NULL;
	t=readData(argv[1]);//receiving a complete tree
	while(ch!=4)
	{
		printf("\n1.Display the full index of earthquackes\n");
		printf("2.Display earthquackes of the most dangerous place\n");
		printf("3.Display the weakest earthquacke\n");
		printf("4.Exit\n");
		printf("----------------------------------\n");
		printf("Enter your opion:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				displayIndex(t);//displaying the contents of a tree in alphabetical order
				break;
			case 2:
				countmax(t,&max);//first counting the maximum number of earthquackes for some country
				dangerousPlace(t,max);//then using that number to find that country and print it
				break;
			case 3:
				min=t->mag;//assigning the magnitude of the earthquacke of the root node as minimum value
				countmin(t,&min);//counting the minimum magnitude
				weakestEarthquacke(t,min);//using the minimum magnitude to find the country that has this earthquacke
				break;
			case 4:
				printf("\nGoodbye!\n");//Goodbye!
				break;
			default:
				printf("\nCommand not recognized\n");
				break;
		}
	}
}
/*
Time complexity of weakestEarthquacke function is O(n*k) where n - number of nodes in the tree
and k - maximum number of nodes in a linked list of all of the trees.
This complexity comes from the fact that this function traverses each node of the avl tree, and
for each node it also traverses its linked list, to find the earthquacke of magnitude equal to
min (the magnitude of the weakest earthquacke).
*/
void weakestEarthquacke(tree t, float min)
{
	if(t!=NULL)
	{
		struct Tree *temp=t;
		weakestEarthquacke(t->right,min);
		weakestEarthquacke(t->left,min);
		while(temp!=NULL)
		{
			if(temp->mag==min)
			{
				printf("Weakest earthquacke:\n");
				printf("%s,%.1f,%.4f,%.4f,%d\n",temp->name,temp->mag,temp->lat,temp->lon,temp->tsu);
			}
			temp=temp->next;
		}
	}
}
/*
Time complexity of countmin function is O(n*k) where n - number of nodes in the tree
and k - maximum number of nodes in a linked list of all of the trees.
This complexity comes from the fact that this function traverses each node of the avl tree, and
for each node it also traverses its linked list, to find min (the minimum earthquacke magnitude
of the entire tree)
*/
void countmin(tree t, float *min)
{
	if(t!=NULL)
	{
		struct Tree *temp=t;
		countmin(t->left,min);
		countmin(t->right,min);
		while(temp!=NULL)
		{
			if(temp->mag<*min)
			{
				*min=temp->mag;
			}
			temp=temp->next;
		}
	}
}
/*
Time complexity of dangerousPlace function is O(n*k) where n - number of nodes in the tree
and k - maximum number of nodes in a linked list of all of the trees.
This complexity comes from the fact that this function traverses each node of the avl tree, and
for each node it also traverses its linked list, to find the country with the same number of
nodes as max (maximum number of earthquackes in some country)
*/
void dangerousPlace(tree t, int max)
{
	if(t!=NULL)
	{
		int num=0;
		struct Tree *temp=t;
		dangerousPlace(t->left,max);
		dangerousPlace(t->right,max);
		while(temp!=NULL)
		{
			num++;
			temp=temp->next;
		}
		if(num==max)
		{
			temp=t;
			while(temp!=NULL)
			{
				printf("%s,%.1f,%.4f,%.4f,%d\n",temp->name,temp->mag,temp->lat,temp->lon,temp->tsu);
				temp=temp->next;
			}
		}
	}
}
/*
Time complexity of countmax function is O(n*k) where n - number of nodes in the tree
and k - maximum number of nodes in a linked list of all of the trees.
This complexity comes from the fact that this function traverses each node of the avl tree, and
for each node it also traverses its linked list, to find max (the maximum number of earthquackes
for a country in the entire tree)
*/
void countmax(tree t, int *max)
{
	if(t!=NULL)
	{
		int num=0;
		countmax(t->left,max);
		countmax(t->right,max);
		struct Tree *temp=t;
		while(temp!=NULL)
		{
			num++;
			temp=temp->next;
		}
		if(*max<num)
		{
			*max=num;
		}
	}
}
/*
After discussing time complexities of each of the above functions, I would like to emphasize that
the time complexity of the process of finding the most dangerous country is O(n*k)+O(n*k)=O(n*k).

Also, I am going to discuss how I could reduce the time compelxity of this code.

I believe that if our binary tree would be built according to the sizes of linked lists 
attached to each node of the tree (for example, if linked list attached to a root node has
3 nodes, then the linked list attached to the left child of the root could only have less than
3 nodes). This way, our dangerousPlace function's complexity would have been reduced to O(log(n))
because we could have easily found the node of the tree which has the linked list with maximum
nodes.

Considering weakestEarthquacke function, if the linked lists that are attached to the nodes of
our tree are already sorted according to their earthquackes magnitudes, where head is minimum
magnitude and tail is the maximum magnitude, then the time complexity of weakestEarthquacke
function would be O(n), where n is the number of nodes of the tree. This is because we still
would have traversed each node of the tree to find minimum magnitude, but now we would not
traverse the linked list of each tree, because we know that the first node of the linked list
already contains the minimum magnitude of that linked list.

*/
tree readData(char argv[])
{
	tree t=NULL;
	FILE *file;
	file=fopen(argv,"r");
	if(file==NULL)
	{
		printf("Such file does not exist.\n");
		exit(1);
	}
	char str[100],c;
	float mag,lat,lon;
	int tsu,i=0;
	while((c=fgetc(file))!=EOF)
	{
		while(c!=',')
		{
			str[i]=c;
			str[i+1]='\0';
			c=fgetc(file);
			i++;
		}
		fscanf(file,"%f",&mag);
		c=fgetc(file);
		fscanf(file,"%f",&lat);
		c=fgetc(file);
		fscanf(file,"%f",&lon);
		c=fgetc(file);
		fscanf(file,"%d",&tsu);
		c=fgetc(file);
		i=0;
		t=insertEarthquacke(t,str,mag,lat,lon,tsu);
	}
	fclose(file);
	return t;
}
tree insertEarthquacke(tree t, char str[], float mag, float lat, float lon, int tsu)
{
	if(t==NULL)
	{
		t=malloc(sizeof(struct Tree));
		if (t == NULL)
		{
			printf("Error.\n");
			exit(1);
		}
		else
		{
			strcpy(t->name,str);
			t->mag=mag;
			t->lat=lat;
			t->lon=lon;
			t->tsu=tsu;
			t->left=NULL;
			t->right=NULL;
			t->next=NULL;
			t->height=0;
		}
	}
	else if(strcmp(str,t->name)<0)//str is val t name is t val and this is val<t val case
	{
		t->left=insertEarthquacke(t->left,str,mag,lat,lon,tsu);
		if(height(t->left)-height(t->right)==2)
		{
			if(strcmp(str,t->left->name)<0)
			{
				t=LLrotation(t);
			}
			else
			{
				t=RLrotation(t);
			}
		}
	}
	else if(strcmp(str,t->name)>0)
	{
		t->right=insertEarthquacke(t->right,str,mag,lat,lon,tsu);
		if(height(t->right)-height(t->left)==2)
		{
			if(strcmp(str,t->right->name)>0)
			{
				t=RRrotation(t);
			}
			else
			{
				t=LRrotation(t);
			}
		}
	}
	else if(strcmp(str,t->name)==0)
	{
		struct Tree *temp=NULL;
		temp=t;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=malloc(sizeof(struct Tree));
		temp=temp->next;
		strcpy(temp->name,str);
		temp->mag=mag;
		temp->lat=lat;
		temp->lon=lon;
		temp->tsu=tsu;
		temp->left=NULL;
		temp->right=NULL;
		temp->next=NULL;
		return t;
	}
	t->height = max(height(t->left), height(t->right)) + 1;
	return t;
}
void displayIndex(tree t)
{
	if(t==NULL)
	{
		return;
	}
	displayIndex(t->left);
	printf("%s,%.1f,%.4f,%.4f,%d\n",t->name,t->mag,t->lat,t->lon,t->tsu);
	if(t->next!=NULL)
	{
		struct Tree *temp=NULL;
		temp=t->next;
		while(temp!=NULL)
		{
			printf("%s,%.1f,%.4f,%.4f,%d\n",temp->name,temp->mag,temp->lat,temp->lon,temp->tsu);
			temp=temp->next;
		}
	}
	displayIndex(t->right);
}
