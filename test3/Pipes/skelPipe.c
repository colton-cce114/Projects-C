/*
  Name: Colton Earls
  NetID: cce114
  Compiler: gcc
  Program Description: This is the pipe skeleton program for test 3. 
  NOTES: I'm just trying to pass. I'm trying to demonstrate that even if  this doesn't work, I still understand what's going on. 


   Write a multiple concurrent process program that does the following
   1. Displays the contents of a file to STDOUT

   The program should perform this task in the following way:
   1. Report an error message if no file was specified
   2. Open a pipe to allow for communication between the parent and child

   3. Create a child process that:
      a. Dups the write side of the pipe to STDOUT
      b. Executes the cat function on the file specified in the 
         command line arguments

Note: cat is a program that is run from the linux command line .. just type man cat for more details.

   4. Create a parent process that:
      a. Reads character data from the read side of the pipe
      b. Outputs the data to STDOUT
   -- Make certain to continue reading from the pipe until all of the
      data has been read and sent to STDOUT
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

#define BUF_SIZE 4

void signalHandler(int sig)
{
  pid_t pid;

  /* WAIT WHILE CHILD IS ACTIVE */
  if (sig == SIGCHLD)
    {
      while((pid == waitpid(-1, NULL, 0)) > 0) continue;
    }
  
}

void assertFunction(int errorNum, const char *errorDesc)
{
  if (errorNum == -1)
    {
      perror(errorDesc);
      exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
  int i, size, numRead;
  char *arr[1024];
  char buf[1024];
  char chthing;
  int fd[2]; //Pipes
  int inFd;
  pid_t pid;

  /* Check for correct parameter count */
  if(argc != 2)
    {
      assertFunction(-1, "Please enter a valid file id as a parameter\n!");
    }

  assertFunction((inFd = open(argv[1], O_RDONLY)), "Failed to find the specified file");

  /* Make a pipe */
  assertFunction((pipe(fd)), "Failed to create pipe\n");


  
  /* Fork the child */
  pid = fork();
  switch(pid)
    {
    /* If fork failed */
    case -1:
      assertFunction(-1, "Failure to fork the child\n");


      
    /* What the child does */
    case 0:
      close(fd[0]);
      /* Kinda lazy way of  figuring out the size of the data to send */
      /* I suppose I could do this with read, but I'm not for ease */
      while(1)
	{
	  chthing = fgetc(inFd);
	  if (chthing == EOF)
	    {
	      break;
	    }
	  size++;
	}

      /* Write size to pipe */
      assertFunction((write(fd[1], &size, sizeof(int)) == -1), "Failed to write data size to pipe\n");

      /* I think this is what you meant. This should replace the write
         pipe of the child with stdout as an input feed instea. So
         if i use system call "cat" itll take whatever is spit out
         on terminal and send it through the pipe */
      assertFunction((dup2(fd[1], 1) == -1), "Failed to dup inFd to STDOUT\n");
      system("cat argv[1]");

      /* Close everything */
      close(fd[1]);
      close(inFd);


      
    /*What the parent does */
    default:
      close(fd[1]);
      close(inFd);
      usleep(50000);
      assertFunction((read(fd[0], &size, sizeof(int)) == -1), "Failed to read datasize\n");
      for (i = 0; i < size; i ++)
	{
	  assertFunction((read(fd[0], &buf[i], sizeof(char)) == -1), "Failed to read something coming from the pipe\n");
	}
      write(1, &buf, strlen(buf));
      close(fd[0]);
      exit(EXIT_SUCCESS);

    }
      
}
