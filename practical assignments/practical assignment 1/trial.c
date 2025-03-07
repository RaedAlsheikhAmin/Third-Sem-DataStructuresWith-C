//RAED ALSHEIKH AMIN-2528271-PRACTICAL ASSIGNMENT 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
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

int main()
{
    FILE *infile;//declaring the varriable of the file
    char filename[20];//declaring the string of the file name.
    CO *con;//my structure pointer of country in main function
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
    //printf("\n hi hi\n %d",(con->down->down->side->tsunami));//this for checking if my linked list is working or not.
    printf("The earthquake characteristics is successfully loaded. \n---------------------------------------------------------------\n");
    printf("Operations Menu\n---------------------------------------------------------------\n1. Remove Earthquake\n2. Show Statistics\n3. Exit");
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

        fscanf(infile,"%[^,],",countrys->countryname);//reading from the file.
        if(countrys->down!=NULL)
        {
            if(strcmp(countrys->countryname,countrys->down->countryname)==0)
               {
                   infos=(inf*)malloc(sizeof(inf));
                   fscanf(infile,"%d,%d,%d,%f,%f,%f,%d",&(infos->year),&(infos->month),&(infos->day),&(infos->magnitude),&(infos->lattitude),&(infos->logitude),&(infos->tsunami));
                    countrys->side=infos;




               }


        }
        printf("%s,%d,%d,%d,%f,%f,%f,%d\n\n",(countrys->countryname),infos->year,(infos->month),(infos->day),(infos->magnitude),(infos->lattitude),(infos->logitude),(infos->tsunami));
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
            temp1->down=countrys;//
            temp2->next=infos;
        }

    }
return h1;
}

