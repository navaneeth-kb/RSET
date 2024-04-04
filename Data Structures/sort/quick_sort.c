int a[50],max=0;
void quick_sort(int low,int high)
{
    int j;
    if(low<high)
    {
        j=partition(low,high);
        quick_sort(low,j-1);
        quick_sort(j+1,high);
    }
}
int partition(int low,int high)
{
    int i=low+1;
    int j=high;
    int pivot=low;
    while(i<=j)
    {
        while(a[i]<=a[pivot])
        {
            i++;
        }
        while(a[j]>a[pivot])
        {
            j--;
        }
        if(i<j)
        {
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }

    }
    int temp=a[j];
    a[j]=a[low];
    a[low]=temp;
    return j;
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
    quick_sort(0,max-1);
    printf("\narray elements:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }
}
