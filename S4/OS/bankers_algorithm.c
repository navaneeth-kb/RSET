#include <stdio.h>
#include <stdbool.h>

int P,R;
void calculateNeed(int need[P][R],int max[P][R],int allot[P][R])
{
	for(int i=0;i<P;i++)
	{
		for(int j=0;j<R;j++)
		{
			need[i][j]=max[i][j]-allot[i][j];
			printf("%d\t",need[i][j]);
		}
		printf("\n");
	}
	
}
bool isSafe(int processes[],int avail[],int max[][R],int allot[][R])
{
	int need[P][R];
	calculateNeed(need,max,allot);
	bool finish[P];
	int safeSeq[P];
	int work[R];
	for(int i=0;i<R;i++)
	{
		work[i]=avail[i];
	}
	int count=0;
	while(count<P)
	{
		bool found=false;
		for(int p=0;p<P;p++)
		{
			if(!finish[p])
			{
				int j;
				for(j=0;j<R;j++)
				{
					if(need[p][j]>work[j])
					{
						break;
					}
				}
			
				if(j==R)
				{	
					for(int k=0;k<R;k++)
					{
						work[k]+=allot[p][k];
					}
					safeSeq[count++]=p;
					finish[p]=1;
					found=true;
					
				}
			}
		}
		if(!found)
		{
			printf("System is not in safe state\n");
			return false;
		}
	}
	printf ("Systemis in safe state.\n Safe sequense is:");
	for(int i=0;i<P;i++)
	{
		printf("%d\t",safeSeq[i]);
		
	}
	printf("\n");
	return true;
}
int main()
{
	printf("Enter the number of processes:");
	scanf("%d",&P);
	int processes[P];
	printf("enter the no of resources:");
	scanf("%d",&R);
	for(int i=0;i<P;i++)
	{
		processes[i]=i;
	}
	int avail[R];
	printf("Enter the available resources(total %d type):",R);
	for(int i=0;i<R;i++)
	{
		scanf("%d",&avail[i]);
	}
	int max[P][R];
	int allot[P][R];
	printf("Enter the maximum resource matrix (%d processes and %d resources types):\n",P,R);
	for(int i=0;i<P;i++)
	{
		printf("Process %d:",i);
		for(int j=0;j<R;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	printf("Enter the allocation matrix(%d processes and %d resource types):\n",P,R);
	for(int i=0;i<P;i++)
	{
		printf("Process %d:",i);
		for(int j=0;j<R;j++)
		{
			scanf("%d",&allot[i][j]);
		}
	}
	if (isSafe(processes,avail,max,allot))
	{
		printf("the system can allocate resources safely\n");
	}
	else
	{
		printf("The system cannot allocate resources safely\n");	
	}
	return 0;
}
