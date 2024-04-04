#include <stdio.h>   
int max=0,a[50],b[50];
void merge_sort(int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        merge_sort(low,mid);
        merge_sort(mid+1,high);
        merge(low,mid,high);
    }
}

void merge(int low, int mid, int high) 
{
    int i = low;
    int x = low;
    int y = mid + 1;

    while (x <= mid && y <= high) {
        if (a[x] <= a[y]) {
            b[i] = a[x];
            x++;
        } else {
            b[i] = a[y];
            y++;
        }
        i++;
    }

    // Copy remaining elements from the left subarray
    while (x <= mid) {
        b[i] = a[x];
        x++;
        i++;
    }

    // Copy remaining elements from the right subarray
    while (y <= high) {
        b[i] = a[y];
        y++;
        i++;
    }

    // Copy merged elements back to the original array
    for (i = low; i <= high; i++) {
        a[i] = b[i];
    }
}

void main()
{
    printf("Enter max value:");
    scanf("%d",&max);
    printf("Enter array elements:");
    for(int i=0;i<max;i++)
    {
        scanf("%d",&a[i]);
    }

    printf("\narray elements:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
    merge_sort(0,max-1);
    printf("\narray elements:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
}
