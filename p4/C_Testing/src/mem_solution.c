#include "mem.h"
extern BLOCK_HEADER* first_header;

void test_Print_Block_Data(BLOCK_HEADER *h) {
    return;
}

int test_Is_Free(BLOCK_HEADER *h) {
    int alloc_bit = h->size_alloc & 1;
    if (alloc_bit) 
        return 0;
    return 1;
}

int test_Get_Payload_Size(BLOCK_HEADER *h) {
    return h->payload;
}

void* test_Get_User_Pointer(BLOCK_HEADER *h) {
    return (void *)((unsigned long)h + (unsigned long)8);
}

BLOCK_HEADER * test_Get_Next_Header(BLOCK_HEADER *c) {
    BLOCK_HEADER *n = (BLOCK_HEADER *)((unsigned long)c + (unsigned long)(c->size_alloc & 0xFFFFFFFE));
    return n;
}

int test_Get_Padding(BLOCK_HEADER *h) {
    return (h->size_alloc & 0xFFFFFFFE) -8 - h->payload;   
}

void* test_Mem_Alloc(int size){
    // find a free block that's big enough
    BLOCK_HEADER *current = first_header;
    while (current->size_alloc != 1) {
        if (test_Is_Free(current) && test_Get_Payload_Size(current) >= size) break; 
        current = test_Get_Next_Header(current);
    }

    // return NULL if we didn't find a block
    if (current->size_alloc == 1) return NULL;

    // allocate
    current->size_alloc |= 1;
    current->payload = size;

    // split if necessary (if padding size is greater than or equal to 16 split the block 
    if (test_Get_Padding(current) >= 16) {
        BLOCK_HEADER *next = test_Get_Next_Header(current);
        int block_size = size + 8;
        while (block_size % 16) block_size++;
        BLOCK_HEADER *new_header = (BLOCK_HEADER *)((unsigned long)current + block_size);
        new_header->size_alloc = (int)((unsigned long)next - (unsigned long)new_header);
        new_header->payload = new_header->size_alloc-8;
        current->size_alloc = (int)((unsigned long)new_header - (unsigned long)current);
        current->size_alloc |= 1;
    }

    return test_Get_User_Pointer(current);
}

// return 0 on success
// return -1 if the input ptr was invalid
int test_Mem_Free(void *ptr){
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
    BLOCK_HEADER *current = first_header;
    while (current->size_alloc != 1) {
        if (test_Get_User_Pointer(current) == ptr) break;
        current=test_Get_Next_Header(current);
    }
    // test for failure
    if (current->size_alloc == 1) return -1;

    // free the block 
    current->size_alloc &=0xFFFFFFFE; // set alloc bit
    BLOCK_HEADER *next = test_Get_Next_Header(current);
    current->payload = (unsigned long)next - (unsigned long)current - 8; // update payload

    // coalesce adjacent free blocks
    current = first_header;
    next = test_Get_Next_Header(current);
    while (next->size_alloc != 1) {
        if (test_Is_Free(current) && test_Is_Free(next)) {
            // merge them
            next=test_Get_Next_Header(next);
            current->size_alloc = (unsigned long)next - (unsigned long)current;
            current->payload = current->size_alloc-8;
            continue;
        }
        current = test_Get_Next_Header(current);
        next = test_Get_Next_Header(next);
    }

    return 0;
}

