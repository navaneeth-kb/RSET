#include <stdio.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_BLOCKS 100

int main() {
    printf("Navaneeth K.B S5 CSC \n");

    int total_blocks;  // Total number of blocks available
    printf("Enter the total number of blocks: ");
    scanf("%d", &total_blocks);

    int blocks[MAX_BLOCKS] = {0};  // Array to track block allocation (initialized to 0)

    int num_files;
    printf("Enter the number of files: ");
    scanf("%d", &num_files);

    char file_name[MAX_FILES][10];  // Array to store file names
    int file_size[MAX_FILES];       // Array to store file sizes
    int file_blocks[MAX_FILES][MAX_BLOCKS];  // Array to store allocated blocks for each file
    int file_count = 0;     // To keep track of the number of files

    for (int i = 0; i < num_files; i++) {
        printf("\nEnter the file name: ");
        scanf("%s", file_name[file_count]);

        printf("Enter the number of blocks required: ");
        scanf("%d", &file_size[file_count]);

        int allocated_blocks = 0;  // To track number of blocks allocated for current file
        for (int j = 0; j < total_blocks && allocated_blocks < file_size[file_count]; j++) {
            if (blocks[j] == 0) {  // If block is free
                blocks[j] = 1;  // Mark block as allocated
                file_blocks[file_count][allocated_blocks] = j;  // Store block index
                allocated_blocks++;
            }
        }

        if (allocated_blocks == file_size[file_count]) {
            printf("Blocks allocated for %s: ", file_name[file_count]);
            for (int j = 0; j < file_size[file_count]; j++) {
                printf("%d ", file_blocks[file_count][j]);
            }
            printf("\n");
            file_count++;
        } else {
            printf("Not enough blocks available for file %s.\n", file_name[file_count]);
        }
    }

    // Display final allocation table
    printf("\nFinal allocation table:\n");
    printf("File Name\tSize\tBlocks\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-10s\t%-5d\t", file_name[i], file_size[i]);
        for (int j = 0; j < file_size[i]; j++) {
            printf("%d ", file_blocks[i][j]);
        }
        printf("\n");
    }

    return 0;
}