#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILES 100

int main() {
	printf("Navaneeth K.B S5 CSC");
    int total_blocks;  // Total number of blocks available
    printf("Enter the total number of blocks: ");
    if (scanf("%d", &total_blocks) != 1 || total_blocks <= 0 || total_blocks > MAX_FILES) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    int blocks[total_blocks];  // Initialize blocks array
    for (int i = 0; i < total_blocks; i++) {
        blocks[i] = 0;  // Set all blocks to unallocated (0)
    }

    srand(time(0));  // Seed the random number generator

    int file_start[MAX_FILES];   // Array to store the starting block of each file
    int file_size[MAX_FILES];    // Array to store file sizes
    int file_blocks[MAX_FILES][total_blocks];  // Array to store block chains
    int file_count = 0;          // To keep track of the number of files
    int blocks_left = total_blocks;  // Track available blocks

    // Ask for the number of files to allocate
    int num_files;
    printf("Enter the number of files to allocate: ");
    if (scanf("%d", &num_files) != 1 || num_files <= 0 || num_files > MAX_FILES) {
        printf("Invalid number of files.\n");
        return 1;
    }

    while (file_count < num_files) {
        if (file_count >= MAX_FILES) {
            printf("Maximum number of files reached.\n");
            break;
        }

        printf("\nEnter the file name: ");
        char file_name[10];
        if (scanf("%s", file_name) != 1) {
            printf("Invalid file name.\n");
            return 1;
        }

        printf("Enter the number of blocks allocated to the file: ");
        int num_blocks;
        if (scanf("%d", &num_blocks) != 1 || num_blocks <= 0) {
            printf("Invalid number of blocks.\n");
            return 1;
        }

        // Check if enough blocks are available
        if (num_blocks > blocks_left) {
            printf("Not enough blocks available for file %s.\n", file_name);
            printf("Allocation skipped for file %s.\n", file_name);
            continue;  // Skip the allocation and proceed with the next file
        }

        // Allocate blocks for the file
        int start_block = -1;  // Starting block of the file
        int prev_block = -1;   // Previous block in the chain
        int allocated_blocks = 0;

        for (int i = 0; i < num_blocks; i++) {
            int block;
            if (blocks_left <= 0) {
                printf("Not enough blocks available to allocate more for file %s.\n", file_name);
                break;
            }

            do {
                block = rand() % total_blocks;
            } while (blocks[block] == 1);

            blocks[block] = 1;  // Mark block as allocated
            blocks_left--;      // Decrease the count of available blocks

            if (i == 0) {
                start_block = block;  // Set the start block for the file
            } else {
                // Link previous block to the current block
                file_blocks[file_count][prev_block] = block;
            }
            prev_block = block;
            file_blocks[file_count][block] = -1;  // End of file marker

            allocated_blocks++;
        }

        // Update the file start and size
        file_start[file_count] = start_block;
        file_size[file_count] = num_blocks;

        printf("File %s allocated with %d blocks starting from block %d.\n", file_name, num_blocks, start_block);

        file_count++;

        // Check if all blocks are allocated
        if (blocks_left <= 0) {
            printf("All blocks are allocated.\n");
            break;
        }
    }

    // Display the entire table of allocated files
    printf("\nFinal allocation table:\n");
    printf("File\tSize\tStart\tBlocks\n");
    for (int i = 0; i < file_count; i++) {
        printf("File%d\t%d\t%d\t", i, file_size[i], file_start[i]);
        int block = file_start[i];
        while (block != -1) {
            printf("%d ", block);
            block = file_blocks[i][block];
        }
        printf("\n");
    }

    return 0;
}
