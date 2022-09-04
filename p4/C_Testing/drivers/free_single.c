#include "../mem.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: ./a.out <alloc_size>\n");
        exit(0);
    }
    int n = atoi(argv[1]);

    Initialize_Memory_Allocator(1600);
   
    char *p = test_Mem_Alloc(n);
    test_Mem_Free(p);
    Mem_Dump();

    printf("<BREAK>\n");
    p = test_Mem_Alloc(n);
    Mem_Free(p);
    Mem_Dump();
    
    Free_Memory_Allocator();
    return 0;
}
