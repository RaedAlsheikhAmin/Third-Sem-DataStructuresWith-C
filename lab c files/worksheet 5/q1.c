#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct Node
{
        int  val;
        struct Node *next;
};

struct ListRecord
{
        struct Node *head;
        struct Node *tail;
        int size;
};

typedef struct ListRecord *List;

List CreateList(void);
void MakeEmptyList(List);
int ListSize(List);
int HeadOfList(List);
int TailOfList(List);
int IsEmptyList(List);
void DisplayList(List);
void InsertList(List,int ,int);

int main()
{
        List myList;
        int exit, val, pos;
        char command;

        myList = CreateList();
        exit = FALSE;

        while (!exit)
        {
                fflush(stdin);
                printf("\n(i)nitialize\n");
                printf("(n)ew element\n");
                printf("(d)elete element\n");
                printf("(f)ind element\n");
                printf("(p)osition of element\n");
                printf("(h)ead of list\n");
                printf("(t)ail of list\n");
                printf("(e)xit\n");
                printf("Enter command: ");
                scanf("%c", &command);
                fflush(stdin);

                switch (command)
                {
                case 'i':
                        MakeEmptyList(myList);
                        break;
                case 'n':
                        printf("enter value: ");
                        scanf("%d", &val);
                        printf("enter position: ");
                        scanf("%d", &pos);
                        InsertList(myList, pos, val);
                        break;
                case 'd':
                        printf("enter value: ");
                        scanf("%d", &val);
                        //DeleteList(myList, val);
                        break;
                case 'p':
                        printf("enter value: ");
                        scanf("%d", &val);
                        //pos = GetPositionOfElement(myList, val);
                        if (pos > 0)
                                printf("element %d at position %d\n", val, pos);
                        break;
                case 'f':
                        printf("enter position: ");
                        scanf("%d", &pos);
                        //val = GetElementAtPosition(myList, pos);
                        if (val >= 0)
                                printf("element at position %d is %d\n", pos, val);
                        break;
                case 'h':
                        val = HeadOfList(myList);
                        if (val != -1)
                                printf("front element is %d\n", val);
                        break;
                case 't':
                        val = TailOfList(myList);
                        if (val != -1)
                                printf("rear element is %d\n", val);
                        break;
                case 'e':
                        exit = TRUE;
                        break;
                default:
                        printf("command not recognized\n");
                        break;
                }
                DisplayList(myList);
        }

        printf("\n");
        system("PAUSE");
        return 0;
}

List CreateList()
{
        List l;//l is a structure of list record

        l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
        if (l == NULL)//checking for the memory allocation
                printf("Out of memory!\n");
    else
            MakeEmptyList(l);

        return l;
}

void MakeEmptyList(List l)
{
        l->head = (struct Node *) malloc(sizeof(struct Node));//dummy node
        if (l->head == NULL)//checking for memory
                printf("Out of memory!\n");

        l->head->next = NULL;
        l->tail = l->head;
        l->size = 0;
}

int IsEmptyList(List l)
{
        return (l->size == 0);
}

int ListSize(List l)
{
        return (l->size);
}

int HeadOfList(List l)
{
        if (!IsEmptyList(l))
                return l->head->next->val;
        else
        {
                printf("The linked list is empty\n");
                return -1;
        }
}

int TailOfList(List l)
{
        if (!IsEmptyList(l))
                return l->tail->val;
        else
        {
                printf("The linked list is empty\n");
                return -1;
        }
}

void DisplayList(List l)
{
        struct Node *p;

        p = l->head->next;
        printf("List content:\n");

        while (p != NULL)
        {
                printf("--> %d\t", p->val);
                p = p->next;
        }
        printf("\n");
}

void InsertList(List l,int pos, int val)

{
        struct Node *insert, *temp;
        int i;
        insert=(struct Node *)malloc(sizeof(struct Node));
        if(insert==NULL)
        {
                printf("error");
                exit(1);
        }
        insert->val=val;
        insert->next=NULL;

        if(pos > ((l->size)+1))//insert at the end of the list if the it is bigger.
                {
                        pos=((l->size)+1);
                }
        if(pos==(l->size)+1)//insert at the end of the list
        {
                l->tail->next=insert;
                l->tail=insert;
        }
        else//insert in the middle
        {
                temp=l->head;//because it can be at the begginig.
                for(i=1;i<pos;i++)
                {
                        temp=temp->next;
                }
                insert->next=temp->next;
                temp->next=insert;
        }
        l->size++;

}
