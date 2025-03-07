//question a
#include <stdio.h>
#include <stdlib.h>

//To represent an empty stack, EMPTY_TOS -1 is used
#define EMPTY_TOS -1
//Minimim stack size should be 5
#define MIN_STACK_SIZE 5
#define FALSE 0
#define TRUE 1

//Stack record that holds the following data:
//the capacity of the stack,
//the index of the top of stack and
//the array to hold the data in the stack

struct StackRecord
{
        int capacity;
        int topOfStack;
        int *array;
};


typedef struct StackRecord *Stack;

//Function signatures
Stack CreateStack(int);
void MakeEmptyStack(Stack);
void PushStack(int, Stack);
int PopStack(Stack);
int TopOfStack(Stack);
int IsFullStack(Stack);
int IsEmptyStack(Stack);
void DisplayStack(Stack);

int main()
{
        int stackSize;
        Stack myStack;
        int exit, val;
        char command;

        printf("Enter stack size: ");
        scanf("%d", &stackSize);
        myStack = CreateStack(stackSize);
        if (myStack == NULL)
                exit = TRUE;
        else
                exit = FALSE;

        while (!exit)
        {
                fflush(stdin);
                printf("\n(i)nitialize\n");
                printf("(p)ush\n");
                printf("(r)emove (pop)\n");
                printf("(t)op of stack\n");
                printf("(e)xit\n");
                printf("Enter command: ");
                scanf("%c", &command);
                fflush(stdin);

                switch (command)
                {
                case 'i':
                        MakeEmptyStack(myStack);
                        break;
                case 'p':
                        printf("enter value: ");
                        scanf("%d", &val);
                        PushStack(val, myStack);
                        break;
                case 'r':
                        val = PopStack(myStack);
                        break;
                case 't':
                        val = TopOfStack(myStack);
                        if (val != -1)
                                printf("top element is %d\n", val);
                        break;
                case 'e':
                        exit = TRUE;
                        break;
                default:
                        printf("command not recognized\n");
                        break;
                }
                DisplayStack(myStack);
        }

        printf("\n\n");
        system("PAUSE");
        return 0;
}

//This function initialises a stack by initialising the following:
//Initiliases the array that will hold the data
//Sets the capacity to the maximum number of elements
//Calls the makeEmptyStack function to initialise the top of stack to -1
Stack CreateStack(int maxElements)
{
        Stack s;

        if(maxElements<MIN_STACK_SIZE)
        {
                printf("Stack size is too samll\n");
                return NULL;

        }
        s=(struct StackRecord*)malloc (sizeof(struct StackRecord));
        if(s==NULL){
                printf("out of meomory");
                exit(1);
        }
        s->array=(int*)malloc(maxElements*sizeof(int));
        if(s->array==NULL){
                printf("out of meomory");
                exit(1);
        }

        s->capacity=maxElements;
        MakeEmptyStack(s);

        return s;

}

//Sets the top of stack to -1 which represents an empty stack
void MakeEmptyStack(Stack s)
{
        s->topOfStack=-1;

}

//Checks if a stack is empty. If the top of stack is -1 then the stack is empty.
int IsEmptyStack(Stack s)
{
                if(s->topOfStack==-1)
                        return 1;
                else return 0;
}

//Checks if a stack is full, if the top of stack is equal to the capacity then the stack is full
int IsFullStack(Stack s)
{
        if(s->topOfStack==s->capacity)
                        return 1;
                else return 0;
}

//Pushes the given element to the stack and increments the top of stack
void PushStack(int x, Stack s)
{

        if(IsFullStack(s))
        printf("The stack is full\n");

        else{


                s->array[++s->topOfStack]=x;
        }


}

//Pops and returns the top element in the stack and decrements the top of stack by one
int PopStack(Stack s)
{
        if(!IsEmptyStack(s))
                return s->array[s->topOfStack--];

        else
                printf("stack is empty");
}

//Returns the top of the stack
int TopOfStack(Stack s)
{
        if (!IsEmptyStack(s))
                return s->array[s->topOfStack];
        else{
                printf("The stack is empty\n");
                return -1;
        }
}

//Shows the content of the stack. This does not change the content of the stack.
void DisplayStack(Stack s)
{
        int i;
        printf("Stack content:\n");
        for (i = s->topOfStack; i >= 0; i--)
                printf("\t--> %d\n", s->array[i]);
}
