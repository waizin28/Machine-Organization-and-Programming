#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_SIZE 3
#define NUM_BLOCKS 100

int main() {
    Initialize_Memory_Allocator(1600);

    int **ptr = malloc(sizeof(int*) * NUM_BLOCKS);
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ptr[i] = test_Mem_Alloc(ALLOC_SIZE);
    }
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 3 == 0) {
            test_Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    
    // Force left coaleses
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 1) {
            test_Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    

    // Force right coaleses
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 5) {
            test_Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }

    // Force coaleses from both sides
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 4) {
            test_Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    
    // Clean memory for user frees
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 2 || i%9 == 7 || i%9 == 8) {
            test_Mem_Free(ptr[i]);
        }
    }    
    printf("<BREAK>\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        ptr[i] = test_Mem_Alloc(ALLOC_SIZE);
    }
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 3 == 0) {
            Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    
    // Force left coaleses
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 1) {
            Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    

    // Force right coaleses
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 5) {
            Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }

    // Force coaleses from both sides
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if(i % 9 == 4) {
            Mem_Free(ptr[i]);
            Mem_Dump();
        }
    }    

    free(ptr);
    Free_Memory_Allocator();
    return 0;
}
