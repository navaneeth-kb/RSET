#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FILES 100

int main() {
	printf("Navaneeth K.B S5 CSC\n");
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

    int index_blocks[MAX_FILES];  // Array to store index block for each file
    char file_name[MAX_FILES][10];  // Array to store file names
    int file_size[MAX_FILES];       // Array to store file sizes
    int file_blocks[MAX_FILES][total_blocks];  // Array to store block allocations
    int file_count = 0;     // To keep track of the number of files
    int blocks_left = total_blocks;  // Track available blocks

    int num_files;
    printf("Enter the number of files: ");
    if (scanf("%d", &num_files) != 1 || num_files <= 0 || num_files > MAX_FILES) {
        printf("Invalid number of files.\n");
        return 1;
    }

    for (int file_index = 0; file_index < num_files; file_index++) {
        if (file_count >= MAX_FILES) {
            printf("Maximum number of files reached.\n");
            break;
        }

        printf("\nEnter the file name: ");
        if (scanf("%s", file_name[file_count]) != 1) {
            printf("Invalid file name.\n");
            return 1;
        }

        printf("Enter the number of blocks allocated to the file: ");
        if (scanf("%d", &file_size[file_count]) != 1 || file_size[file_count] <= 0) {
            printf("Invalid file size.\n");
            return 1;
        }

        // Check if enough blocks are available (including the index block)
        if (file_size[file_count] + 1 > blocks_left) {
            printf("Not enough blocks available for file %s.\n", file_name[file_count]);
            continue;  // Skip the allocation and move to the next file
        }

        // Allocate index block
        int index_block;
        do {
            index_block = rand() % total_blocks;
        } while (blocks[index_block] == 1);
        blocks[index_block] = 1;  // Mark index block as allocated
        index_blocks[file_count] = index_block;
        blocks_left--;  // Decrease the count of available blocks

        printf("%-10s\t%-6d\t%-8d\t", file_name[file_count], file_size[file_count], index_block);

        // Allocate data blocks and store them
        int allocated_blocks = 0;
        for (int i = 0; i < file_size[file_count]; i++) {
            if (blocks_left <= 0) {
                printf("Not enough blocks available to allocate more for file %s.\n", file_name[file_count]);
                blocks[index_block] = 0;  // Free the index block
                blocks_left++;  // Restore the count of available blocks
                break;
            }
            int block;
            do {
                block = rand() % total_blocks;
            } while (blocks[block] == 1);
            blocks[block] = 1;  // Mark block as allocated
            file_blocks[file_count][i] = block;
            printf("%d ", file_blocks[file_count][i]);
            blocks_left--;  // Decrease the count of available blocks
            allocated_blocks++;
        }
        if (allocated_blocks == file_size[file_count]) {
            printf("\n");
            file_count++;
        }

        // Check if all blocks are allocated
        if (blocks_left <= 0) {
            printf("All blocks are allocated.\n");
            break;
        }
    }

    // Display the entire table of allocated files
    printf("\nFinal allocation table:\n");
    printf("Name      \tSize  \tIndex   \tBlocks\n");
    printf("---------------------------------------------\n");
    for (int i = 0; i < file_count; i++) {
        printf("%-10s\t%-6d\t%-8d\t", file_name[i], file_size[i], index_blocks[i]);
        for (int j = 0; j < file_size[i]; j++) {
            printf("%d ", file_blocks[i][j]);
        }
        printf("\n");
    }

    return 0;
}
