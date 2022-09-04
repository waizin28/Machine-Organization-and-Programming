#include "mem.h"
#include <stdio.h>

int main() {
    Initialize_Memory_Allocator(1600);
    Mem_Dump();
   
    int *p1 = Mem_Alloc(8);
    printf("Pointer p1 %p\n",p1);
    int *p2 = Mem_Alloc(8);
    int *p3 = Mem_Alloc(8);
    int *p4 = Mem_Alloc(8);
    int *p5 = Mem_Alloc(8);
    int *p6 = Mem_Alloc(8);
    int *p7 = Mem_Alloc(8);
    int *p8 = Mem_Alloc(8);
    int *p9 = Mem_Alloc(8);
    int *p10 = Mem_Alloc(1592);
    Mem_Dump();

    printf("Free P7\n");
    printf("Pointer to be free p7 %p\n", p7);
    Mem_Free(p7);
    printf("After freeing\n");
    Mem_Dump();

    printf("Free P6\n");
    printf("Pointer to be free p6 %p\n", p6);
    Mem_Free(p6);
    Mem_Dump();

    printf("Free P6 again\n");
    Mem_Free(p6);
    Mem_Dump();

    printf("Free P8\n");
    Mem_Free(p8);  
    printf("Pointer to be free p8 %p\n", p8);
    Mem_Dump();

    printf("Free P4\n");  
    printf("Pointer to be free p4 %p\n", p4);
    Mem_Free(p4);
    Mem_Dump();
   
    printf("Free P5\n");  
    printf("Pointer to be free  p5 %p\n", p5);
    Mem_Free(p5);
    Mem_Dump();  

    Free_Memory_Allocator();
    return 0;
}
