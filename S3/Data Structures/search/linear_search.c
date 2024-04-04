int max=0,a[50];
void linear_search(int ele)
{
    int flag=0;
    for(int i=0;i<max;i++)
    {
        if(a[i]==ele)
        {
            printf("found");
            flag=1;
            break;
        }

    }
    if(flag==0)
    {
        printf("not found");
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

    printf("array elements:");
    for(int i=0;i<max;i++)
    {
        printf("%d\t",a[i]);
    }

    printf("Enter value:");
    int ele;
    scanf("%d",&ele);
    linear_search(ele);
}
