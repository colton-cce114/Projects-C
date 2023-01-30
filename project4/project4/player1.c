/*
  Name: Colton Earls
  NetID: cce114
  Compiler: gcc
  Program Description: This is going to be the player 1 program

  Task List for Player 1:
       1. Make a FIFO called "xoSync". If it already exists
          continue. 
       2. Generate 2 random numbers. They're going to be used for 
          System V keys. 
       3. Generate the System V keys with ftok using the random 
          numbers and the FIFO xoSync. 
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

#define PLAYER1 0
#define PLAYER2 1

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

/* This is the struct for the game board in shared memory */
struct tictactoe
{
  int turnCounter;
  int gameBoard[3][3];
  
};


int main(int argc, char *argv[])
{
  int i, j, size;
  key_t shmKey, semKey;
  int shmID, semID;
  int fdFIFO;
  int playerNum = atoi(argv[1]);
  int rand1 = genRand(1, 999);
  int rand2 = genRand(1000, 1999);

  /* Initialize rand to time */
  srand(time(NULL));
  
  /* Declare the shared memoory thing */
  struct tictactoe *game;
  
  /* Check if they entered a parameter */
  if (argc != 2)
    {
      assertFunction(-1, "Input player position as a paramerer (-1/1)");
    }

  /* Check if they entered a valid parameter */
  if (playerNum == -1) //Player 1
    {
      printf("Player 1\n");
    }
  else if (playerNum == -2) //Player 2
    {
      printf("Player 2\n");
    }
  else
    {
      assertFunction(-1, "Input valid player ID (-1/-1)");
    }

  /* Generate Keys for the semaphor group and the sahred memory */
  shmKey = ftok("./key", rand1);
  semKey = ftok("./key", rand2);

  /* Create the semaphors and shared memory */
  shmID = checkCall(shmget(shmKey, sizeof(struct tictactoe), IPC_CREAT | S_IRUSR | S_IWUSR), "shmget1");
  semID = checkCall(semget(semKey, 2, IPC_CREAT | S_IRUSR | S_IWUSR), "semget2");

  /* Initialize semaphore values. , Player 2 is used */
  initSemAvailable(semID, PLAYER1);
  initSemInUse(semID, PLAYER2);
  
  /* Attach the shared memory */
  game = (struct tictactoe *) shmat(shmID, NULL, 0);
  if (game == (void *) -1) checkCall(-1, "shmat in player 1");

  /* Open a FIFO for WRITE*/
  if (mkfifo("xoSync", S_IRWXU) == -1)
    {
      if (errno != EEXIST)
	{
	  assertFunction(-1, "FIFO already exists");
	}
    }
  
  fdFIFO = open("xoSync", O_WRONLY);
  if (fdFIFO == -1)
    {
      perror("Failed to open the FIFO(Player 1)\n");
      exit(EXIT_FAILURE);
    }

  /* Write the 2 random numbers for process 2 */
  assertFunction(write(fdFIFO, &rand1, sizeof(int)), "Failed to write #1");
  assertFunction(write(fdFIFO, &rand2, sizeof(int)), "Failed to write #2");
  close(fdFIFO);

  /* Enter the game loop!!!! 
  while(game->turnCounter != -1)
    {
      
    }
  reserveSem(semID, PLAYER1);
  */
  
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      game->gameBoard[i][j] = 0;
    }
  }
  game->gameBoard[0][0] = 1;
  game->gameBoard[1][1] = 1;
  game->gameBoard[2][2] = 1;
  game->turnCounter = 5;

  /* Detach the shared memory/delete the semaphore set */
  shmdt(game);
  checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl");
  checkCall(semctl(semID, 0, IPC_RMID), "semctl");
  
  exit(EXIT_SUCCESS);
  
}
