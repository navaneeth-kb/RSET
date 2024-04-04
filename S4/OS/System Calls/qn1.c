#include&lt;stdio.h&gt;
#include&lt;sys/types.h&gt;
#include&lt;unistd.h&gt;
#include&lt;sys/wait.h&gt;
void main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf(&quot;Hello\n&quot;);
    }
    else if(pid&gt;0)
    {
        wait(NULL);
        printf(&quot;Goodbye\n&quot;);
    }
    else
    {
        fprintf(stderr,&quot;Fork Failed&quot;);
    }
}