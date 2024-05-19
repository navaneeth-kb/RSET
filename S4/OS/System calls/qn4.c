#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
void main()
{
    pid_t pid=fork();
    if(pid==0)
    {
       execlp("/bin/pwd","pwd",NULL);
    }
    else if(pid>0)
    {
        wait(NULL);
        printf("Success\n");
    }
    else
    {
        fprintf(stderr,"Fork Failed");
    }
}
