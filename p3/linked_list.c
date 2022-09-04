/* Wai Zin Linn
*  9082616286
*/

// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
     
    int count = 0;

    //start from the head node and keep looping 
    //through until NULL is encountered 

    NODE *current = list.head;

    while(current != NULL){

        //keep updating counter is not NULL
        count++;

        //update the node
        current = current->next;
    }
  
    return count;    
}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){

    //create a newNode and input information 
    NODE* newNode = malloc(sizeof(NODE));
    newNode->data = data;

    //newNode will point what ever head used to point before (inserting at front)
    newNode->next = list->head;
    list->head = newNode; 
    return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {
    
    //put in newNode as first node if list is empty
    if(list->head == NULL){
      Push_Front(list,data);
      return;
    }
    
    //find the node before last node
    NODE* lastNode = list->head;
    while(lastNode->next != NULL){
      lastNode = lastNode->next;
    }

    //create a new node and put in data
    NODE* newNode = malloc(sizeof(NODE));
    newNode->data = data;
    //newNode's next would be NULL because it will be placed at end
    newNode->next = NULL;

    //change the pointer of lastNode to make newNode last node
    lastNode->next = newNode;
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    
    //check for empty list and return 0 immediately    
    if(list->head == NULL){
        return 0;
    }

    //if not empty then there are nodes, so we must remove them
    
    //get the head of the list 
    NODE* temp = list->head;

    //store the node's data that is going
    //to be removed into data
    *data = temp->data;

    //redirect the head pointer to node's
    //next pointer  
    list->head = temp->next;
    
    //free the memory on heap
    free(temp);
    
    //return 1 since node has been deleted
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
  
  //check for empty list and return 0 immediately
  if(list->head == NULL){
      return 0;
  }
  
  //handling for the case when there is only 1 node in list

  //check if list only have 1 node by checking head's next
  //to be null
  if(list->head->next == NULL){
    //store the data that's going to be deleted
    *data = list->head->data;
    //free the memory
    free(list->head);
    //change the head to NULL 
    list->head = NULL;
    return 1;
  }
    
  //handling the case when there are 2 or more nodes in list

  NODE *current = list->head;

  //trying to get the second last node 
  while(current->next->next != NULL){
    current = current->next;
  }

    //get the data from last node
    *data = current->next->data;
    
    //free the last node
    free(current->next);

    //change the pointer of second last node to 
    //point to NULL since last node is deleted
    current->next = NULL;
 
    //return 1 since a node has been deleted
   return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    
    int count = 0;

    //get the head of list
    NODE *current = list.head;

    //keep looping through until last Node
    //is encountered (NULL)
    while(current != NULL){

        //if data match, then increment counter
        if(current->data == data){
          count++;
        }

      //keep updating the node
      current = current->next;
    }
    return count;    
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    
    //if the list is empty then immediately return 0
    //since there is no node to delete        
    if(list->head == NULL){
      return 0;
    }
    
    NODE *temp = list->head;
    int val = 0;
    // handle the case for value that we are loooking for is stored in the head

    if(temp->data == data){
      
      //need a node to store old node so it can be free
      NODE *toDelete = list->head;

      //change the head to whatever head was pointing to before 
      list->head = list->head->next;
      
      //free the previous head node
      free(toDelete);
      val = 1;
    }else{
      
      //from node previous to node where value is located, adjust the link
      
      while(temp->next != NULL){
        
        //if next's node data matches with data we are looking for,
        //delete it
        if(temp->next->data == data){
          
          //store the node that's going to be deleted
          NODE *toDelete = temp->next;

          //change the pointer of current to point to what deleted node
          //is pointing
          temp->next = temp->next->next;
      
          //free the deleted node
          free(toDelete);
          val = 1;

          //break out of loop since a node has been removed
          break;
      }
      
      //keep updating the nodes
      temp = temp->next;
    }
  }
  return val;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    //if head is NULL then list is empty
    if(list.head == NULL){
      return 1;
    }
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    
    NODE *current = list->head;
    NODE *nextNode;
    
    //keep looping through if end of list
    //isn't reach yet
    while(current != NULL){
      
      //get the next node
      nextNode = current->next;
      
      //free the current node
      free(current);
      
      //update the current node to nextNode 
      current = nextNode;
    }
    
    //make the head points to NULL
    list->head = NULL;

    return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    
    //exit if list is empty    
    if(list->head == NULL){
      return;
    }

    NODE *compare = list->head;
    NODE *current;
    NODE *temp;

    //get the each node that we want to check
    while(compare != NULL && compare->next != NULL){
      
      //get same list into list we are going to compare to
      current = compare;
      
      //make sure end of list isn't reach yet
      while(current->next != NULL){
          
          //if data match then delete
          if(compare->data == current->next->data){
            temp = current->next;
            current->next = current->next->next;
            free(temp);
          }else{
            //if not keeep comparing with rest of the nodes
            current = current->next;
        }
      }
      //move onto next node to compare
      compare = compare->next;
    }

    return;
}

// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    // write a better test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    Clear(&list);
    
    //testing size when list have been cleared out

    printf("Testing size after clear method\n");
    if(Size(list) != 0){
      printf("Incorrect output for size\n");
    }else{
      printf("Correct size\n");
    }
 
    printf("size = %d\n",Size(list));
    
    //manually adding nodes
     
    NODE *third = malloc(sizeof(NODE)); Verify_Malloc(third);
    NODE *fourth = malloc(sizeof(NODE)); Verify_Malloc(fourth);
    NODE *fifth = malloc(sizeof(NODE)); Verify_Malloc(fifth);
    NODE *sixth = malloc(sizeof(NODE)); Verify_Malloc(sixth);
    NODE *seventh =  malloc(sizeof(NODE)); Verify_Malloc(seventh);
    third->data = 3;
    fourth->data = 4;
    fifth->data = 5;
    sixth->data = 6;
    seventh->data = 7;
     
    list.head = third;
    third->next = fourth;
    fourth->next = fifth;
    fifth->next = sixth;
    sixth->next = seventh;
    seventh->next = NULL;

    //testing size after adding 5 new nodes    
    printf("Testing size after adding 5 new Node\n");
        
    if(Size(list) != 5){
      printf("Incorrect output for size\n");
    }else{
      printf("Correct size\n");
    }
    
    printf("size = %d\n",Size(list));
    
    printf("\n");

    //Testing Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    printf("Testing Is_Empty when the list is empty\n");
    Clear(&list);
    
    if(Is_Empty(list) != 1){
      printf("Is_Empty method is wrong\n");
    }else{
      printf("Is_Empty method is correct\n");
    }

    printf("Testing Is_Empty method after adding a node\n");
    Push_Front(&list, 4);    
     
     // print the list
    printf("List: ");
    Print_List(stdout, list);
 
    if(Is_Empty(list) != 0){
      printf("Is_Empty method is wrong\n");
    }else{
      printf("Is_Empty method is correct\n");
    }
    
    printf("Clear out the list again after test\n");

    Clear(&list);

     // print the list
    printf("List: ");
    Print_List(stdout, list);
    
    printf("\n");


    // write a better test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    Push_Front(&list, 3);
    Push_Front(&list, 3);
    Push_Front(&list, 9);
    Push_Front(&list, 7);
    Push_Front(&list, 9);
    
    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);
 
    printf("size = %d\n",Size(list));
   
    //testing for push_front
 
    printf("Testing for push_front next data, Expected: 9\n");
    
    if(list.head->data != 9){
     printf("Push_Front incorrect\n");
    }else{
      printf("Push_Front correct\n");
    }
    
    //testing for push_front next value

    printf("Testing for push_front next data, Expected: 7\n");

    if(list.head->next->data != 7){
       printf("Push_Front next value incorrect\n");
    }else{
      printf("Push_Front next value correct\n");
    }


    //testing for push_front after clear

    printf("Testing Push_front after clear method\n");
    Clear(&list);
    
    printf("After clear: "); 
    Print_List(stdout, list);

    Push_Front(&list, 5);
    
    printf("After adding 5 with push_front: "); 
    Print_List(stdout, list);
    
    if(list.head->data != 5){
      printf("Push_Front value after clear incorrect\n");
    }else{
      printf("Push_Front value after clear correct\n");
    }
   
    //testing for size after adding 1 node with Push_front
    
    printf("Testing size after clearing and adding 1 node with Push_front\n");

    if(Size(list) != 1){
      printf("size is incorrect\n");
    }else{
      printf("size is correct\n");
    }

    printf("\n");
    
    // write a better test for Push_Back
    printf("Testing Push_Back: 3 was inserted to the back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);
    
    //get the last node
    NODE* lastNode = list.head;
    while(lastNode->next != NULL){
      lastNode = lastNode->next;
    }

    printf("Testing if 3 is in last node\n");
    if(lastNode->data != 3){
      printf("Push_back incorrect\n");
    }else{
      printf("Push_back correct\n");
    }
 
    printf("Testing Push_back after clear method\n");
    Clear(&list);
    
    printf("After clear: "); 
    Print_List(stdout, list);

    Push_Back(&list, 4);

    printf("Adding 4 with push_back after clear: "); 
    Print_List(stdout, list);
    
    //get the last node
    NODE* last = list.head;
    while(last->next != NULL){
      last = last->next;
    }

    printf("List: "); 
    Print_List(stdout, list);
    
    printf("Testing if 4 is in last node\n");
    if(last->data != 4){
      printf("Push_back incorrect\n");
    }else{
      printf("Push_back correct\n");
    }
 
    //testing for size after adding 1 node with Push_Back
    
    printf("Testing size after clearing and adding 4 to end with Push_front\n");

    if(Size(list) != 1){
      printf("size is incorrect\n");
    }else{
      printf("size is correct\n");
    }

    printf("\n");

    // write a better test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            printf("List: ");
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    printf("Testing Pop_Front after clearing the list\n");
    Clear(&list);
     
    printf("After clear: "); 
    Print_List(stdout, list);
    
    //making sure empty list pop_front work    
    int k;
    if(Pop_Front(&list, &k) != 1){
      printf("Pop_Front for empty list correct\n");
    }else{
      printf("Pop_Front for empty list incorrect\n");
    }

    printf("Testing the return data\n");
    if(k != 0){
      printf("Return data value is incorrect\n");
    }else{
      printf("Return data value is correct\n");
    }    
    
    //testin for when there is only 1 node in list
    printf("Adding data 5 in at end of list\n");    
    
    Push_Back(&list, 5);
    
    if(Pop_Front(&list, &k) != 0){
      printf("Pop_Front for empty list correct\n");
    }else{
      printf("Pop_Front for empty list incorrect\n");
    }

    printf("Testing the return data\n");
    if(k != 5){
      printf("Return data value is incorrect\n");
    }else{
      printf("Return data value is correct\n");
    }    
 
    //testing for actual pop_front when there are multiple nodes
    printf("Testing for Pop_Front when there are multiple nodes\n");
    Push_Back(&list, 6);    
    Push_Back(&list, 3);   
    Push_Back(&list, 2);
    Push_Back(&list, 21);
    Push_Back(&list, 5543);
    Push_Back(&list, 23);
     
    printf("New list: "); 
    Print_List(stdout, list); 

    int q;
    if(Pop_Front(&list, &q) != 0){
      printf("Pop_Front for empty list correct\n");
    }else{
      printf("Pop_Front for empty list incorrect\n");
    }

    printf("Testing the return data\n");
    if(q != 6){
      printf("Return data value is incorrect\n");
    }else{
      printf("Return data value is correct\n");
    }    
  
    printf("After Pop_Front (6): "); 
    Print_List(stdout, list);
    

    printf("\n");

    // write a better test for Pop_Back
    printf("Testing Pop_Back\n");

    // adding a new node since list is empty
    printf("Added a new node 123 since the list is empty\n");
    Push_Front(&list, 123);

    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            printf("List: ");
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    printf("Testing Pop_Back after clearing the list\n");
    Clear(&list);
     
    printf("After clear: "); 
    Print_List(stdout, list);
    

    int j;
    if(Pop_Back(&list, &j) != 1){
      printf("Pop_Back for empty list correct\n");
    }else{
      printf("Pop_Back for empty list incorrect\n");
    }

    printf("Testing the return data for Pop_Back\n");
    if(j != 23){
      printf("Return data value is incorrect\n");
    }else{
      printf("Return data value is correct\n");
    }    
    
    printf("Adding data 6 in at end of list with Push_Back\n");    
    
    Push_Back(&list, 6);
    
    if(Pop_Back(&list, &j) != 0){
      printf("Pop_Back for empty list correct\n");
    }else{
      printf("Pop_Back for empty list incorrect\n");
    }
  
    printf("Testing the return data\n");
    if(j != 6){
      printf("Return data value is incorrect\n");
    }else{
      printf("Return data value is correct\n");
    }    
 
    printf("\n");

 
    // write a beter test for Count_If
    printf("Count_If test\n");
    printf("Adding 2 new node to with same value after empty list\n");

    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);

    printf("Count_If expected 2 since checking for 5 (data value)\n");
    if(Count_If(list, 5) != 2){
      printf("Count_If is wrong\n");
    }else{
      printf("Count_If is correct\n");
    }

    printf("Testing Count_If after clearing the list\n");
    Clear(&list);
    
    //testing after clear 
    printf("After clear: "); 
    Print_List(stdout, list);
    
    printf("Count_If expected 0 since list is empty\n");
    if(Count_If(list, 0) != 0){
      printf("Count_If is wrong\n");
    }else{
      printf("Count_If is correct\n");
    }
 
    printf("\n");    

    // write a test for Delete 
    printf("Testing Delete\n");

    //adding newNodes since list is empty
    Push_Front(&list, 1);
    Push_Front(&list, 2);
    Push_Front(&list, 1);
    Push_Front(&list, 1);
    Push_Front(&list, 7);
    Push_Front(&list, 1);
    Push_Front(&list, 3);
    Push_Front(&list, 3);    

    Print_List(stdout, list);
    printf("Checking if first 1 is deleted\n");

    if(Delete(&list, 1) != 1){
      printf("Delete is wrong\n");
    }else{
      printf("Delete is correct\n");
    }
 
    Print_List(stdout, list);

    //checking for case when there is only 1 node with matching data val
   
    printf("Clearing the list\n");
    Clear(&list);

    //add a new node
    printf("Added a new node 3\n");
    Push_Front(&list, 3);    

    if(Delete(&list, 3) != 1){
      printf("Delete is wrong\n");
    }else{
      printf("Delete is correct\n");
    }
 
    printf("List: ");
    Print_List(stdout, list);

    //making sure no node is deleted if data doesn't match
    //added some nodes since the list is empty
    Push_Front(&list, 13);
    Push_Front(&list, 74);
    Push_Front(&list, 12);
    Push_Front(&list, 3);
    Push_Front(&list, 1); 

    printf("Added some nodes to check for no deletion of node if data doesn't match\n");
  
    printf("List after adding new nodes: ");
    Print_List(stdout, list);

    if(Delete(&list, 64) != 0){
      printf("Delete is wrong\n");
    }else{
      printf("Delete is correct\n");
    }
     
    printf("List after calling delete with data 64: ");
    Print_List(stdout, list);

    printf("Delete node at back (13)\n");

    if(Delete(&list, 13) != 1){
      printf("Delete is wrong\n");
    }else{
      printf("Delete is correct\n");
    }
  
    printf("List after calling delete with data 13: ");
    Print_List(stdout, list);

    printf("Delete node at middle (12)\n");

    if(Delete(&list, 12) != 1){
      printf("Delete is wrong\n");
    }else{
      printf("Delete is correct\n");
    }
  
    printf("List after calling delete with data 12: ");
    Print_List(stdout, list);

    printf("\n");

    // write a better test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    //Expected 0 since list is not empty    
    if(Is_Empty(list) != 0){
      printf("Is_Empty is wrong\n");
    }else{
      printf("Is_Empty is correct\n");
    }    

    //checking after clear
 
    printf("Testing Is_Empty after clearing the list\n");
    Clear(&list);
    
    //testing after clear 
    printf("After clear: "); 
    Print_List(stdout, list);
     
    //Expected 1 since list is empty after clear    
    if(Is_Empty(list) != 1){
      printf("Is_Empty is wrong\n");
    }else{
      printf("Is_Empty is correct\n");
    }    
   
    printf("\n");
 
    // write a better test for Clear
    printf("Testing for clear method\n");
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    if(list.head != NULL){
      printf("Clear method is wrong\n");
    }else{
      printf("Clear method is correct\n");
    }

    printf("Checking for size of list after clear\n");
    if(Size(list) != 0){
       printf("Clear method check for size is wrong\n");
    }else{
      printf("Clear method check for size is correct\n");
    }

    printf("\n");

    // write a better test for Remove_Duplicates
    printf("Test for Remove_Duplicates\n");
    Push_Back(&list, 1);
    Push_Front(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 1);
    Push_Front(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Front(&list, 7);

    printf("List before Remove_Duplicate\n"); 
    Print_List(stdout, list);
    
    Remove_Duplicates(&list);
 
    printf("List after Remove_Duplicate\n"); 
    Print_List(stdout, list);

    printf("Checking for size after Remove_Duplicates, expect 4\n"); 
    
    if(Size(list) != 4){
      printf("Remove_Duplicate for size is wrong\n");
    }else{
      printf("Remove_Duplicate for size is correct\n");
    } 

    //make sure only 1 element (7) isn't removed
    if(list.head->data != 7){
      printf("Remove_Duplicate for first element is wrong\n");
    }else{
      printf("Remove_Duplicate for first element is correct\n");
    }
    
    //testing for empty list 
    printf("Testing for empty list\n");
    Clear(&list);
    printf("List :"); 
    Print_List(stdout, list);
     
    Remove_Duplicates(&list);
 
    printf("List after Remove_Duplicate: \n"); 
    Print_List(stdout, list);

 
    return 0;
}
