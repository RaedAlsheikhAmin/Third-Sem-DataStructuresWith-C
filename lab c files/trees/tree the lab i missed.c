#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 16
#define FALSE 0
#define TRUE 1

/*A tree Node declaration*/
struct Node
{
 int val;
 struct Node* left;
 struct Node* right;
};
typedef struct Node *Tree;
struct StackRecord //stack
{
   struct Node* data;
   struct StackRecord *next;
};
/*Function signatures*/
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree);
void PushStack(struct StackRecord *, struct Node *);
struct Node * popStack(struct StackRecord * );
int isEmpty(struct StackRecord*);
void InOrderDisplay(struct Node*, struct StackRecord *);
int main()
{
   struct StackRecord *myStack;
   myStack=(struct StackRecord *)malloc(sizeof(struct StackRecord));
   myStack->next=NULL;
   Tree myTree, pos;
   int exit, val, height;
   char command;

       myTree = CreateTree();
       exit = FALSE;

       while (!exit)
       {
              fflush(stdin);
              printf("\nMenu:\n i)nitialize\n n)ew element \n e)xit\n o)rder \nEnter command: ");
              scanf("%c", &command);
              fflush(stdin);

                 switch(command)
                 {
                        case 'i':
                               myTree = MakeEmptyTree(myTree);
                               break;
                        case 'n':
                               printf("enter value: ");
                               scanf("%d", &val);
                               myTree = InsertElement(val, myTree);
                               DisplayTree(myTree);
                               break;
                        case 'e':
                               exit = TRUE;
                               break;
                         case 'o':
                               InOrderDisplay(myTree, myStack);
                               break;
                        default:
                                printf("command not recognized\n");
                                break;
                 }


       }

   printf("\n\n");
   system("PAUSE");
   return 0;
}

/*Function that mainly creates a tree which is initially NULL*/
Tree CreateTree(void)
{
   return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyTree(Tree t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

/*This function takes an integer value and a tree,
 and inserts that value to the tree*/
Tree InsertElement(int x, Tree t)
{
  if (t == NULL)
   {
       /* Create and return a one-node tree */
       t = (Tree) malloc(sizeof(Tree));
           t->val = x;
           t->left = t->right = NULL;

   }
   else if (x < t->val)
   t->left = InsertElement(x, t->left);
   else if (x > t->val)
   t->right = InsertElement(x, t->right);
   /* else x is in the tree already. We'll do nothing */
   return t; /* Don't forget this line!! */
}

/*This function takes a tree and displays its content on the screen*/
void DisplayTree(Tree t)
{
  if (t !=NULL)
  {
       DisplayTree(t->left);
       printf("%d\n", t->val);
       DisplayTree(t->right);
  }
}
void InOrderDisplay(struct Node *myTree, struct StackRecord *myStack)
{
   int finished=0;
   struct Node *start;
   start=myTree;
   while(finished!=1)
   {
       if(start!=NULL)
       {
           PushStack(myStack,start);
           start=start->left;
       }
       else if(!isEmpty(myStack))
       {
           start=popStack(myStack);
           printf("%d ",start->val);
           start=start->right;
       }
       else
       {
           finished=1;
       }
   }
}
void PushStack(struct StackRecord *s, struct Node *t )
{
   struct StackRecord *newnode;
   newnode=(struct StackRecord *)malloc(sizeof(struct StackRecord));
   newnode->data=t;
   newnode->next=s->next;
   s->next=newnode;
}
struct Node *popStack(struct StackRecord *s)
{
   struct StackRecord *removed;
   removed=s->next;
   s->next=s->next->next;
   return(removed->data);
}
int isEmpty (struct StackRecord* myStack)
{
   if(myStack->next==NULL)
       return 1;
   else
       return 0;
}
