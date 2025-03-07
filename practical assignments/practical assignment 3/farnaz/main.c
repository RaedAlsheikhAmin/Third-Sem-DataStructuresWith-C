//
//  main.c
//  indexingEarthquakes
//


// i used some of the functions from the lab worksheet and changed them based on the assignments requirement
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    float mag, lat, lon;
    int tsu;
    struct node *next;
};
typedef struct Node *AVLTree;

struct Node
{
    char p[100];
    float mag, lat, lon;
    int tsu;
    AVLTree left;
    AVLTree right;
    struct node *side;
    int height;
};

//extra function i used since i needed them for my code
AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree);
AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);
int AVLTreeHeight(AVLTree);
int Max(int, int);
void MagMin(AVLTree, float*);

//functions required in the manual
AVLTree readData(char *);
AVLTree insertEarthquake(AVLTree,char *, float, float, float, int);
void displayIndex(AVLTree);
void dangerousPlace(AVLTree, int *);
void weakestEarthquke(AVLTree, float );

int main()
{
    //creating AVL Tree
    AVLTree myTree;
    myTree = CreateTree();
    float min;
    int valid=1, choice, max=0, exit=0;
    char filename[100];
    printf("Welcome to Earthquake Indexing\n");
   do//do while loop to check if the entered file name is correct
    {
        do//do while loop to keep asking for the command
        {
        //asking the file name from the user since i am using mac i couldn't use command line and header file but i know how to use them in codeblocks, i had the same issue previous semester in cng 140
        printf("\nEnter file name:");
        scanf("%s",filename);
        if(strcmp(filename,"Earth.txt")==0)
        {
            //making empty tree
            myTree = MakeEmptyTree(myTree);
            myTree = readData(filename);
            printf("------------------------------------------------------------------------------------------------\nMenu\n1. Display the full index of earthquakes\n2. Display the earthquakes of the most dangerous place\n3. Display the weakest earthquake\n4. Exit\n-------------------------------------------------------------------------------------------------\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    displayIndex(myTree);
                    break;
                case 2:
                    dangerousPlace(myTree, &max);
                    break;
                case 3:
                    min=myTree->mag;
                    MagMin(myTree, &min);
                    weakestEarthquke(myTree,min);
                    break;
                case 4:
                    printf("bye bye !!!");
                    exit=1;
                    break;
                default:
                    printf("command not recognized !\n");

            }
            valid=1;
       }
        else
        {
           printf("Error! File not Found!!!");
           valid=0;
        }
        }while(exit==0);
    }while(valid!=1);
    return 0;
}
//------------------------------------------------------------------------------------------
AVLTree CreateTree(void)
{
        return NULL;
}
//------------------------------------------------------------------------------------------
AVLTree MakeEmptyTree(AVLTree t)
{
        if (t != NULL)
        {
                MakeEmptyTree(t->left);
                MakeEmptyTree(t->right);
                free(t);
        }
        return NULL;
}
//------------------------------------------------------------------------------------------
AVLTree readData(char * filename)
{
    AVLTree t;
    t = CreateTree();
    t = MakeEmptyTree(t);
    char c, place[100];
    float magnitude, latitude, longitude;
    int i=0, NumOfLine=0, tsunami;
    FILE *infile;
    infile=fopen(filename, "r");//openning the file for reading
    if(infile==NULL)//checking if the file opened successfully
    {
        printf("\nError! Couldn't open the file!");
        exit(1);
    }
    while((c=fgetc(infile))!=EOF)//counting the number of lines to know how many nodes we'll have
    {
        if(c=='\n')
        {
            NumOfLine++;
        }
    }
    NumOfLine++;
    rewind(infile);
    while(i<NumOfLine)
    {
        //reading from the file and inserting one by one by calling the insertEarthquake function everytime
        fscanf(infile,"%[^,],%f,%f,%f,%d",place,&magnitude,&latitude,&longitude,&tsunami);
        t =insertEarthquake(t,place,magnitude, latitude,longitude,tsunami);
        i++;
    }
    return t;
}
//------------------------------------------------------------------------------------------
//this function works only if the starting country doesn't have many values like country 6 or 7, otherwise it is not correct AVL tree, i spent 2 days trying to fix the problem but i couldn't
AVLTree insertEarthquake(AVLTree t, char * place, float magnitude, float latitude, float longitude, int tsunami)
{
    struct node* temp;
    if (t == NULL)
    {
        /*Create and return a one-node tree */
        t = malloc(sizeof(struct Node));
        if (t == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            strcpy(t->p,place);
            t->mag= magnitude;
            t->lat= latitude;
            t->lon=longitude;
            t->tsu=tsunami;
            t->height = 0;
            t->side = NULL;
            t->left = t->right =  NULL;
        }
    }
    else if (strcmp(place,t->p)<0)
    {
        t->left = insertEarthquake(t->left, place, magnitude, latitude, longitude, tsunami);
        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
        if (strcmp(place,t->p)<0)
            t = SingleRotateWithLeft(t);//right rotation
        else
            t = DoubleRotateWithLeft(t);

    }
    else if(strcmp(place,t->p)==0)
    {
        struct node * n;
        if(t->side==NULL)
        {
            n =(struct node *)malloc(sizeof(struct node));
            n->next=NULL;
            n->mag=magnitude;
            n->lat= latitude;
            n->lon= longitude;
            n->tsu= tsunami;
            t->side=n;
        }
        else
        {
            n =(struct node *)malloc(sizeof(struct node));
            n->next=NULL;
            n->mag=magnitude;
            n->lat= latitude;
            n->lon= longitude;
            n->tsu= tsunami;
            temp=t->side;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=n;

        }
    }
    else if (strcmp(place,t->p)>0)
    {
        t->right = insertEarthquake(t->right, place, magnitude, latitude, longitude, tsunami);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        if (strcmp(place,t->p)>0)
            t = SingleRotateWithRight(t);//left rotation
        else
            t = DoubleRotateWithRight(t);
    }
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    return t;
}
//------------------------------------------------------------------------------------------
int AVLTreeHeight(AVLTree t)
{
        if (t == NULL)
                return -1;
        else
                return t->height;
}
//------------------------------------------------------------------------------------------
AVLTree SingleRotateWithLeft(AVLTree k2)
{
        AVLTree k1;
        k1=k2->left;
        k2->left=k1->right;
        k1->right=k2;

        k2->height=Max(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right))+1;
        k1->height=Max(AVLTreeHeight(k1->left),k2->height)+1;
        return k1;
}
//------------------------------------------------------------------------------------------
AVLTree SingleRotateWithRight(AVLTree k1)
{
        AVLTree k2;
        k2=k1->right;
        k1->right=k2->left;
        k2->left=k1;

        k1->height=Max(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right))+1;
        k2->height=Max(AVLTreeHeight(k2->left),k1->height)+1;
        return k2;
}
//------------------------------------------------------------------------------------------
AVLTree DoubleRotateWithLeft(AVLTree k3)
{
        k3->left= SingleRotateWithRight(k3->left);
        return SingleRotateWithLeft(k3);
}
//------------------------------------------------------------------------------------------
AVLTree DoubleRotateWithRight(AVLTree k3)
{
        k3->right=SingleRotateWithLeft(k3->right);
        return SingleRotateWithRight(k3);
}
//------------------------------------------------------------------------------------------
int Max(int x, int y)
{
        if (x >= y)
                return x;
        else
                return y;
}

