#include<stdio.h>
int a[50],max=0;
void bubble_sort()
{
    for(int i=0;i<max-1;i++)
    {
        for(int j=0; j<max-1-i;j++)
        {
            if(a[j+1]<a[j])
            {
                int temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}
void main()
{
    printf("Enter max value:");
    scanf("%d",&max);
    printf("\nEnter array elements");
    for(int i=0;i<max;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("\nthe array elements are:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
    bubble_sort();
    printf("\nthe array elements are:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
}
