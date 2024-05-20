#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main()
{
    int i;
    char *shared_memory;
    char string[100];
    int shmid;
    key_t key=111;
    shmid=shmget(key, 1024, 0666|IPC_CREAT);
    shared_memory=(char *)shmat(shmid,NULL,0);
    printf("Enter some data to write to shared memory\n");
    scanf("%s^\n",string);
    strcpy(shared_memory,string);
    printf("Writing over");
}