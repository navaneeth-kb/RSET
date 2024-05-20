#include <sys/shm.h>
#include <stdio.h>
void main()
{
    int i, n, r, fact=1, fact1=1, *shared_memory, buff[100], shmid;
    key_t key = 111;
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    shared_memory = (int *)shmat(shmid, NULL, 0);
    printf("Enter the integer n:");
    scanf("%d",&n);
    shared_memory[1]=n;
    for(i=1;i<=n;i++)
    {
        fact=fact*i;
    }
    shared_memory[2] = fact;
    printf("The factorial is:");
    printf("%d\n", shared_memory[2]);
    printf("Enter the integer r:");
    scanf(&quot;%d&quot;, &amp;r);
    shared_memory[3]=r;
    for(i=1;i&lt;=r;i++)
    {
        fact1=fact1*i;
    }
    shared_memory[4] = fact1;
    printf("The factorial is:");
    printf("%d\n", shared_memory[4]);
}