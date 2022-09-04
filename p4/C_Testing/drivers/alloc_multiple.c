#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: ./a.out <alloc_size> <num_times>\n");
        exit(0);
    }
    int size = atoi(argv[1]);
    int n = atoi(argv[2]);

    char **ptr = malloc(sizeof(char *) * n);

    Initialize_Memory_Allocator(1600);
   
    for (int i = 0; i < n; i++) {
        ptr[i] = test_Mem_Alloc(size);
        Mem_Dump();
    }
    for (int i = 0; i < n; i++) {
        test_Mem_Free(ptr[i]);
    }
    printf("<BREAK>\n");
    for (int i = 0; i < n; i++) {
        ptr[i] = Mem_Alloc(size);
        Mem_Dump();
    }
    free(ptr);
    Free_Memory_Allocator();
    return 0;
}
