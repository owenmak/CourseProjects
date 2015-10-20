#include <stdlib.h>
#include <stdio.h>
#include <cstring>


/*This file contains a number of functions that contain
some pitfalls in using pointers/memory allocation/strings.
You are required to identify these pitfalls and fix them*/


/*The following function adds two vectors v1 and v2
  if and only if the sizes of both vectors are equal */
int *add_vectors(int *v1, int n1, int *v2, int n2) {
  int *result;
  if(n1 != n2) {
//    delete[] result;  PITFALL
    return NULL;
  }
  result = new int[n1];
  for(int i = 0; i < n1; i++)
    result[i] = v1[i] + v2[i];
  return result;
}

/*The following function divides v1[i]/v2[i]
  and returns the result in a new vector 
if any element of v2 is equal to 0, it returns NULL*/
int* divide_vectors(int *v1, int *v2, int n) {
  int *result = new int[n];
  for(int i = 0; i < n; i++) {
    if(v2[i] != 0)
      result[i] = v1[i] / v2[i];
    else{
	  delete[] result;//PITFALL
      return NULL;
	}
  }
  return result;
}

/*The following function does the following:
1. It takes two vector arrays of equal size as arguments.
2. It computes v1_0 * v2_0 ... v1_n * v2_n and places
the result in a temp vector.
3. it sums the values of the temp vector and returns the sum
*/
int sumOfSquares(int *v1, int *v2, int n) {
  int * temp = new int[n];
  for(int i = 0; i < n; i++)
    temp[i] = v1[i] * v2[i];
  int sum = 0;
  for(int i = 0; i < n; i++)
    sum += temp[i];
  delete[] temp;//PITFALL
  return sum;
}


/* The following function adds two numbers that are
passed by pointers. Assume the caller function looks something
like this:
int x = 10, y = 20;
int sum = add(&x, &y);*/
int add(int *n1, int *n2) {
  int sum = *n1 + *n2;
//  delete n1;
//  delete n2;
  return sum;
}

/*The following function copies n chars
from  str1 into str2
len is the number of chars in str1 to copy
into str2
*/

void strncp(char* str1, char* str2, int len) {
  for(int i = 0; i < len; i++)
//    *str2++ = *str1++;
	str2[i] = str1[i];
  str2[len] = 0; // null character
}

/* The following function sums two vectors and returns
   the resulting vector*/
int* sum_vectors(int *v1, int* v2, int nelements) {
  int *vsum = new int[nelements];
  for(int i = 0; i < nelements; i++)
     vsum[i] = v1[i] + v2[i];
//   delete[] vsum;  PITFALL
   return vsum;
}

/*the following function allocates at least 10 bytes of memory
  for the pointer ptr. The user is supposed to call this function
like this. 
You can change the type of the parameters, return value
or the way the caller uses the call.:
char *ptr;
allocate_atleast_10bytes(ptr, n);
ptr[5] = 'v';
You can change the type of the parameters, how they are used, return value
or the way the caller calls this function to solve the problem.:
*/
void allocate_atleast_10bytes(char *ptr, unsigned int nbytes) {
  if(nbytes < 10)
    nbytes = 10;
  ptr = new char[nbytes]; //the user is responsible for freeing memory
}

/* The following function computes the 
   median of an array of size n */

float median(int *arr, int len) {
  int *arr2 = new int[len];
  for(int i = 0; i < len; i++)
    arr2[i] = arr[i];
  
  //bubble sort arr2
  int * ptr1 = arr2;
  int * ptr2 = arr2;
  for(int i = 0; i < len; i++) {
    for(int j = 0; j < len-1; j++) {
      if (ptr2[j]>ptr2[j+1]) {
        int temp = ptr2[j];
        ptr2[j] = ptr2[j+1];
        ptr2[j+1] = temp;
      }
    }
  }
  
  int result;
  if(len % 2)
    result = arr2[len / 2];
  else
    result = (arr2[len / 2] + arr2[(len - 1) / 2]) / 2.0;

//  delete[] ptr1;
//  delete[] ptr2;
  delete[] arr2;
  return result;
}


/*This function duplicates a string. For example, "hello" becomes "hellohello"
 */
void strdup2(char* str) {
  int len = strlen(str);
/*  str+len = new char[len+1];
  strcpy(str+len, str);*/
  char *p = str+len;
  p = new char[len+1];
  memcpy(str + len, str, len);
//  strcpy(string, str);
//  strcpy(string + len, str);
//  free(str);
//  str = string;
}

/*creates an array of 10 arrays and then frees memeory*/
void create_and_free(int rows, int cols) {
  char **arr =  new char*[rows];
  for(int i = 0; i < rows; i++)
    arr[i] = new char[cols];

  //free memory
//  delete [] arr;
  for(int i = 0; i < rows; i++)
    delete[] arr[i];
  delete [] arr; //PITFALL
}

/*reverses a char array*/
void reverse(char *arr, int len) {
  char *arr2 = new char[len];
  if(len == 0);
  else if(len == 1) //no need to reverse
    delete[] arr2;
  else {
    for(int i = 0 ; i < len; i++)
      arr2[i] = arr[i];
    for(int i = 0 ; i < len; i++)
      arr[len - i - 1] = arr2[i];
	delete[] arr2;
  }
}

int main() {
  return 0;
}
