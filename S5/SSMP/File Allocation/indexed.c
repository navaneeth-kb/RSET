#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILES 100

int main() {
    printf("Navaneeth K.B S5 CSC\n");
    
    int total_blocks, num_files;
    printf("Enter the total number of blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    int blocks[total_blocks];  // Array to track allocated blocks
    for (int i = 0; i < total_blocks; i++) {
        blocks[i] = 0;  // Set all blocks to unallocated (0)
    }

    srand(time(0));  // Seed the random number generator

    char file_name[MAX_FILES][10];  // Array to store file names
    int file_size[MAX_FILES];        // Array to store file sizes
    int index_blocks[MAX_FILES];     // Array to store index blocks
    int file_blocks[MAX_FILES][total_blocks]; // Array to store block allocations

    printf("Enter the number of files: ");
    if (scanf("%d", &num_files) != 1 || num_files <= 0 || num_files > MAX_FILES) {
        printf("Invalid number of files.\n");
        return 1;
    }

    int blocks_left = total_blocks;

    for (int i = 0; i < num_files; i++) {
        printf("\nEnter the file name: ");
        if (scanf("%s", file_name[i]) != 1) {
            printf("Invalid file name.\n");
            return 1;
        }

        printf("Enter the number of blocks allocated to the file: ");
        if (scanf("%d", &file_size[i]) != 1 || file_size[i] <= 0 || file_size[i] + 1 > blocks_left) {
            printf("Invalid or insufficient blocks for file %s.\n", file_name[i]);
            continue;
        }

        // Allocate index block
        int index_block;
        do {
            index_block = rand() % total_blocks;
        } while (blocks[index_block] == 1);
        blocks[index_block] = 1;
        index_blocks[i] = index_block;
        blocks_left--;  // Decrease the count of available blocks

        printf("%-10s\t%-6d\t%-8d\t", file_name[i], file_size[i], index_block);

        // Allocate data blocks for the file
        for (int j = 0; j < file_size[i]; j++) {
            int block;
            do {
                block = rand() % total_blocks;
            } while (blocks[block] == 1);
            blocks[block] = 1;
            file_blocks[i][j] = block;
            printf("%d ", file_blocks[i][j]);
            blocks_left--;  // Decrease the count of available blocks
        }

        printf("\n");

        // Check if all blocks are allocated
        if (blocks_left <= 0) {
            printf("All blocks are allocated.\n");
            break;
        }
    }

    // Display the final allocation table
    printf("\nFinal allocation table:\n");
    printf("Name      \tSize  \tIndex   \tBlocks\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < num_files; i++) {
        if (file_size[i] > 0) {  // Only display allocated files
            printf("%-10s\t%-6d\t%-8d\t", file_name[i], file_size[i], index_blocks[i]);
            for (int j = 0; j < file_size[i]; j++) {
                printf("%d ", file_blocks[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
