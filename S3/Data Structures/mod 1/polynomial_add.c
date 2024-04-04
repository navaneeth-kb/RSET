#include <stdio.h>
#include <stdlib.h>
struct poly
{
    int expo;
    int coef;
};
struct poly p1[20],p2[20],p3[20];
void main()
{
    int t1,t2;
    printf("\nInput poly 1");
    printf("\nEnter num of term of poly 1:");
    scanf("%d",&t1);
    for(int i=0;i<t1;i++)
    {
        printf("input coef and expo:");
        scanf("%d",&p1[i].coef);
        scanf("%d",&p1[i].expo);
    }
    printf("\nInput poly 2");
    printf("\nEnter num of term of poly 2:");
    scanf("%d",&t2);
    for(int i=0;i<t2;i++)
    {
        printf("input coef and expo:");
        scanf("%d",&p2[i].coef);
        scanf("%d",&p2[i].expo);
    }
    int i=0,j=0,k=0;
    while(i<=t1 && j<=t2)
    {
        if(p1[i].expo>p2[j].expo)
        {
            p3[k].expo=p1[i].expo;
            p3[k].coef=p1[i].coef;
            k++;
            i++;
        }
        else if(p1[i].expo<p2[j].expo)
        {
            p3[k].expo=p2[j].expo;
            p3[k].coef=p2[j].coef;
            k++;
            j++;
        }
        else
        {
            p3[k].expo=p1[i].expo;
            p3[k].coef=p1[i].coef+p2[j].coef;
            k++;
            i++;
            j++;
        }
    }
    while(i<t1)
    {
        p3[k].expo=p1[i].expo;
        p3[k].coef=p1[i].coef;
        k++;
        i++;
    }
    while(j<t2)
    {
        p3[k].expo=p2[j].expo;
        p3[k].coef=p2[j].coef;
        k++;
        j++;
    }
    printf("\nadded poly:");
    for(i=(k-1);i>=1;i--)
    {
        printf("%dx^%d+",p3[i].coef,p3[i].expo);
    }
    printf("%dx^%d",p3[i].coef,p3[i].expo);
}
