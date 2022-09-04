/* Wai Zin Linni
 * 9082616286
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

void Clean_Whitespace(char str[]) {

    //Leading
    //Algortihm from: https://www.geeksforgeeks.org/c-program-to-trim-leading-white-spaces-from-string/

    char tempArr[99];
    int firstIdx  = 0;
    int g;
    int h;

    //getting the first index of alphabet after space, tabs and newlines, if false the loop won't execute

    while(str[firstIdx] == ' ' || str[firstIdx] == '\t' || str[firstIdx] == '\n'){
	    firstIdx++;
    }
      
    //start copying from first alphabet into tempArr

    for(g = firstIdx, h = 0; str[g] != '\0'; g++, h++){
    	tempArr[h] = str[g];
    }

    tempArr[h] = '\0';

    // check if there are leading trail, if yes, modify str char array
        
    if(firstIdx != 0){

	 //copying back into str from tempArr
	
	 int y;
	 
	 for(y = 0; tempArr[y] != '\0'; y++){
	 	str[y] = tempArr[y];
	 }

	 str[y] = '\0';
    }
	    
    //Trailing 

    int lastIdx = -1;
    int i = 0;

    //getting the last letter in the char array 
    
    while(str[i] != '\0'){
	if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
		lastIdx = i;
	}
	i++;
    }

    //stop after the last letter

    str[lastIdx+1] = '\0';

    //Internal
    
   for(int z = 0; str[z]; z++){

	 // if there are internal spaces then shift the characters back 

	 if(str[z] == ' ' && str[z+1] == ' '){
	    int n;
	    for(n = z; str[n]; n++){
		str[n] = str[n+1];
	      }	
	     z--;
	  } 
    }

    return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
    
    int i;
    char tempArr[99];

    for(i = 0; str[i]; i++){

	 // capitalizing first character and start of new chracter 

         if(( i == 0 && str[i] != ' ')|| (str[i] != ' ' && str[i-1] == ' ')){
	     if(str[i]>='a' && str[i]<='z'){
		  tempArr[i]=(char)(str[i] - ('a'-'A'));
	     }else{
	             tempArr[i] = str[i];
	      }
	
	// making other characters lower case
	
	}else if(str[i]>='A' && str[i]<='Z'){
	      tempArr[i]= (char) (str[i]+('a'-'A')); 
	    }else{
		   tempArr[i] = str[i];
	       }
	}		
		
    tempArr[i] = '\0';
    
    // copying back into str char array

    int k;

    for(k = 0; tempArr[k] != '\0'; k++){
	 str[k] = tempArr[k];
    }

    str[k] = '\0';
  
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    return atoi(str);
}


/* this function takes the name of a 
 * director as a string and removes all but
 * the last name.  Example:
 * "Bucky Badger" -> "Badger"
 */
