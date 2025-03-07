//question 3
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void find_largest_smallest(int a[], int n, int *largest, int *smallest);
int main()
{
    int *a,n,i,smallest,largest;

    printf("elements you want to store: ");
    scanf("%d",&n);

    a=(int*)malloc(sizeof(int)*n);

    if(a==NULL)
    {
        printf("error");
        exit(1);

    }

    for(i=0;i<n;i++)
    {
        printf("enter a value to be stored in 1st: ");
        scanf("%d",(a+i));
    }
    find_largest_smallest(a,n, &largest, &smallest);

printf("the smallest value is %d and the largest value is %d",smallest,largest);

    return 0;
}



void find_largest_smallest(int a[], int n, int *largest, int *smallest)
{
    int i,temp1,temp2;
    *smallest=a[0];
    *largest=a[0];
    for(i=1;i<n;i++)
    {
        if(*largest<a[i])
            *largest=a[i];
        else
            *smallest=a[i];

    }

}
