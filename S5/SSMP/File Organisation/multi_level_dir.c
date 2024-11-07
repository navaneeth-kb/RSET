#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

void main()
{
    while(1)
    {
        int ch;
        char fname[100];
        char dname[100];
        DIR *d;
        struct dirent *dir;
        printf("1-CREATE FILE\n2-DELETE FILE\n3-SEARCH FILE\n4-DISPLAY ALL FILES\n5-RENAME FILE\n6-CREATE DIR\n7-DELETE DIR\n8-CHANGE DIR\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("enter file name:");
                scanf("%s",fname);
                FILE *fp;
                char text[100];
                fp=fopen(fname,"w");
                printf("enter file contents:");
                gets(text);
                gets(text);
                fprintf(fp, "%s", text);   //in linux => fprintf(fp,text);
                printf("file created\n");
                fclose(fp);
                break;

            case 2:
                printf("enter file name:");
                scanf("%s",fname);
                if(remove(fname)==0)
                {
                    printf("file removed");
                }
                else
                {
                    printf("file removal unsuccessful");
                }
                break;

            case 3:
                d=opendir(".");
                printf("enter file name:");
                scanf("%s",fname);
                int flag=0;
                if(d)
                {
                    while((dir=readdir(d))!=NULL)
                    {
                        if(strcmp(fname,dir->d_name)==0)
                        {
                            flag=1;
                            printf("Found\n");
                            break;
                        }
                    }
                    closedir(d);
                    if(flag==0)
                    {
                        printf("File not found\n");
                    }
                }
                break;

            case 4:
                d=opendir(".");
                if(d)
                {
                    while((dir=readdir(d))!=NULL)
                    {
                        printf("%s\n",dir->d_name);
                    }
                    closedir(d);
                }
                printf("\n");
                break;

            case 5:
                printf("Enter the file name:");
				scanf("%s",fname);
				char fname_new[100];
				printf("Enter new name:");
				scanf("%s",fname_new);
				if(rename(fname,fname_new)==0)
                {
                    printf("File renamed\n");
                }
                else
                {
                    printf("No file found\n");
                }
                break;

            case 6:
                printf("Enter the dir name:");
				scanf("%s",dname);
				if(mkdir(dname)==0)
                {
                    printf("mkdir successful\n");
                }
                else
                {
                    printf("mkdir unsuccessful\n");
                }
                break;

            case 7:
                printf("Enter the dir name:");
				scanf("%s",dname);
				if(rmdir(dname)==0)
                {
                    printf("rmdir successful\n");
                }
                else
                {
                    printf("rmdir unsuccessful\n");
                }
                break;

            case 8:
                printf("Enter the dir name:");
				scanf("%s",dname);
				if(chdir(dname)==0)
                {
                    printf("chdir successful\n");
                }
                else
                {
                    printf("chdir unsuccessful\n");
                }
                break;
        }
    }
}
