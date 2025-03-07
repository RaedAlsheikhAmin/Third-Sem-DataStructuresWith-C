#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define FALSE 0
#define TRUE 1

struct TreeNode
{
  float val;//it should array of float and takes two rating at the same time, change your code accordingly that you have strcmp()==0 to check if the name is repeated, and do the last function.
  char movie[30];
  struct TreeNode* left;
  struct TreeNode* right;
};

struct TreeNode* CreateTree(void);
struct TreeNode* Insert(float,char[], struct TreeNode*);
float searchTOWatch(struct TreeNode*, char[]);
void TwoRatings(struct TreeNode*);
void DisplayTree(struct TreeNode*);

int main()
{
    struct TreeNode* myTree;
    char moviename[30],search[30];
    int exit;
    float val;
    char command;
	myTree = CreateTree();
    exit = FALSE;
	while (!exit)
	{
      printf("\nMenu:\n i)nitialize\n n)ew element \n s)search \n e)xit\nEnter command: ");
      scanf(" %c", &command);
     switch(command)
     {
		case 'i':
			myTree = CreateTree();
			break;
		case 'n':
			printf("enter rating: ");//my rating
			scanf("%f", &val);
			while(val>10 || val<0)//to have a fair rating for the movies
			{

				printf("\nthe rating that you entered is not accepted\n");
				printf("enter the rate of the movie again: ");//my rating
				scanf("%f", &val);
			}
			printf("enter a movie name or series: ");
			fflush(stdin);
			gets(moviename);
			myTree = Insert(val,moviename, myTree);
			printf("Tree now:\n");
			DisplayTree(myTree);
			break;
		case 's':
			printf("enter the movie or series name that you want to search about: ");
			fflush(stdin);
			gets(search);
			if(searchTOWatch(myTree,search)==-1)
				printf("name is not found");
			else
				printf("the rating of the movie that you searched about is %.1f",searchTOWatch(myTree,search));
			break;
  		case 'e':
			exit = TRUE;
			break;
		default:
			printf("command not recognized\n");
			break;
	}//end switch
  }//end while

  printf("\n\n");
  system("PAUSE");
  return 0;
}//end main

struct TreeNode* CreateTree(void)
{
    return NULL;
}

struct TreeNode* Insert(float val, char moviename[30], struct TreeNode* t)
{
 if(t == NULL)
	{
		t = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		if(t == NULL)
			printf("Out of memory space!!!\n");
		else
		{
			t->val = val;
			strcpy(t->movie,moviename);
			t->left = t->right = NULL;
		}
	}
	else
	if(strcmp(moviename,t->movie)==-1)
		t->left = Insert(val,moviename,t->left);

	else
		if(strcmp(moviename,t->movie)==1)
			t->right = Insert(val,moviename, t->right);
	return t;
}

void DisplayTree(struct TreeNode* t)
{
   if (t !=NULL)
   {
		DisplayTree(t->left);
		printf("%s %.1f\n", t->movie,t->val);
		DisplayTree(t->right);
   }
}
float searchTOWatch(struct TreeNode* t, char moviename[30])
{
	if(t==NULL)
	{
		return -1;
	}
	if(strcmp(moviename,t->movie)==-1)
		return searchTOWatch(t->left,moviename);

	else if(strcmp(moviename,t->movie)==1)
			 return searchTOWatch(t->right,moviename);
	return t->val;

}
void TwoRatings(struct TreeNode* t)
{
}


