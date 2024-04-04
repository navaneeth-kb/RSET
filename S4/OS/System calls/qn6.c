#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
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
