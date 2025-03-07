//question 2
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define Pi 3.14
void calculate_volume_surface(double rad, double *vol, double *surface);

int main()
{

    double rad,vol,surface;
    printf("give me the value of the radius: ");
    scanf("%lf",&rad);
    calculate_volume_surface(rad,&vol,&surface);

    printf("\nthe volume is %lf and the surface is %lf",vol,surface);


return 0;

}
void calculate_volume_surface(double rad, double *vol, double *surface)
{

    *vol=(4.0/3.0)*Pi*pow(rad,3);
    *surface=4.0*Pi*rad*rad;


}
