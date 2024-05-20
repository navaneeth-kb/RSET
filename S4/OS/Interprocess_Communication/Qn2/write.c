#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main()
{
    int i;
    char *shared_memory;
    char buff[100];
    int shmid;
    key_t key=111;
    shmid=shmget(key, 1024, 0666|IPC_CREAT);
    shared_memory=shmat(shmid,NULL,0);
    printf(&quot;Enter some data to write to shared memory\n&quot;);
    read(0,buff,100);
    strcpy(shared_memory,buff);
    for(i=0;shared_memory[i]!=&#39;\0&#39;;i++){}
    i=i-1;
    printf(&quot;Length is %d\n&quot;,i);
    printf(&quot;You wrote : %s&quot;,(char *)shared_memory);
}