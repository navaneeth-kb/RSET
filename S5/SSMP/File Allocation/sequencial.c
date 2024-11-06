#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILES 100

int main() {
	printf("Navaneeth K.B S5 CSC \n");
    int total_blocks;  // Total number of blocks available
    printf("Enter the total number of blocks: ");
    scanf("%d", &total_blocks);

    int blocks[total_blocks];  // Initialize blocks array
    for (int i = 0; i < total_blocks; i++) {
        blocks[i] = 0;  // Set all blocks to unallocated (0)
    }

    int start_block = 0;    // Start block for allocation
    char file_name[MAX_FILES][10];  // Array to store file names
    int file_size[MAX_FILES];       // Array to store file sizes
    int file_blocks[MAX_FILES][total_blocks];  // Array to store block allocations
    int file_count = 0;     // To keep track of the number of files

    int num_files;
    printf("Enter the number of files: ");
    scanf("%d", &num_files);

    for (int i = 0; i < num_files; i++) {
        printf("\nEnter the file name: ");
        scanf("%s", file_name[file_count]);
        printf("Enter the number of blocks allocated to the file: ");
        scanf("%d", &file_size[file_count]);

        if (start_block + file_size[file_count] > total_blocks) {
            printf("Not enough blocks available for file %s.\n", file_name[file_count]);
            continue;  // Skip the allocation and ask for the next file
        }

        printf("Allocating blocks for %s (%d blocks): ", file_name[file_count], file_size[file_count]);
        for (int j = 0; j < file_size[file_count]; j++) {
            blocks[start_block] = 1;  // Allocate block
            file_blocks[file_count][j] = start_block;
            printf("%d ", start_block);
            start_block++;
        }
        printf("\n");
        file_count++;

        // Check if all blocks are allocated
        if (start_block >= total_blocks) {
            printf("All blocks are allocated.\n");
            break;
        }
    }

    // Display the entire table of allocated files
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
