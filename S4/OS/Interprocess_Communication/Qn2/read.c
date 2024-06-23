#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
int main()
{
    int i;
    int flag=0;
    char *shared_memory;
    char buff[100];
    int shmid;
    key_t key=111;
    shmid=shmget(key, 1024, 0666 | IPC_CREAT);
    shared_memory=(char *)shmat(shmid,NULL,0);
    strcpy(string,shared_memory);
    int l=strlen(string);
    int flag=0;
    for(int i=0;i<=l/2;i++)
    {
        if(string[l-1-i]!=string[i])
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
        printf("\nNot a palindrome\n");
    else
        printf("\nIs a palindrome\n");
    printf("\nReader process completed\n");
}