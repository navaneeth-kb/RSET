#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf(&quot;usage %s &lt;file or directory&gt;\n&quot;,argv[0]);
        return 1;
    }
    struct stat filestat;
    if(stat(argv[1],&amp;filestat)==-1)
    {
        perror(&quot;Error in stat&quot;);
        return 1;
    }
    printf(&quot;File name:%s\n&quot;,argv[1]);
    printf(&quot;File size:%ld bytes\n&quot;,filestat.st_size);
    printf(&quot;Blocks allocated:%ld\n&quot;,filestat.st_blocks);
    return 0;
}
