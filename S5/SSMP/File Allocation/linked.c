#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_FILE_NAME_LENGTH 20

void main() {
    printf("Navaneeth K.B S5 CSC\n");

    int total_blocks;  // Total number of blocks available
    printf("Enter the total number of blocks: ");
    scanf("%d", &total_blocks);
    
    int blocks[total_blocks]={0};  // Initialize blocks array

    srand(time(0));  // Seed the random number generator

    char file_names[MAX_FILES][MAX_FILE_NAME_LENGTH];  // Array to store file names
    int file_start[MAX_FILES];   // Array to store the starting block of each file
    int file_size[MAX_FILES];    // Array to store file sizes
    int file_blocks[MAX_FILES][total_blocks];  // Array to store block chains
    int file_count = 0;          // To keep track of the number of files
    int blocks_left = total_blocks;  // Track available blocks

    // Ask for the number of files to allocate
    int num_files;
    printf("Enter the number of files to allocate: ");
    scanf("%d", &num_files);

    while (file_count < num_files) 
    {
        printf("\nEnter the file name: ");
        scanf("%s", file_names[file_count]);
    
        printf("Enter the number of blocks allocated to the file: ");
        int num_blocks;
        scanf("%d", &num_blocks);

        // Check if enough blocks are available
        if (num_blocks > blocks_left) {
            printf("Not enough blocks available for file %s.\n", file_names[file_count]);
            continue;  // Skip the allocation and proceed with the next file
        }

        // Allocate blocks for the file
        int start_block = -1;  // Starting block of the file
        int prev_block = -1;   // Previous block in the chain

        for (int i = 0; i < num_blocks; i++) 
        {
            int block;
            do {
                block = rand() % total_blocks;
            } while (blocks[block] == 1);  // Find an unallocated block
        
            blocks[block] = 1;  // Mark the block as allocated
            blocks_left--;      // Decrease available blocks
        
            if (i == 0) {
                start_block = block;  // Set the start block for the file
            } else {
                file_blocks[file_count][prev_block] = block;  // Link to the previous block
            }
            
            prev_block = block;  // Update the previous block
        }

        file_blocks[file_count][prev_block] = -1;  // End of file chain

        // Update file metadata
        file_start[file_count] = start_block;
        file_size[file_count] = num_blocks;

        printf("File %s allocated with %d blocks starting from block %d.\n", file_names[file_count], num_blocks, start_block);
        file_count++;

        // Check if all blocks are allocated
        if (blocks_left <= 0) {
            printf("All blocks are allocated.\n");
            break;
        }
    }

    // Display the entire table of allocated files
    printf("\nFinal allocation table:\n");
    printf("File\t\tSize\tStart\tBlocks\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-10s\t%d\t%d\t", file_names[i], file_size[i], file_start[i]);
        int block = file_start[i];
        while (block != -1) {
            printf("%d ", block);
            block = file_blocks[i][block];  // Follow the block chain
        }
        printf("\n");
    }
}
