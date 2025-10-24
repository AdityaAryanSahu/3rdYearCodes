#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TOTAL_BLOCKS 20    
#define SPARE_BLOCKS 3    

typedef struct {
    int bad_block;
    int spare_block;
} BadBlockEntry;

void print_disk(bool disk[], int size) {
    printf("Disk blocks: ");
    for (int i = 0; i < size; i++) {
        if (disk[i]) printf("[Used] ");
        else printf("[Free] ");
    }
    printf("\n");
}

int main() {
    bool disk[TOTAL_BLOCKS] = {0}; 
    int file_start, file_size;
    int spare_blocks[SPARE_BLOCKS];
    BadBlockEntry bad_table[SPARE_BLOCKS];
    int bad_count = 0;

    for (int i = 0; i < SPARE_BLOCKS; i++) {
        spare_blocks[i] = TOTAL_BLOCKS - SPARE_BLOCKS + i;
    }

    printf("Enter start block of file: ");
    scanf("%d", &file_start);
    printf("Enter size of file in blocks: ");
    scanf("%d", &file_size);

    printf("\nEnter the indices of bad blocks in the file (enter -1 to stop):\n");
    int bad;
    while (bad_count < SPARE_BLOCKS) {
        scanf("%d", &bad);
        if (bad == -1) break;
        if (bad >= file_start && bad < file_start + file_size) {
            bad_table[bad_count].bad_block = bad;
            bad_table[bad_count].spare_block = spare_blocks[bad_count];
            bad_count++;
        } else {
            printf("Bad block must be within file allocation.\n");
        }
    }

    printf("\nAllocating file...\n");
    for (int i = file_start; i < file_start + file_size; i++) {
        bool is_bad = false;
        for (int j = 0; j < bad_count; j++) {
            if (i == bad_table[j].bad_block) {
                disk[bad_table[j].spare_block] = 1; 
                printf("Block %d is bad, using spare block %d\n", i, bad_table[j].spare_block);
                is_bad = true;
                break;
            }
        }
        if (!is_bad) disk[i] = 1;
    }

    print_disk(disk, TOTAL_BLOCKS);

    if (bad_count > 0) {
        printf("\nBad Blocks Table:\n");
        printf("Bad Block -> Spare Block\n");
        for (int i = 0; i < bad_count; i++) {
            printf("%d -> %d\n", bad_table[i].bad_block, bad_table[i].spare_block);
        }
    } else {
        printf("\nNo bad blocks detected.\n");
    }

    return 0;
}
