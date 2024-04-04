#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
void main()
{
    fork();
    fork();
    fork();
    fork();
    printf(&quot;hello\n&quot;);
    wait(NULL);
    wait(NULL);
}
