#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
int main()
{
    int a=1, b=1, c=1, d=1, ncr, fact=1, *shared_memory, buff[100],
    shmid;
    key_t key = ftok(&quot;/home/s4csc/navi&quot;, 78);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    shared_memory = (int *)shmat(shmid, NULL, 0);

    a=shared_memory[1];
    b=shared_memory[2];
    c=shared_memory[3];
    d=shared_memory[4];
    int t=a-c;
    for(int i=1; i&lt;=t; i++)
    {
        fact=fact*i;
    }
    ncr=(b/d)/fact;
    printf(&quot;The number is %d\n&quot;,ncr);
}