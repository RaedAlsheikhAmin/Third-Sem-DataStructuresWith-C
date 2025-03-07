//question 4
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void pay_month(int dollars, int *twenties, int *tens, int *fives, int *ones);

int main()
{
    int dollars,twenties=0,tens=0,fives=0,ones=0;
    printf("enter the amount to pay: ");
    scanf("%d",&dollars);


    pay_month(dollars, &twenties, &tens, &fives, &ones);
    printf("You need to pay %d x$20 + %d x$10 + %d x$5+ %d$",twenties,tens,fives,ones);

}
void pay_month(int dollars, int *twenties, int *tens, int *fives, int *ones)
{
    int reminder;
    *twenties=dollars/20;
    reminder=dollars%20;
    *tens=reminder/10;
    reminder=reminder%10;
    *fives=reminder/5;
    reminder=reminder%5;
    *ones=reminder;

}
