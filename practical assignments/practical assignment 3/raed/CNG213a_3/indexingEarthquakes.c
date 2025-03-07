#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "avltree.h"
//this code works perfectly for everything except if the first country is going to be duplicated( for some reason) that is why i will upload the txt file.
t* readData(char **);//this function is going to take the data from the file and send them to insert function
t* insertEarthquake(char[],float,float,float,int,t*);//this function is going to make the AVL tree.
void displayIndex(t*);//this is going to display all the tree(countries)
void dangerousPlace(t*,int,int);
void dangerousplacemax(t*,int,int *);//this is going to get the max value of the nodes that each country have and send it to dangerousplace function to print.
void weakestEarthqukemin(t*, float*);//this is going to get the min magnitude of the earthquakes and send it to the weakesearthquake function to print it.
void weakestEarthquke(t*,float);
int main(int argc, char *argv[])//argc and argv to read from command line.
{
    t *tree=NULL;//make tree NULL to call read data later.
    int pmax=0,nmax=0;//pmax=previous max ,nmax=new ma; they will help me to find the max nodes for each country.
    float nearth=10;//nearth= new earthquacke, it will help me to find the weakest earthquacke, and it is set to 10 because it is the highest magnitude.
    tree=readData(argv);//here the function is to process the data from the file
    printf("Welcome to Earthquake Indexing :) :) ");
    printf("\n------------------------------------------------------------------------------------------------\nMenu \n1. Display the full index of earthquakes\n2. Display the earthquakes of the most dangerous place\n3. Display the weakest earthquake\n4. Exit");

    int command;//will take the command
    int exit=0;//for the loop
    while (!exit)
    {
        printf("\n-------------------------------------------------------------------------------------------------\n");
        fflush(stdin);
        printf("Enter your option: ");
        scanf("%d",&command);
        switch(command)//to hold the menu
        {
        case 1:
            displayIndex(tree);
            break;
        case 2:
            dangerousplacemax(tree,pmax,&nmax);
            dangerousPlace(tree,pmax,nmax);
            break;
        case 3:
            printf("Weakest Earthquake:\n");
            weakestEarthqukemin(tree,&nearth);
            weakestEarthquke(tree,nearth);
            break;
        case 4:
            printf("bye bye !!!");
            exit=1;
            break;
        default:
            printf("command not recognized\n");
            break;
        }//end of switch
    }//end of while for the menu

}
t* readData(char *argv[])
{
    FILE *infile;//declaring a file
    t *tree=NULL;//to return the tree.
    char c;//character to go over the file.
    int numberoflines=0;//varriable to count the number of lines.
    infile=fopen(argv[1],"r");//opening the file for reading
    if(infile==NULL)
    {
        printf("couldn't open the file ");
        exit(1);
    }
     while((c=fgetc(infile))!=EOF)//counting the lines in the file to make nodes as needed.
    {
        if(c =='\n')
            numberoflines++;
    }
    numberoflines++;//increament one for the last line
    rewind(infile);//to restart the crosser that i can read again.
    int i=0;//for the loop
    char countryname[30];//this varriables to hold the values form the file
    float mag,lat,lon;//this varriables to hold the values form the file
    int tsu;//this varriables to hold the values form the file
    while(i<numberoflines)
    {
        fscanf(infile,"%[^,],%f,%f,%f,%d",countryname,&mag,&lat,&lon,&tsu);
        //printf("%s %f %f %f %d\n",countryname,mag,lat,lon,tsu);//if you want to check if I am reading correctly or not
        tree=insertEarthquake(countryname,mag,lat,lon,tsu,tree);//sending the data to insert them in the tree one by one.
        i++;
    }
    fclose(infile);//closing the file not to take space
    return tree;//returning the full tree




}
t* insertEarthquake(char countryname[30],float mag,float lat,float lon,int tsu,t* tree)
{
     if (tree == NULL)//if my tree is empty, or the place that i am going to is empty
        {
                /*Create and return a one-node tree */
                tree= (t*)malloc(sizeof(t));
                if (tree == NULL)
                        printf("Out of memory space!!!\n");
                else//assign the data
                {
                        strcpy(tree->place,countryname);
                        tree->ma=mag;
                        tree->la=lat;
                        tree->lo=lon;
                        tree->ts=tsu;
                        tree->height = 0;
                        tree->left = tree->right = NULL;
                        tree->side=NULL;
                }
        }
         else if (strcmp(countryname,tree->place)==-1)//if the value of the name is less that my root
        {
                tree->left = insertEarthquake(countryname,mag,lat,lon,tsu,tree->left);//move to the left

                if (AVLTreeHeight(tree->left) - AVLTreeHeight(tree->right) == 2)//the left side is heavier
                {

                    if (strcmp(countryname,tree->left->place)==-1)//if the node before it is heavy on the left as well
                            tree = SingleRotateWithLeft(tree);//we will have LL case with single rotation
                    else
                            tree = DoubleRotateWithLeft(tree);//else, that means we will have LR
                }
        }
        else if (strcmp(countryname,tree->place)==1)//the name of the country is bigger than the root
        {
                tree->right = insertEarthquake(countryname,mag,lat,lon,tsu,tree->right);//we go right
                if (AVLTreeHeight(tree->right) - AVLTreeHeight(tree->left) == 2)//the right side is heavier
                {
                    if (strcmp(countryname,tree->right->place)==1)//the node before it is going to be heavy on the right
                            tree = SingleRotateWithRight(tree);//RR
                    else
                            tree = DoubleRotateWithRight(tree);//RL


                }
        }
        /* else contryname is in the tree already  so insert the data to linked list...  */

        else//because we know that strcmp will return 1,-1,0 so now we will study 0 case that when they are the same
        {

            n *linked;//declaring a pointer  for linked list
            n *temp;//declaring a pointer  for linked list
                linked=(n*)malloc(sizeof(n));//creating a new node to hold the data
                if(linked==NULL)
                {
                    printf("not able to allocate memory");
                    exit(1);
                }
                linked->next=NULL;
                linked->ma=mag;
                linked->la=lat;
                linked->lo=lon;
                linked->ts=tsu;
            if(tree->side==NULL)//tree->side will be as head
            {
                tree->side=linked;//assign the head to the data(make connection between the tree node and linked list.
            }
            else
            {

                temp=tree->side;//assign temp to the head
                while(temp->next!=NULL)//move until you find an empty slot
                    temp=temp->next;
                temp->next=linked;//connect the linked list together


            }
        }
        tree->height = Max(AVLTreeHeight(tree->left), AVLTreeHeight(tree->right)) + 1;//we update the height
        return tree;//we return the tree that we have so far to readdata function.

}
void displayIndex(t* tree)//in-order displaying.
{
    if(tree==NULL)//that means we don't have tree(which means the file is empty, which doesn't make sense.
    {
        return;
    }
    displayIndex(tree->left);//calling the left side of the tree
    printf("%s %.1f %.4f %.4f %d",tree->place,tree->ma,tree->la,tree->lo,tree->ts);//printing the nodes
    if(tree->side!=NULL)//if there is more than one data for the same country
    {
        n *temp=tree->side;//we make a temp which is going to point to the head
        while(temp!=NULL)
        {
            printf("%s %.1f %.4f %.4f %d",tree->place,temp->ma,temp->la,temp->lo,temp->ts);//we print the data, but i don't know if you want it using( ; )or space
            temp=temp->next;
        }
    }
     displayIndex(tree->right);//we call the right side of the tree
     printf("\n");
     //i wanted to make it in the same way as we have in the sample run but it didn't happen, I hope you give me feedback about it.

}
void dangerousplacemax(t* tree,int pmax,int *nmax)//previous max and new max to find the maximum number of nodes each country has
{
    if(tree!=NULL)//checking if my tree is not NULL
    {
        dangerousplacemax(tree->left,pmax,nmax);//calling the left side with the pointer that is going to be updated
        dangerousplacemax(tree->right,pmax,nmax);//calling the right side with the pointer that is going to be updated
        if(tree->side!=NULL)//that means the country has more than one data
        {
            n* temp=tree->side;//make a temp that is going to point to the head
            pmax++;//increase by one because we have already the tree node
            while(temp->next!=NULL)//that we don't print something doesn't exist.
            {
                temp=temp->next;
                pmax++;//increase the counter
            }
            if(*nmax<pmax)//if the country has more data than the max that we have that means we will update our max.
                *nmax=pmax;
        }
    }
}
void dangerousPlace(t* tree,int pmax,int nmax)//previous max and new max to print the max number of nodes for specific country
{//the complexity of this function is O(n^3) because is going to call the function n times according to the nodes we have and we have two loops to search and print as well.
    //to improve this, I believe we can make the country with duplicate nodes on the right that we can check them easier by searching only in the right side.
    //this function can't be written alone without an if condition that is going to findmax and display in the same time(which i couldn't find) so i used additional function.
    if(tree!=NULL)//we repeat the same procedure but with printing and equal sign.
    {
        dangerousPlace(tree->left,pmax,nmax);
        dangerousPlace(tree->right,pmax,nmax);
        if(tree->side!=NULL)
        {
            n* temp=tree->side;
            pmax++;
            while(temp->next!=NULL)//n
            {
                temp=temp->next;
                pmax++;
            }
            if(nmax==pmax)
                {
                    printf("%s %.1f %.4f %.4f %d",tree->place,tree->ma,tree->la,tree->lo,tree->ts);
                    temp=tree->side;
                    while(temp!=NULL)//n^2
                    {
                    printf("%s %.1f %.4f %.4f %d",tree->place,temp->ma,temp->la,temp->lo,temp->ts);
                    temp=temp->next;
                    }
                }
        }

    }

}
void weakestEarthqukemin(t* tree, float * nearth)//new earth=nearth to find the minimum value of the earthquacke  which is going to be pointer that we can compare with it later.
{
    if(tree!=NULL)//checking if we have data in the file or not.
    {
        weakestEarthqukemin(tree->left,nearth);//calling the left side that we can traverse the whole tree.
        weakestEarthqukemin(tree->right,nearth);////calling the left side that we can traverse the whole tree.
        if(tree->ma<*nearth)//checking if the magnitude of the node in the tree is less or not to update nearth.
            *nearth=tree->ma;
        if(tree->side!=NULL)//if the country has more than one node
        {
            n* temp=tree->side;
            while(temp->next!=NULL)//That we can go over all the nodes
            {
                if(temp->ma<*nearth)//we check if the magnitude is less that we can update.
                    *nearth=temp->ma;
                temp=temp->next;


            }
        }
    }
}
void weakestEarthquke(t* tree, float nearth)//this is the main function that is going to print the country with the lowest earthqucke.
{//this function is going to traverse the whole tree until it finds the minimum magnitude, so the best case is that the root with the mimum magnitude and it doesn't have any node connected so it will be o(1)
    //it is hard to spot the avg case, but for the worse case I believe it should go until the last child which has nodes, so is going to be O(n^2)
    //to improve this function, I think we can have else condtion when the tree is NULL and compute the whole values in one function.
    if(tree!=NULL)//same procedure as before, but with printing and with equal signs to check.
    {
        weakestEarthquke(tree->left,nearth);
        weakestEarthquke(tree->right,nearth);
        if(tree->ma==nearth)
            printf("%s %.1f %.4f %.4f %d\n",tree->place,tree->ma,tree->la,tree->lo,tree->ts);//printing extra newline here if we have two countries which have the lowest magnitude value
        if(tree->side!=NULL)
        {
            n *temp=tree->side;
            while(temp->next!=NULL)
            {
                if(temp->ma==nearth)
                    printf("%s %.1f %.4f %.4f %d\n",tree->place,temp->ma,temp->la,temp->lo,temp->ts);//printing extra newline here if we have two countries which have the lowest magnitude value
                temp=temp->next;
            }
        }

    }
}