//------------------------------------------------------------------------------------------
void displayIndex(AVLTree t)
{
    if (t != NULL)
    {
        displayIndex(t->left);
        printf("%s %f %f %f %d\n", t->p, t->mag, t->lat, t->lon, t->tsu);
        if(t->side!=NULL)
        {
            struct node* tmp;
            tmp=t->side;
            do
            {
                printf("%s %f %f %f %d\n", t->p, tmp->mag, tmp->lat, tmp->lon, tmp->tsu);
                tmp=tmp->next;
            }while(tmp!=NULL);
        }
        displayIndex(t->right);
        printf("\n");
    }
}
//------------------------------------------------------------------------------------------
//i tried to avoid splitting this function into two parts and did it as a whole 1 function but if we have 2 counties with multiple values for ex country 2 with 4 values and country 6 with 5 values country 6 will be shown which is correct but instead of 5 times it'll be shown 10 time(twice), but there was no information or extra sample run given about multiple countries having multiple values or no country having multiple values
void dangerousPlace(AVLTree tree, int *max)
{
    int mx=0, count=0;
    AVLTree t =tree;
    AVLTree tr =tree;
    if(t != NULL)
    {
        dangerousPlace(t->left, max);
        if(t->side != NULL)
        {
            struct node* tmp;
            tmp=t->side;
            while(tmp!=NULL)
            {
                mx++;
                tmp=tmp->next;
            }
            if(*max<mx)
                *max=mx;
        }
        dangerousPlace(t->right, max);
    }
    t=NULL;
    if(t==NULL)
    {
        if(tr!=NULL)
        {
            dangerousPlace(tr->left, max);
            if(tr->side !=NULL)
            {
                struct node* Temp;
                Temp=tr->side;
                while(Temp!=NULL)
                {
                    count++;
                    Temp=Temp->next;
                }
                if(*max==count)
                {
                    printf("%s %f %f %f %d\n", tr->p, tr->mag, tr->lat, tr->lon, tr->tsu);
                    Temp=tr->side;
                    while(Temp!=NULL)
                    {
                        printf("%s %f %f %f %d\n", tr->p, Temp->mag, Temp->lat, Temp->lon, Temp->tsu);
                        Temp=Temp->next;
                    }
                }
            }
            dangerousPlace(tr->right, max);
        }
    }

}
//------------------------------------------------------------------------------------------
//for the weakestEarthquke function i tried to do it the same as the previous function but ocean x was also being printed and i couldn't fix the problem so i split it into two functions, first i find min magnitude using MagMin then i traverse through the tree and find the node which had min magnitude and print it
void MagMin(AVLTree t, float * min)
{
    if(t!=NULL)
    {
        MagMin(t->left,min);
        if(t->mag < *min)
        {
            *min=t->mag;
        }
        if(t->side!=NULL)
        {
            struct node* tmp;
            tmp=t->side;

            while(tmp!=NULL)
            {
                if(tmp->mag < *min)
                {
                    *min=tmp->mag;
                }
                tmp=tmp->next;
            }
        }
        MagMin(t->right,min);
    }
}
//------------------------------------------------------------------------------------------
void weakestEarthquke(AVLTree t, float min)
{
    if(t!=NULL)
    {
        weakestEarthquke(t->left,min);
        if(t->mag == min)
            printf("%s %f %f %f %d\n", t->p, t->mag, t->lat, t->lon, t->tsu);
        if(t->side !=NULL)
        {
            struct node* Temp;
            Temp=t->side;
            while(Temp!=NULL)
            {
                if(Temp->mag == min)
                {
                    printf("%s %f %f %f %d\n", t->p, Temp->mag, Temp->lat, Temp->lon, Temp->tsu);
                }
                Temp=Temp->next;
            }
        }
        weakestEarthquke(t->right,min);
    }

}
//worst case and avg case and best case are the same for both last 2 function asked in the manual and since we traverse through the tree it is O(N).
