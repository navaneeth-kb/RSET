#include<stdio.h>
#include<sys/stat.h>
#include<dirent.h>
void main()
{
    DIR *dir;
    struct dirent *entry;
    dir=opendir(".");
    if(dir==NULL)
    {
        printf("Error opening directory");
        return;
    }
    while((entry=readdir(dir))!=NULL)
    {
        printf("%s\n",entry->d_name);
    }
    closedir(dir);
}
