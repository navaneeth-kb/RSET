#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("usage %s <file or directory>;\n",argv[0]);
        return 1;
    }
    struct stat filestat;
    if(stat(argv[1],&amp;filestat)==-1)
    {
        perror("Error in stat");
        return 1;
    }
    printf("File name:%s\n",argv[1]);
    printf("File size:%ld bytes\n",filestat.st_size);
    printf("Blocks allocated:%ld\n",filestat.st_blocks);
    return 0;
}