void Director_Last_Name(char str[]) {
    
    // cleaning up str char array to handle white space tests
    Clean_Whitespace(str);
    Fix_Case(str);

    int lastIdx = 0;
    int i = 0;

    //get the last white space of char array

    while(str[i] != '\0'){
	if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n'){
	 lastIdx = i;
	}
	i++;
    }

    char tempArr[99];

    // start copying chracters after last white space
    if(lastIdx != 0){

	int w;
	int j;

    	for(w = 0, j = lastIdx+1; str[j] != '\0'; w++, j++){
	    tempArr[w] = str[j];
    	}

    	tempArr[w] = '\0';
    }else{

	int u;

	for(u = 0; str[u] != '\0'; u++){
		tempArr[u] = str[u];
	}

	tempArr[u] = '\0';	
    }
    
    int k;

    for(k = 0; tempArr[k] != '\0' ; k++){
    	str[k] = tempArr[k];
    }

    str[k] = '\0';
    return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    return atof(str);
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    
    int i;
    char clearWhiteSpace[99];
    int size;

    // getting the number of characters in str character array 

    for(i = 0, size = 0; str[i] != '\0'; i++){
	 if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
	    clearWhiteSpace[size] = str[i];
	    size++;
	 }
    }

    clearWhiteSpace[size] = '\0';

    // getting the last character of char array 

    char lastChar = str[size-1];
    
    //just return normal number if last character is not M, m, k r K

    if(lastChar != 'M' && lastChar != 'm' && lastChar != 'K' && lastChar != 'k'){
	return atof(clearWhiteSpace) * 1L;	
    }

    int j;
    char tempArr[99];
	
    for(j = 0; clearWhiteSpace[j] != '\0'; j++){
	  if(j != size - 1){
	     tempArr[j] = clearWhiteSpace[j];
	    }
      }

    tempArr[j] = '\0';
   
   // calcualting the number if last character ends with M,m,K or k

    float number = atof(tempArr);
    long long total = 0LL;   
   
    if(lastChar == 'M' || lastChar == 'm'){
	total = number * 1000000LL;
    }else if(lastChar == 'K' || lastChar == 'k'){
        total = number * 1000LL;
    }

    return total;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {

    int count = 0;
    int j = 0;
    char buf[6][1024];

    // reading csv row by row

    for(int i = 0; i < num_movies; i++){	   
	   for (int m = 0; m < 6; m ++ ){
		 while(csv[i][count] != ',' && csv[i][count] != '\0'){
                     buf[m][j] = csv[i][count];
                     j++;
                     count++;
            	}
		 buf[m][j] = '\0';
		 count ++;
		j = 0;
	   } 

	   // getting titles that are read into buf back into titles array

	   int buf_i = 0;
	   while(buf[0][buf_i] != '\0'){
		titles[i][buf_i] = buf[0][buf_i];
		buf_i++;
	   }

	   titles[i][buf_i] = '\0';

	   // modifying titles

	   Fix_Case(titles[i]);
	   Clean_Whitespace(titles[i]);

	   // reading years into years

	   years[i] = String_To_Year(buf[1]);

           Director_Last_Name(buf[3]);
	
	   // rreading directors into directors char array
   	   	   
	   buf_i = 0;

	   while(buf[3][buf_i] != '\0'){
                directors[i][buf_i] = buf[3][buf_i];
                buf_i++;
           }

	  directors[i][buf_i] = '\0';
	  
	  ratings[i] = String_To_Rating(buf[4]);

	  //reading in follars into dollars char array

	  dollars[i] = String_To_Dollars(buf[5]);

	  //resetting count to start reading from next row

	  count = 0;

         }

    return;
}



/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
   
    // finding longest Movie length

    int longestMovieLength = 0;
    for(int g = 0; titles[g][0] != '\0'; g++){
	  int count = 0;
	  for(int u = 0; titles[g][u] != '\0'; u++){
		count++;
		if(count > longestMovieLength){
		   longestMovieLength = count;
		}
	}
    }

    // following the movie length specification

    if(longestMovieLength+2 < 7){
	longestMovieLength = 7;
    }else{
  	longestMovieLength += 2;
    }

    // finding longest director length

    int longestLengthDirector = 0;
    for(int row = 0; directors[row][0] != '\0'; row++){
	    int directCounter = 0;
	    for(int col = 0; directors[row][col] != '\0'; col++){
		directCounter++;
		if(directCounter > longestLengthDirector){
			longestLengthDirector = directCounter;
		}
	    }
    }

    // following the director length specification

    if(longestLengthDirector+2 < 10){
	longestLengthDirector = 10;
    }else{
	longestLengthDirector += 2;
    }

    // printing out table as specified by instruction

    char headers[20][20] = {{"Id"},{"Title"},{"Year"},{"Director"},{"Rating"},{"Revenue"}};
 
    for(int i = 0; i < num_movies;i++){

	  if(i == 0){
	     printf("%-3s%-*s%-6s%-*s%6s%11s\n", headers[i], longestMovieLength, headers[i+1], headers[i+2], longestLengthDirector, headers[i+3], headers[i+4], headers[i+5]); 
	  }
	  
	  printf("%-3d%-*s%-6d%-*s%6.1f%11lld\n",i+1, longestMovieLength, titles[i], years[i], longestLengthDirector, directors[i], ratings[i], dollars[i]); 
    }

    return;
}
