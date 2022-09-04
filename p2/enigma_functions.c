/* Wai Zin Linn
*  9082616286
*/

#include "enigma.h"
#include <stdio.h>
#include <string.h>

const char *ROTOR_CONSTANTS[] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ", // Identity Rotor (index 0 - and useful for testing):
                                           
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        "VZBRGITYUPSDNHLXAWMJQOFECK",
        "JPGVOUMFYQBENHZRDKASXLICTW",
        "NZJHGRCXMYSWBOUFAIVLPEKQDT",
        "FKQHTLXOCBJSPDZRAMEWNIUYGV",
};

// This method reads a character string from the keyboard and 
// stores the string in the parameter msg.
// Keyboard input will be entirely uppercase and spaces followed by 
// the enter key.  
// The string msg should contain only uppercase letters spaces and 
// terminated by the '\0' character
// Do not include the \n entered from the keyboard
void Get_Message(char msg[]){
    char buffer[81];
    scanf("%[^\n]%*c",buffer);
    
    int i = 0;
    while(i < 80){
      msg[i] = buffer[i];
      i++;
    }

    msg[i] = '\0';
    
    return;
}

// This function reads up to 4 characters from the keyboard
// These characters will be only digits 1 through 8. The user
// will press enter when finished entering the digits.
// The rotor string filled in by the function should only contain 
// the digits terminated by the '\0' character. Do not include
// the \n entered by the user. 
// The function returns the number of active rotors.
int Get_Which_Rotors(char which_rotors[]){

    int counter = 0;
    int number = 0;
    char tempArr[80];

    // Scanning in all the user input but just reading in
    // first 4 characters into which_rotors

    scanf("%[^\n]%*c",tempArr);
    int j;

    for(j = 0; j < 4;j++){
        number = tempArr[j] - '0';
        if(number >= 1 && number <= 8){
            which_rotors[counter++] = tempArr[j];
        }
    }

    which_rotors[counter] = '\0';

    return counter;    
} 

// This function reads an integer from the keyboard and returns it 
// This number represents the number of rotations to apply to the 
// encryption rotors.  The input will be between 0 and 25 inclusive
int Get_Rotations(){
    int number;
    scanf("%d", &number);
    return number;
}


// This function copies the rotors indicated in the which_rotors string 
// into the encryption_rotors.  For example if which rotors contains the string 
// {'3', '1', '\0'} Then this function copies the third and first rotors into the 
// encryption rotors array in positions 0 and 1.  
// encryptions_rotors[0] = "BDFHJLCPRTXVZNYEIWGAKMUSQO"
// encryptions_rotors[1] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
void Set_Up_Rotors(char encryption_rotors[4][27], char which_rotors[5]){

    int number = 0;
    int j, k;

    // Getting the chracter array of rotors based on the 
    // number that has been inputed into which_rotors

    for(j = 0; which_rotors[j] != '\0'; j++){
        number = which_rotors[j] - '0';
        for(k = 0; ROTOR_CONSTANTS[number][k] != '\0'; k++){
            encryption_rotors[j][k] = ROTOR_CONSTANTS[number][k];
        }
        encryption_rotors[j][k]='\0';
      } 
}


// This function rotates the characters in each of the active encryption rotors
// to the right by rotations.  For example if rotations is 3 encryption_rotors[0]
// contains "BDFHJLCPRTXVZNYEIWGAKMUSQO" then after rotation this row will contain
// SQOBDFHJLCPRTXVZNYEIWGAKMU.  Apply the same rotation to all for strings in 
// encryption_rotors
void Apply_Rotation(int rotations, char encryption_rotors[4][27]) {

    int h, i, shiftIdx;
    char lastChar;
    int size = strlen(encryption_rotors[0]);
    
    // Shifting the encryption rotors to amount sepcified by rotations
    // to the right

    h = 0;
    while(h < rotations){
        for(i = 0; i < 4; i++){
            lastChar = encryption_rotors[i][size-1];
            for(shiftIdx = size-1; shiftIdx > 0; shiftIdx--){
               encryption_rotors[i][shiftIdx] = encryption_rotors[i][shiftIdx-1];
               
            }
            encryption_rotors[i][0] = lastChar;
        }
        h++;
      }
}

// This function takes a string msg and applys the enigma machine to encrypt the message
// The encrypted message is stored in the string encryped_msg 
// Do not change spaces, make sure your encryped_msg is a \0 terminated string
void Encrypt(char encryption_rotors[4][27], int num_active_rotors, char msg[], char encrypted_msg[]){

    int msgCount, h;
    
    // To encrypt the first rotor, we need to get the alahabet that is in same index as where alphabet is found in identity
    // rotor. Then we get the alphabet from rotor that we ecrypting that is in same index(index where msg alphabet is found in identity rotor). 
    // For rest of the encryption, we will first get the encrypted alphabet index at identity
    // and put the corresponding index alphabet from rotor that we are encrypting from into encrypted_msg. 

    for(h = 0; h < num_active_rotors; h++){
        for(msgCount = 0; msg[msgCount] != '\0'; msgCount++){
            if(msg[msgCount] == ' '){
                encrypted_msg[msgCount] = ' ';
            }else{
               if(h == 0){
                encrypted_msg[msgCount] = encryption_rotors[h][msg[msgCount]-'A'];
               }else{
                 encrypted_msg[msgCount] = encryption_rotors[h][encrypted_msg[msgCount]-'A'];
              }
            }
        }
        encrypted_msg[msgCount] = '\0';
    }

    int i;

    for(i = 0; encrypted_msg[i] != '\0'; i++){
        msg[i] = encrypted_msg[i];
    }

    msg[i] = '\0';

    return;

}


// This function takes a string msg and applys the enigma machine to decrypt the message
// The encrypted message is stored in the string encryped_msg and the decrypted_message 
// is returned as a call by reference variable
// remember the encryption rotors must be used in the reverse order to decrypt a message
// Do not change spaces, make sure your decrytped_msg is a \0 terminated string
void Decrypt(char encryption_rotors[4][27], int num_active_rotors, char encrypted_msg[], char decrypted_msg[]) {
  
  int activeIdx, msgCount;  
  
  // We will decrypt by reversing the order of the rotor. For first decryption (last rotor used to encrypt), we first get 
  // the encrypted index of where encrypted alphabet is found on the rotor and pass that idex to identity rotor. 
  // Then we utlize the msg that has been decrypted first time to go find the index of alphabets where it would lie
  // in rotors and passed that index into identity rotor. 

  for(activeIdx = num_active_rotors-1; activeIdx >= 0; activeIdx--){
      for(msgCount = 0; encrypted_msg[msgCount] != '\0'; msgCount++){

          if(encrypted_msg[msgCount] == ' '){
              decrypted_msg[msgCount] = ' ';
          }else{
  
          if(activeIdx+1 == num_active_rotors){
          
             int idx = 0;
      
            for(int search = 0; search < 27; search++){
               if(encryption_rotors[activeIdx][search] == encrypted_msg[msgCount]){
                     idx = search;       
                }
            }
        
           decrypted_msg[msgCount] = ROTOR_CONSTANTS[0][idx];
        
          }else{
          
             int idx = 0;

             for(int search = 0; search < 27; search++){
                 if(encryption_rotors[activeIdx][search] == decrypted_msg[msgCount]){                         
                      idx = search;
                   }
               }        
             
             decrypted_msg[msgCount] = ROTOR_CONSTANTS[0][idx];
            }
          }
        }
           decrypted_msg[msgCount] = '\0';
       }
           return;
}


