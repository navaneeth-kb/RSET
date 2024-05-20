#include <sys/shm.h>
#include <stdio.h>
int main()
{
    int i, n, r, fact=1, fact1=1, *shared_memory, buff[100], shmid;
    key_t key = 111;
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    shared_memory = (int *)shmat(shmid, NULL, 0);
    printf(&quot;Enter the integer n:&quot;);
    scanf(&quot;%d&quot;, &amp;n);
    shared_memory[1]=n;
    printf(&quot;The number in shared memory is %d\n&quot;,shared_memory[1]);
    for(i=1;i&lt;=n;i++)
    {
        fact=fact*i;
    }
    shared_memory[2] = fact;
    printf(&quot;The factorial is:&quot;);
    printf(&quot;%d\n&quot;, shared_memory[2]);
    printf(&quot;Enter the integer r:&quot;);
    scanf(&quot;%d&quot;, &amp;r);
    shared_memory[3]=r;
    printf(&quot;The number in shared memory is %d\n&quot;,shared_memory[3]);
    for(i=1;i&lt;=r;i++)
    {
        fact1=fact1*i;
    }
    shared_memory[4] = fact1;
    printf(&quot;The factorial is:&quot;);
    printf(&quot;%d\n&quot;, shared_memory[4]);
    return 0;
}