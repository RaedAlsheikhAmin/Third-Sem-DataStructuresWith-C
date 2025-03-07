//RAED ALSHEIKH AMIN-2528271-PRACTICAL ASSIGNMENT 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
//important notes
/*
my load function doesn't work perfectly and the data will be like that.
country1->data
.
.
country2->data
.
.
country2->data
.
.
country2->data
.
.
country7->data
.
.
country6->data
.
.
oceanx->data


*/

struct info//structure info which is gonna make the nodes that have the informations of earthquakes.
{
    int year;
    int month;
    int day;
    float magnitude;
    float lattitude;
    float logitude;
    int tsunami;
    struct info *next;//to have the next node.
};

struct country{//structure country which is gonna make the node of the country which has the name.
    char countryname[50];
    struct country *down;//it refers to the countries in the first column.
    struct info *side;//it connect each country with each info that it has.
    };
typedef struct country CO;//to make it easier to use.(co instead of all the structure)
typedef struct info inf;//to make it easier to use.(inf instead of all the structure)





CO* load_data(char[]);
void remove_earthquake(CO*,float);
void count_earthquakes(CO*,char[]);//it will take a string to search for the name
float average_magnitude(CO*,char[]);//it will search for specific country and return the avg magnitude.

int main()
{
    FILE *infile;//declaring the varriable of the file
    char filename[20];//declaring the string of the file name.
    CO *con;//my structure pointer of country in main function
    float threshold;
    int operation;
    char countrysearch[20];
    printf("Welcome to Earthquakes Data Analysis Program \n");
    printf("Enter file name: ");
    gets(filename);//to get the file name from the user.
    while((infile=fopen(filename,"r"))==NULL)//to check if the file name is correct or not and re-ask the user to enter again.
    {
        printf("error, the file is not existed\n");
        printf("Enter file name: ");
        gets(filename);
    }
    fclose(infile);//to close the file.

    con=load_data(filename);//calling the function and assigning the strucutre that is returned to a strucutre pointer that i will use.
    printf("The earthquake characteristics is successfully loaded. \n");
    do
    {

        printf("---------------------------------------------------------------\nOperations Menu\n---------------------------------------------------------------\n1. Remove Earthquake\n2. Show Statistics\n3. Exit");
        printf("\nEnter your option: ");
        fflush(stdin);
        scanf("%d",&operation);
        if(operation==1)
        {
            printf("\nEnter a threshold value for the magnitude: ");
            scanf("%f",&threshold);//taking the value from the user to compare
            remove_earthquake(con,threshold);//calling the function.
        }
        else if(operation==2)
        {
            printf("Enter a user name: ");
            fflush(stdin);
            scanf("%s",countrysearch);//take the countryname from the user to search in the linked list.
            count_earthquakes(con,countrysearch);//calling the function.
            printf("The average of earthquake magnitude is: %.2f\n",average_magnitude(con,countrysearch));//calling and printing the avg function
        }
    }while(operation!=3);
    printf("See you, bye bye!");

}






CO* load_data(char filename[20])//the function that takes the file name and returns a structure pointer which is country.
{
    int numberoflines=0;//varriable to count the number of lines.
    char c;//character to go over the file.
    FILE *infile;//declaring the file
    CO *countrys;//s refers to structure
    inf *infos;//s refers to strucutre

    infile=fopen(filename,"r");//opening the file to read from it
    if(infile==NULL)//checking if the file opened correctly or not.
    {
        printf("couldn't proceed to the file");
        exit(1);
    }

    while((c=fgetc(infile))!=EOF)//counting the lines in the file to make nodes as needed.
    {
        if(c =='\n')
            numberoflines++;
    }
    numberoflines++;
    rewind(infile);//to restart the crosser that i can read again.
    int i=0;
    CO *h1=NULL;//it goes down
    inf *h2=NULL;//right
    CO *temp1=NULL;//it is gonna keep the list connected and go down
    inf *temp2=NULL;//it is gonna go right


    while(i<numberoflines)//numberoflines=number of nodes that we are going to make
    {
        countrys=(CO*)malloc(sizeof(CO));//creating nodes for the country columns
        infos=(inf*)malloc(sizeof(inf));//creating nodes for the info columns

        fscanf(infile,"%[^,],%d,%d,%d,%f,%f,%f,%d",countrys->countryname,&(infos->year),&(infos->month),&(infos->day),&(infos->magnitude),&(infos->lattitude),&(infos->logitude),&(infos->tsunami));//reading from the file.
        i++;
        countrys->down=NULL;//every time we make a node we set node down to null.
        countrys->side=NULL;//we set node side that points to another node to null.
        infos->next=NULL;//the other node which is infos points to null.


        if(h1==NULL && h2==NULL)//it will be executed once.
           {
            h1=countrys;//h1 is a pointer that has the value of countrys to go over the linked list.
            h2=infos;//h2 is a pointer that has the value of infos to go over the linked list

            }
        else
        {
            temp1=h1;
            temp2=h2;
            while((temp1->down)!=NULL )
            {
                temp1=temp1->down;//to connect the countries together.
                temp2=temp2->next;//to connect the info together if we have more than one.
                }
            temp1->side=temp2;//to connect both nodes together
            temp1->down=countrys;//to connect countrys together
            temp2->next=infos;//to connect infos
        }//end of else

    }//end of while
    countrys->side=infos;//countrys and infos are the tails of my program.//this command to connect the last country with the infos.


return h1;
}

void remove_earthquake(CO* h1,float threshold)//the function to remove earthquake which means removing the countryies.
{
 CO *temp1=h1;
 CO *temp2=h1;
 CO *deletenodecountry;
 int countofremovednodes=0,i=0;
 while(temp1!=NULL)
 {
     if((temp1->side->magnitude<threshold) &&(temp1->side!=NULL))
     {
         deletenodecountry=temp1;//to specify the node to delete.
         temp2->down=deletenodecountry->down;//to connect
         free(deletenodecountry);//to delete the nood
         countofremovednodes++;//number of nodes deleted.
     }
     if(i==1)
     {
     	temp2=temp2->down;
	 }
     temp1=temp1->down;
     i=1;
 }
 printf("The number of removed nodes: %d\n",countofremovednodes);
}

void count_earthquakes(CO* h1,char countryname[20])//function to count earthquakes for a specific country.
{
CO *temp1=h1;
CO *search;
search=(CO *)malloc(sizeof(CO));//i tried to make a node the strcmp works but it is not.
strcpy(search->countryname,countryname);//copying the data from the user to a node to use strcmp
int countearth=0,counttsunami=0;

    while(temp1!=NULL)
    {
        if(strcmp(search->countryname,temp1->countryname)==0)//to compare two strings.
        {
            countearth++;
             if((temp1->side->tsunami)==1)
        {
            counttsunami++;
        }
        }


        temp1=temp1->down;//to go over the linked list
    }
    printf("The number of earthquake is: %d and the Tsunami is %d\n", countearth,counttsunami);
}
float average_magnitude(CO *h1,char countryname[20])
{
    CO *temp1=h1;
    float avg=0;
    int count=0;
    int valid=0;
    while(temp1!=NULL)
    {
        if(strcmp(temp1->countryname,countryname)==0)
            {
                avg+=temp1->side->magnitude;
                count++;
                valid=1;
            }
            temp1=temp1->down;
}
if(valid==0)//that means the country is not in the list
    return 0;


return (avg/count);


}

