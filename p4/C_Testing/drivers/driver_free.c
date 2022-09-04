#include "../mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
   
    int *p1 = test_Mem_Alloc(8);
    int *p2 = test_Mem_Alloc(8);
    int *p3 = test_Mem_Alloc(8);
    int *p4 = test_Mem_Alloc(8);
    int *p5 = test_Mem_Alloc(8);
    int *p6 = test_Mem_Alloc(8);
    int *p7 = test_Mem_Alloc(8);
    int *p8 = test_Mem_Alloc(8);
    int *p9 = test_Mem_Alloc(8);

    test_Mem_Free(p7);
    Mem_Dump();

    test_Mem_Free(p6);
    Mem_Dump();

    test_Mem_Free(p8);
    Mem_Dump();

    test_Mem_Free(p4);
    Mem_Dump();
   
    test_Mem_Free(p5);
    Mem_Dump();

    test_Mem_Free(p1);
    test_Mem_Free(p2);
    test_Mem_Free(p3);
    test_Mem_Free(p9);
    printf("<BREAK>\n");
    p1 = test_Mem_Alloc(8);
    p2 = test_Mem_Alloc(8);
    p3 = test_Mem_Alloc(8);
    p4 = test_Mem_Alloc(8);
    p5 = test_Mem_Alloc(8);
    p6 = test_Mem_Alloc(8);
    p7 = test_Mem_Alloc(8);
    p8 = test_Mem_Alloc(8);
    p9 = test_Mem_Alloc(8);

    Mem_Free(p7);
    Mem_Dump();

    Mem_Free(p6);
    Mem_Dump();

    Mem_Free(p8);
    Mem_Dump();

    Mem_Free(p4);
    Mem_Dump();
   
    Mem_Free(p5);
    Mem_Dump();

    Free_Memory_Allocator();
    return 0;
}
