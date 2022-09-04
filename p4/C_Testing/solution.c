/* Wai Zin Linn
*  9082616286
*/

#include "mem.h"                      
extern BLOCK_HEADER* first_header;

// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){

    if(size < 0){
      return NULL;
    }

    //initalizing all of the variables to use      
    int padding = 0;
    int isAlloc = 0;
    int headerSize = 8;
    int block_size = 0; 
    int curr_block_size = 0;   
    int MBS = 16; //header+data+padding    
 
    BLOCK_HEADER *current = first_header;
    BLOCK_HEADER* user_pointer;  
      
    //rounding up padding to be divisible by 16 bits
     while((headerSize+size+padding)%16 != 0) ++padding;

     block_size = headerSize+size+padding;//header + data + padding (round)
 
    //traversing the link
    //if we didn't reach the end of the block yet, execute
    while (1) { 
        
        //getting the alloc bit (1 or 0)   
        isAlloc = current->size_alloc & 1;
        
        //getting current block size (if odd (alloc), just want pure size) 
        curr_block_size = current->size_alloc & 0xFFFFFFFE;

    //check if allocated
    //if block fit with blocksize we are looking for
      if(!isAlloc && (curr_block_size >= block_size)){        
               //allocate give whole block or split
             int diffSize = curr_block_size-block_size; 

             while(diffSize%16) diffSize++;   
          
              //greater than minimum block size, split
              if(diffSize >= MBS){
                    //change current size to new BS
                    //current alloc change to 1
                    current->size_alloc = block_size+1; 
                  
                    current->payload = size;

                    //Add new header, need size and alloc
                    //where -> current+blocksize
                    //size -> diffSize
                    //aloc bit -> 0
                    //user pointer is the pointer where it's pointing to split block
                 
                    user_pointer  = (void *)((unsigned long)current+block_size);

                    //chaning new header's size_alloc and payload
                    user_pointer->size_alloc = diffSize;
                 
                    //getting the new size block after being allocated by requested size
                    user_pointer->payload = diffSize-sizeof(BLOCK_HEADER);

                 return (current+1);

            }else{
                    //Non splitting case, just update size_alloc, payload and return curr
                    int allocBit = 1;
                    current->size_alloc = block_size+allocBit;
                    current->payload = size;
                    return (current+1);
                }
         }
  
      //exit by returning NULL when reach it cannot find the block it's looking to free
      if(current->size_alloc == 1) return NULL;         
  
      //increment the current block 
       current = (BLOCK_HEADER *)((unsigned long)current + curr_block_size);
  }
    
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){

  // traverse the list and check all pointers to find the correct block 
  // if you reach the end of the list without finding it return -1
  
  //if input ptr is NULL cannot find it so return -1 
  if(ptr == NULL){
    return -1;
  }  

  //initalizing all of the variables
  int header = 8;  
  int isAlloc = 0;
  int currBlockSize = 0;
  int counter = 0;
  int nextIsAlloc = 0;  
  int prevIsAlloc = 0;

  //initalizing current header 
  BLOCK_HEADER *current = first_header;
  BLOCK_HEADER *search_hdr = ptr-header;
  BLOCK_HEADER *prev;
  BLOCK_HEADER *next;

 while(1){
     
      //getting the alloc bit (1 or 0)   
      isAlloc = current->size_alloc & 1;
      
      //getting pure block size of current block
      currBlockSize = current->size_alloc & 0xFFFFFFFE;

      //when user pointer we are looking for is found      
      if(search_hdr == current){

        //checking whether the pointer we are looking for is allocated
        if(isAlloc){

         //removing alloc bit and storing it in curr->size_alloc
          current->size_alloc = currBlockSize;          
          break;
          
        }else{

        //Just return -1 when we found the ptr, we are looking to free but is already free
         return -1;
        }

      }
      
      //if address larger than header pointer then it's invalid
      //when reach end of     
      if(current->size_alloc == 1) return -1;         

      //keeping track of previous block
      prev = current;  
        
      //counter to keep track of first header (this will increment when the pointer we are 
      //freeing is not first header within the list)
      counter++;

      //increment the current block to go to next block
      current = (BLOCK_HEADER *)((unsigned long)current + currBlockSize);
  
  }

    // coalesce adjacent free blocks (check the next block is free)
    // immediate coolescing
    
    next = (BLOCK_HEADER *)((unsigned long)current+currBlockSize);  
    nextIsAlloc = next->size_alloc & 1;   
        
    //checking for the first header
    if(counter == 0){
      //case when the next block is free
      if(!nextIsAlloc){
        
        //making sure we're just getting pure size block 
        current->size_alloc = current->size_alloc & 0xFFFFFFFE;           
        
         //current size alloc would take over the next size alloc too     
         current->size_alloc = current->size_alloc + next->size_alloc;
        
         //payload is pure block size so -8 to get rid of the header
         current->payload = current->size_alloc - 8;
        
         //everything successful so return 0
         return 0;

      }else{
  
        //making sure we're just getting pure size block 
        current->size_alloc = current->size_alloc & 0xFFFFFFFE;           
        
        current->payload = current->size_alloc - 8;       
    
        //don't need to coalesc so just return 0
        return 0;
      }
    }

    //checking for prev is alloc or not
    prevIsAlloc = prev->size_alloc & 1;

    //case for when prev is free and next is allocaed
    if(!prevIsAlloc && nextIsAlloc){
      
      //making sure we're just getting pure size block 
      current->size_alloc = current->size_alloc & 0xFFFFFFFE; 
     
      prev->size_alloc = prev->size_alloc + current->size_alloc;
  
      prev->payload = prev->size_alloc - 8;
   
      return 0;
  
    }

    //previous is allocated and next is free
    else if(prevIsAlloc && !nextIsAlloc){
      
      //making sure we're just getting pure size block 
      current->size_alloc = current->size_alloc & 0xFFFFFFFE; 
      
      current->size_alloc = current->size_alloc + next->size_alloc;

      current->payload = current->size_alloc - 8;      
     
      return 0;

    }

    //previous and next both free
    else if(!prevIsAlloc && !nextIsAlloc){
    
      //making sure we're just getting pure size block 
      current->size_alloc = current->size_alloc & 0xFFFFFFFE; 
      next->size_alloc = next->size_alloc & 0xFFFFFFFE; 
      
      prev->size_alloc = prev->size_alloc + current->size_alloc + next->size_alloc;
      
      prev->payload = prev->size_alloc - 8;

      return 0;
    
    }

    //previous and next both allocated
    else{

    //just return the modify current block payload to just include pure block size
    current->size_alloc = current->size_alloc & 0xFFFFFFFE;
    current->payload = current->size_alloc - 8;
      
    return 0;

    }
        
}
