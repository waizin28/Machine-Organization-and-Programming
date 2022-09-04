	.file	"To_Upper.s"
	.text
	.globl To_Upper
	.type	To_Upper, @function

/* **********************
    Name: Wai Zin Linn
    Wisc ID Number: 9082616286
    Wisc Email: wlinn@wisc.edu
************************ */

To_Upper:

# C version
/* **********************
    Write the equivalent C code to this function here (in the comment block)
    
    void toUpper(char word[]){
      
      int i = 0;
      
      while(word[i] != '\0'){
        
        if(word[i] >= 97 && word[i] <= 122){
          word[i] = word[i] - 32;
        }

        i++;

      }
        
    }

************************ */


# Memory Layout
/* ************************ 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -8(%rbp)  |  int i
        -16(%rbp)  |  char word[]
************************ */

# Prologue - Setting up stack
   pushq %rbp #store base pointer up to where stack pointer previously is and pushing stack pointer up too
   movq %rsp, %rbp #move base pointer to bottom of stack frame
   subq $32, %rsp  #reserve space for main (optional for leaf function)
  
   movq $0, -8(%rbp) #storing i (counter) at the memory
   movq %rdi, -16(%rbp) #storing the array at the memory
   movq -16(%rbp), %rax #storing the array back into %rax
  
# This code prints the letter 'a' (ascii value 97)
# Use this for debugging
# Comment out when finished - your function should not print anything
# Note putchar overwrites all caller saved registers including argument registers
# movl	$97, %eax
# movl	%eax, %edi
# call	putchar@PLT

# Body of function
TOP_OF_LOOP:
   jmp LOOP_CONDITIONAL #first check the condition of while

LETTER_CHECK:
# word[i] >= 97 && word[i] <= 122
   cmpb $97, %cl #preparing to check for character less than 'a' (97), so we could assume the character is already capital
   jl FALSE_INC #assuming the character to be already capital since it's not within the range of char being small so move onto the next characater

#will continue to LOOP_BODY if character within the range of 'a' and 'z'
   cmpb $122, %cl #checking for word[i] <= 'z' 
   jle LOOP_BODY #move onto the loop body to modify the character 

FALSE_INC:
# i++
   movq -8(%rbp), %rdx #reading in the index value (i) into %rdx
   incq %rdx # adding 1 to i 
   movq %rdx, -8(%rbp) #store the i value back to memory (can be use to access next character from array)
   jmp LOOP_CONDITIONAL #go to check if null bit has reach

LOOP_BODY:
# word[i] = word[i] - 32   
   subb $32, %cl  # rdx -> 64 bits (currently have 32 bits)subtracting word[i] - 32 and saving the character in %cl
   movb %cl, (%rax,%rdx,1) #storing modified letter into word[i] 

# after modifying the letter, continue to next character
   jmp LOOP_CONDITIONAL #go to loop condition to check

LOOP_CONDITIONAL:
# word[i] != '\0'
# read in the registers first to refresh it
   movq -8(%rbp), %rdx #reading counter (i) to %rdx
   movq -16(%rbp), %rax #reading array into the %rax

# comparing the char at index i with null bit, if not equal continue to check the character else exit
   movb (%rax, %rdx, 1), %cl #getting the char at array index
   cmpb $0, %cl #compare the character with null bit, making sure the array is not end up  
 
# if the conidtion satisy do the letter_check
# else exit the loop 
   jne LETTER_CHECK  #jump back to loop body when condition is true    

# Epilogue - clean up stack
   addq $32, %rsp #clean up stack pointer
   popq %rbp #restore %rbp and %rsp to original position 
   ret #copy return address into instruction pointer
