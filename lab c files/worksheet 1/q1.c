//question 1
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int inner_product(int *a,int *b,int n);
int main()
{
    int *a,*b,n,i;

    printf("elements you want to store: ");
    scanf("%d",&n);

    a=(int*)malloc(sizeof(int)*n);

    if(a==NULL)
    {
        printf("error");
        exit(1);

    }
     b=(int*)malloc(sizeof(int)*n);

    if(b==NULL)
    {
        printf("error");
        exit(1);
    }
    for(i=0;i<n;i++)
    {
        printf("enter a value to be stored in 1st: ");
        scanf("%d",(a+i));
    }
    for(i=0;i<n;i++)
    {
        printf("enter a value to be stored in 2nd: ");
        scanf("%d",(b+i));
}

printf("result is %d",inner_product(a,b,n));
    return 0;
}



int inner_product(int *a,int *b,int n)
{
    int i;
    int sum=0;

    for(i=0;i<n;i++)
    {

        sum=sum+(a[i]*b[i]);

    }
    return sum;


}
