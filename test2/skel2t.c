/* Write a threaded program that does the following
1. Prompts the user for the number of words to enter
   2. Prompts the user for each word and writes them into 
      a file named word.dat
   3. Determines how many words are > “too”
   4. Determines how many words are < “five”
   5. Outputs the total count for each group.

   The program should perform this task in the following way:
   Create a producer thread that:
   1. Prompts the user for the number of words to enter
   2. Prompts the user for each word and writes them into a file
      named word.dat
   Create a consumer thread that:
   1. Determines how many words are > “too”
   2. Outputs that value
   3. Sets that value to its exit value
   Create a consumer thread that:
   1. Determines how many words are < “five”
   2. Outputs that value
   3. Sets that value to its exit value
   Create a main thread that: 
   1. Creates threads 1 - 3
   2. Waits on the values of threads 2 and 3. 
   3. Outputs the values from threads 2 and 3.

 */

/* Problem 1(DONE) - Include files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>

/* 
   Global variables:
   We will need a mutex, a condition variable, and a predicate variable. 
   Recall that the predicate variable is the variable we use to determine
   whether data was available prior to our first call to pthread_cond_wait

 */

/* Problem 2. Declare the global variables for the predicate variable, 
   the mutex, and the condition variable. Do no forget to initialize 
   the mutex and the condition variable 
 */





/* This is a convenience function for dealing with errors
   and threads
 */

void hndlError(int error, const char *str)
{
  if (error == 0) return;
  errno = error;
  perror(str);
  exit(EXIT_FAILURE);
}


/* Define the three thread start functions. 
   You can name them whatever you wish 
 */

/* Problem 3. Define and write the start function for thread 1 */









/* Problem 4. Define and write the start function for thread 2 */











/* Problem 5. Define and write the start function for thread 3 */










/* Problem 6: Define and write the function for the main thread */



int main(int argc, char *argv[])
{



  exit(EXIT_SUCCESS);
}
