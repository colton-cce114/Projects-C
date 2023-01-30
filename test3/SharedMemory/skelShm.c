/*
  Name: Colton Earls
  NetID: cce114
  Compiler: gcc
  Program Description: This is the shared memory skeleton for test 3. 
  NOTES: Not sure why we didn't seed time just once.


   Write a multiple concurrent process program that does the following
   1. Displays "ascii modern art" composed of a series of 
      randomly generated blocks of 2 or more repeating characters

   The program should perform this task in the following way:
   1. Create a semaphore set of size 2 -- use IPC_PRIVATE as your key
      a. Initialize the semaphore representing the child to available
      b. Initialize the semaphore representing the parent to in use
   2. Create a segment of shared memory -- use IPC_PRIVATE as your key

   3. Create a child process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator 
      c. Reserves the child semaphore
      d. Generates and stores the total number of blocks to generate. 
         This should be between 10 and 20
      c. For each block, generate and store the following values:
         1. The length of the block (i.e. the number of characters to display)
            This should be between 2 and 10
         2. The character that comprises the block.
            This should be between 'a' and 'z'
      d. Release the parent semaphore
      e. Reserve the child semaphore
      f. Detach the shared memory segment
      g. Release the parent semaphore

   4. Create a parent process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator
      c. Reserve the parent semaphore 
      d. Generate a random width for the ASCII art. 
         This should be between 10 and 15
      e. Using the data stored in the shared memory segment, output an image
         Use the following tips: 
         1. One value stored in the segment should represent the number
            of (length, character) pairings. For each (length, character)
            pairing, you should output length instances of the given 
            character. This means if the pairing was (3, 'b'), you would
            output "bbb".
         2. The random image has basically been encoded use run-length
            encoding (RLE); RLE doesn't including the location of new lines.
            The location of new lines is determined by the random width 
            generated in step d. Each time you output width total characters,
            output a new line.
      f. Release the child semaphore
      g. Reserve the parent semaphore
      h. Detach the shared memory segment

   5. Delete the semaphore
   6. Delete the shared memory
   
   -- You can use/should use the binary semaphore protocol introduced in class
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "binary_sem.h"

#define CHILD 0
#define PARENT 1

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

int checkCall(int val, char *msg)
{
  if (val == -1)
    {
      if (errno == EINTR) return -1;
      perror(msg);
      exit(EXIT_FAILURE);
    }
  return val;
}

int genRand(int low, int high)
{
  int rng = high - low +1;
  double drnd = rand();
  int irnd = drnd/((double) RAND_MAX + 1) * rng;
  return low + irnd;
}

/* I just figured this out, but if you cast a char directly onto
   an integer, it is automatically converted in ASCII */
char converter(int iarg)
{
  return((char)iarg);
}

/* Shared memory blueprint */
struct canvas
{
  int numBlocks; //Number of blocks
  int Blocks[20];
  int chars[20];
  int width;
};

int main(int argc, char * argv[])
{
  int i, j, size;
  int shmID, semID;
  pid_t pid;
  key_t shmKey, semKey;

  /* Declare the initial memory to-be-shared */
  struct canvas *beautifulPainting;

  write(1, "Booting Cooper's Epic Art Generator...\n", 40);
  shmKey = IPC_PRIVATE;
  semKey = IPC_PRIVATE;
  
  write(1, "Creating semaphore set...\n", 27);
  /* I THINK I can just substitute IPC_PRIVATE for the key so I will */
  /* Declare a fantastic semaphore set of size 2 */
  semID = checkCall(semget(semKey, 2, IPC_CREAT | S_IRUSR | S_IWUSR), "semget2");

  write(1, "Initializing semaphore set...\n", 31);
  /* Initializing as: Child->Available and  Parent->Reserved */
  initSemAvailable(semID, CHILD);
  initSemInUse(semID, PARENT);

  write(1, "Creating shared memory segment...\n", 35);
  /* Make our beautifulPainting shared memory */
  shmID = checkCall(shmget(shmKey, sizeof(struct canvas), IPC_CREAT | S_IRUSR | S_IWUSR), "shmget1");
  write(1, "Forking a child...\n", 20);
  /* Creating a child process */
  pid = fork();
  switch(pid)
    {
    case -1:
      assertFunction(-1, "Failure to fork child...\n");

      
      /*---------- What the child does ----------*/
    case 0:
      beautifulPainting = (struct canvas *) shmat(shmID, NULL, 0);
      if (beautifulPainting == (void *) -1) checkCall(-1, "Failed to attach shared memory in child");
      srand(time(NULL));
      reserveSem(semID, CHILD);

      /* Generate the number of blocks we will have */
      beautifulPainting->numBlocks = genRand(10, 20);
      for (i = 0; i < beautifulPainting->numBlocks; i++)
	{
	  /* Sets the length for each block */
	  beautifulPainting->Blocks[i] = genRand(2, 10);
	  /* Sets the char for each block */
	  beautifulPainting->chars[i] = genRand(97, 122);
	}
	     
      /* Release parent's semaphore, reserve the child's */
      releaseSem(semID, PARENT);
      reserveSem(semID, CHILD);

      /* Detach shared memory, release the semaphore */
      shmdt(beautifulPainting);
      checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl in child");
      checkCall(semctl(semID, 0, IPC_RMID), "semctl in child");
      exit(EXIT_SUCCESS);

      
      /*---------- What the parent does ----------*/
    default:
      beautifulPainting = (struct canvas *) shmat(shmID, NULL, 0);
      if (beautifulPainting == (void *) -1) checkCall(-1, "Failed to attach shared memory in parent");
      srand(time(NULL));
      reserveSem(semID, PARENT);

      /* Set the width */
      beautifulPainting->width = genRand(10, 15);
      
      /* Output the image */
      usleep(50000);
      int count;
      for (i = 0; i < beautifulPainting->numBlocks; i++)
	{
	  for (j = 0; j < beautifulPainting->Blocks[i]; j++)
	    {
	      if (count == (beautifulPainting->width - 1))
		{
		  write(1, "\n", 2);
		}
	       else
		{
		  write(1, converter(beautifulPainting->chars[i]), 1);
		}
		
	    }
	      
	}

      releaseSem(semID, CHILD);
      reserveSem(semID, PARENT);
	   
      /* Detach shared memory, release the semaphore */
      shmdt(beautifulPainting);
      checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl in child");
      checkCall(semctl(semID, 0, IPC_RMID), "semctl in child");
      exit(EXIT_SUCCESS);
    }   
  
}
