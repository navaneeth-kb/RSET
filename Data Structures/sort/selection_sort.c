#include<stdio.h>
int a[50],max=0;
void selection_sort()
{
    int min,i;
    for(int i=0;i<max-1;i++)
    {
        int min=i;
        for(int j=i+1; j<max;j++)
        {
            if(a[min]>a[j])
            {
                min=j;
            }
        }
        int temp=a[min];
        a[min]=a[i];
        a[i]=temp;
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
    selection_sort();
    printf("\nthe array elements are:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
}
