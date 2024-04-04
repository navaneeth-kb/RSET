#include&lt;stdio.h&gt;
#include&lt;sys/types.h&gt;
#include&lt;unistd.h&gt;
#include&lt;sys/wait.h&gt;
void main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        printf(&quot;3.Process of 1D of child is %d\n&quot;,getpid());
        printf(&quot;4.Parent of %d is %d\n&quot;,getpid(),getppid());
    }
    else if(pid&gt;0)
    {
        printf(&quot;1.Process 1D of parent is %d\n&quot;,getpid());
        wait(NULL);
        printf(&quot;2.Child of %d is %d\n&quot;,getpid(),pid);
    }
    else
    {
        fprintf(stderr,&quot;Fork Failed&quot;);
    }
}