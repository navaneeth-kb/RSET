#include <stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
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
