#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void main()
{
	int ch;
	char dirname[100];
	while(1)
	{

		printf("MENU \n1-CREATE A FILE \n2-DELETE A FILE \n3-SEARCH A FILE \n4-DISPLAY ALL FILES \n5-RENAME A FILE \n6-CREATE NEW DIRECTORY \n7-CHANGE DIRECTORY\n");
		printf("Enter the choice:");
		scanf("%d",&ch);
		char fname[100];
		char fname2[100];
		char fnames[100];
		DIR *d;
		DIR *d2;
		char fname_rename[100];
		struct dirent *dir;
        struct dirent *dir2;
        char dirname[256];
		switch(ch)
		{
			case 1:

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
            case 6:
                printf("Enter the name of the directory to create: ");
                scanf("%255s", dirname);  // Read the input from the user
                if (mkdir(dirname) == -1)
                {
                    printf("mkdir failed");
                }
                else
                {
                    printf("Directory created successfully\n");
                }
                break;

            case 7:
                printf("Enter the name of the directory: ");
                scanf("%255s", dirname);  // Read the input from the user
                if (chdir(dirname) == -1)
                {
                    printf("chdir failed");  // Print an error message if chdir fails
                } else
                {
                    printf("Successfully changed to directory '%s'\n", dirname);
                }
            }
        }
}
