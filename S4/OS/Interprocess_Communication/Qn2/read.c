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
    shmid=shmget(key, 1024, 0666);
    shared_memory=shmat(shmid,NULL,0);
    int y=strlen(shared_memory)-2;
    for(int i=0;i&lt;=y;i++)
        {
        if(shared_memory[i]!=shared_memory[y-i])
        {
            flag=1;
            break;
        }
    }
    if(flag==1){
    printf(&quot;Not a palindrome\n&quot;);}
    else{
    printf(&quot;Palindrome\n&quot;);}
}