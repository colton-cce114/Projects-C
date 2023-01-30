/* Write a multiple concurrent process program that does the following
1. Prompts the user for the number of words to enter
   2. Prompts the user for each word and writes them into 
      a file named word.dat
   3. Determines how many words are > “too”
   4. Determines how many words are < “five”
   5. Outputs the total count for each group.

   The program should perform this task in the following way:
   Create a producer child that:
   1. Prompts the user for the number of words to enter
   2. Prompts the user for each word and writes them into a file
      named word.dat
   Create a consumer child that:
1.	For each value in the file
	a.	Determine if value > “too”
	b.	If the value > “too”, signals the parent with SIGUSR2
   Create a consumer child that:
1.	For each value in the file
	a.	Determines if value < “five”
	b.	If the value < “five”. signals the parent with SIGUSR1
   Create a parent that: 
   1. Creates children 1 - 3
   2. Pauses. 


 */

/* Problem 1(DONE) - Include files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

/* Problem 2(DONE) - Global ariables. 
   Declare the global variables for pid's of the three
   children and the two integers that serve the role of flags and
   counters. The first flag deals with the large count; the second
   flag deals with the small count.
 */

static pid_t childPID1;
static pid_t childPID2;
static pid_t childPID3;
int largeCount, smallCount;

#define BUF_SIZE 1024


/* myPrint is a convenience function to use when we are in a signal 
   handler. This is because printf uses buffered I/O.
 */
void myPrint(const char *str)
{
  if (write(STDOUT_FILENO, str, strlen(str)) == -1)
    {
      perror("write");
      exit(EXIT_FAILURE);
    }
}

/* Signal handlers
   We will need to implement at least two signal handlers. 
   One for the parent and a minimum of one for the children
 */

/* Problem 3(50%) - Define and write the signal handler for the parent */
static void signalHandlerParent(int sig)
{
  if (sig == SIGUSR1)
    {
      smallCount += 1;
    }
  if (sig == SIGUSR2)
    {
      laargeCount += 1;
    }
  if (sig == SIGCHLD)
    {

      buf[1024] = "All children have terminated...";
      write(STDOUT_FILENO, buf, strlen(buf));
      exit(EXIT_SUCCESS);
    }
}

/* Problem 4(DONE) - Define and write the signal handler for the children */
static void signalHandlerChild(int sig)
{
  if (sig == SIGUSR1)
    {
      smallCount = 1;
    }
  if (sig == SIGUSR2)
    {
      largeCount = 1;
    }
}

/* Functions for each of the children. 
   We will be writing functions for each of the three children.
   This should make it easier to answer the questions on threads.
 */

/* Problem 5. Define and write the function for child 1. */
void childfunc1()
{
  int words, i;
  int outFile, openFlags, filePerms;
  
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = signalHandlerChild;
  sa.sa_flags = 0;

  //Make the file
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | IWOTH;
  outFile = open("word.dat", openFlags, filePerms);

  //Prompt
  myPrint("Please enter the number of words:\n ");

  for (i=0; i<words; i++)
    {
      read(STDIN_FILENO, words, 4);
      myPrint("\n");
      write(outFile, words, strlen(words));
    }
  close(outFile);
}
/* Problem 6. Define and write the function for child 2. */
void childfunc2()
{
  int inFile;
  
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = signalHandlerChild;
  sa.sa_flags = 0;

  while(largeCount == 0)
    {
      pause();
    }

  inFile = open("word.dat", O_RDONLY);
  if (inFile == -1)
    {
      perror("Failed to find/open word.dat in child 2");
      exit(EXIT_FAILURE);
    }


  
  close(inFile);
  myPrintInt(largeCount);
}
/* Problem 7. Define and write the function for child 3. */
void childfunc3()
{
  int inFile;
  
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = signalHandlerChild;
  sa.sa_flags = 0;

  while(smallCount == 0)
    {
      pause();
    }

  inFile = open("word.dat", O_RDONLY);
  if (inFile == -1)
    {
      perror("Failed to find/open word.dat in child 3");
      exit(EXIT_FAILURE);
    }



  close(inFile);
  myPrintInt(largeCount);
}
/* This function forks a child and runs the function passed
   in after the child has successfully forked. I have provided
   it to make the code easier to read.
 */
pid_t hndlFork(void (*child)(void))
{
  pid_t p;
  p = fork();
  if (p == -1)
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
  if (p == 0)
    {
      child();
    }
  return p;
}

 void myPrint(const char *str) //For convenience
 {
   write(STDOUT_FILENO, std, strlen(str));
 }

 void myPrintInt(const in val)
 {
   char buffer[1024];
   sprintf(buffer, "%i", val);
   write(STDOUT_FILENO, buffer, strlen(buffer));
 }

/* Problem 8(50%) - Define and write the function main */


int main(int argc, char *argv[])
{ 
  childPID2 = hndlFork(child2func);
  childPID3 = hndlFork(child3func);

  childPID1 = hndlFork(child1func);
  while(1)
    {
      pause();
    }

  exit(EXIT_SUCCESS);
}
