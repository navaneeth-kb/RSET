#include&lt;stdio.h&gt;
#include&lt;sys/stat.h&gt;
#include&lt;dirent.h&gt;
void main()
{
    DIR *dir;
    struct dirent *entry;
    dir=opendir(&quot;.&quot;);
    if(dir==NULL)
    {
        printf(&quot;Error opening directory&quot;);
        return;
    }
    while((entry=readdir(dir))!=NULL)
    {
        printf(&quot;%s\n&quot;,entry-&gt;d_name);
    }
    closedir(dir);
}