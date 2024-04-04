#include&lt;stdio.h&gt;
#include&lt;sys/types.h&gt;
#include&lt;unistd.h&gt;
#include&lt;sys/wait.h&gt;
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