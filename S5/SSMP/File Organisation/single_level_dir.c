#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
void main()
{
	int ch;
	
	printf("Navaneeth K.B S5 CSC");
	while(1)
	{
		printf("MENU \n1-CREATE A FILE \n2-DELETE A FILE \n3-SEARCH A FILE \n4-DISPLAY ALL FILES \n5-RENAME A FILE\n");
		printf("Enter the choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				char fname[100];
				printf("Enter the file name:");
				scanf("%s",fname);
				FILE *filePointer;
				filePointer = fopen(fname, "w");
				char text[100];
				printf("Enter file content:");
				gets(text);
				gets(text);
				fprintf(filePointer,text);
				printf("File created!\n");
				fclose(filePointer);
				break;
			case 2:
				char fname2[100];
				printf("Enter the file name:");
				scanf("%s",fname2);
			        if (remove(fname2) == 0) 
			        {
					printf("File deleted!!\n");
			        } 
			        else
			        {
			        	printf("No file found");
		        	}
		        	break;
	        	case 3:
	        		char fnames[100];
	        		DIR *d;
			        struct dirent *dir;
			        d = opendir(".");
			        char fname_search[100];
				printf("Enter the file name:");
				scanf("%s",fname_search);
			        int i=0;
			        int flag=0;
			        if (d) 
			        {
			        	while ((dir = readdir(d)) != NULL) 
			        	{
			        		if (strcmp(fname_search, dir->d_name) == 0)
			        		{
			        			printf("%s\n", dir->d_name);
			        			printf("Found!!\n");
			        			flag=1;
			        			char cwd[1024];
							if (getcwd(cwd, sizeof(cwd)) != NULL) 
							{
								printf("Current directory: %s\n", cwd);
							} 
							else 
							{
								perror("getcwd");
							}
			        			break;
		        			}
			        	}
			        	closedir(d);
			        	if (flag==0)
			        	{
			        		printf("not found\n");
        				}
		        	}
		        	break;
		        	
		        case 4:
	        		DIR *d2;
			        struct dirent *dir2;
			        d2 = opendir(".");
			        if (d2) 
			        {
			        	while ((dir2 = readdir(d2)) != NULL) 
			        	{
			        		printf("%s\n", dir2->d_name);
			        	}
			        	closedir(d2);
			        	
		   		}
		   		printf("\n");
		   		break;
		   		
   			case 5:
   				char fname_rename[100];
				printf("Enter the file name:");
				scanf("%s",fname_rename);
				char fname_newname[100];
				printf("Enter new name:");
				scanf("%s",fname_newname);
				if (rename(fname_rename,fname_newname) == 0) 
			        {
					printf("File renamed!!\n");
			        } 
			        else
			        {
			        	printf("No file found");
		        	}
		        	break;
				
   		}
}
}
