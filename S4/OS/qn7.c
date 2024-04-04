#include&lt;stdio.h&gt;
#include&lt;stdlib.h&gt;
#include&lt;fcntl.h&gt;
#include&lt;unistd.h&gt;
#define BUF_SIZE 4096
void main()
{
    int n,f1,f2;
    char file1[100],file2[100];
    printf(&quot;Name of source file:\n&quot;);
    scanf(&quot;%s&quot;,file1);
    printf(&quot;Name of destination file:\n&quot;);
    scanf(&quot;%s&quot;,file2);
    char buff[BUF_SIZE];
    f1=open(file1,O_RDONLY);
    f2=open(file2,O_WRONLY |O_CREAT,S_IWUSR | S_IRUSR);
    n=read(f1,buff,sizeof(buff));
    write(f2,buff,n);
    close(f1);
    close(f2);
}