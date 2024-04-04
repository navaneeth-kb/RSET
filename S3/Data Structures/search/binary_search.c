int max=0,a[50];
void bin_search(int ele)
{
    int low=0;
    int high=max-1;
    while(low<high)
    {
        int mid=(low+high)/2;
        if(a[mid]==ele)
        {
            printf("found");
            break;
        }
        else if(a[mid]>ele)
        {
            high=mid-1;
        }
        else if(a[mid]<ele)
        {
            low=mid+1;
        }
    }
    if(low>high)
    {
        printf("not found");
    }

}
void bubble_sort()
{
    int i,j;
    for(i=0;i<max-1;i++)
    {
        for(j=0;j<max-i-1;j++)
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
    printf("Enter array elements:");
    for(int i=0;i<max;i++)
    {
        scanf("%d",&a[i]);
    }
    bubble_sort();
    printf("array elements:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }

    printf("Enter value:");
    int ele;
    scanf("%d",&ele);
    bin_search(ele);
}
