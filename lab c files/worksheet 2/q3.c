//question 3
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
struct RGB_Image
{
    int r[5][5];
    int g[5][5];
    int b[5][5];
};
typedef struct RGB_Image rgb;
rgb* formRGBImage(int);
void display(rgb*,int);
void AverageOfChannels(rgb*,int);
int main ()
{
   rgb *RGB;
   int numimage;
   printf("Enter the number of images you want: ");
   scanf("%d",&numimage);

   RGB=formRGBImage(numimage);
   display(RGB, numimage);
   AverageOfChannels(RGB,numimage);






    return 0;

}
rgb * formRGBImage(int numimage)
{
    srand(time(NULL));
    rgb *RGB2;
    int i=0,k=0,j=0;
    RGB2=(rgb *)malloc(sizeof(rgb)*numimage);
    if(RGB2==NULL)
    {
        printf("error");
        exit(1);
    }
    while(i<numimage)
    {
        while(k<5)
        {
            while(j<5){
                RGB2[i].r[k][j]=rand()%256;
                RGB2[i].g[k][j]=rand()%256;
                RGB2[i].b[k][j]=rand()%256;
            j++;
            }
            k++;
            j=0;
       }
       i++;
       k=0;
    }
    return RGB2;

}
display(rgb * RGB,int numimage)
{
    int i=0,k=0,j=0;
    while(i<numimage)
    {
        printf("Image %d: R\n",(i+1));
        while(k<5)
        {
            while(j<5){
                printf("%d ",RGB[i].r[k][j]);
            j++;
            }
            printf("\n");
            k++;
            j=0;
       }
       k=0;
        printf("Image %d: G\n",(i+1));
        while(k<5)
        {
            while(j<5){
                printf("%d ",RGB[i].g[k][j]);
            j++;
            }
            printf("\n");
            k++;
            j=0;
       }
       k=0;
        printf("Image %d: B\n",(i+1));
        while(k<5)
        {
            while(j<5){
                printf("%d ",RGB[i].b[k][j]);
            j++;
            }
            printf("\n");
            k++;
            j=0;
       }
       i++;
       k=0;
    }

}
void AverageOfChannels(rgb* RGB,int numimage)
{
    int avgr=0,avgb=0,avgc=0,i=0,k=0,j=0;
     while(i<numimage)
    {
        while(k<5)
        {
            while(j<5){
                avgr=RGB[i].r[k][j]+avgr;
            j++;
            }
            k++;
            j=0;
       }
       k=0;
        while(k<5)
        {
            while(j<5){
                avgb=RGB[i].g[k][j]+avgb;
            j++;
            }
            k++;
            j=0;
       }
       k=0;
        while(k<5)
        {
            while(j<5){
                avgc=RGB[i].b[k][j]+avgc;
            j++;
            }
            k++;
            j=0;
       }
       printf("\n");
    printf("Image %d: R=%d, G=%d, B=%d\n",(i+1),(avgr/25),(avgb/25),(avgc/25));
       i++;
       k=0;
    }
}
