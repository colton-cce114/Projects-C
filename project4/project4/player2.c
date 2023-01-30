/*
  Name: Colton Earls
  NetID: cce114
  Compiler: gcc
  Program Description: This is the player 2 program
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

void assertFunction(int errorNum, const char *errorDesc)
{
  if (errorNum == -1)
    {
      if (errno == EINTR) return -1;
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

/* This is the struct for the game board in shared memory */
struct tictactoe
{
  int turnCounter;
  int gameBoard[3][3];
  
};

int main(int argc, char *argv[])
{
  int i, j, size, rand1, rand2;
  key_t shmKey, semKey;
  int shmID, semID;
  int fdFIFO;
  int playerNum;

  /*
  if (argc != 2)
    {
      assertFunction(-1, "Input player position as a paramerer (-1/1)");
    }
  
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
  */
  
  
  /* Open a FIFO for READ*/
  if (mkfifo("xoSync", S_IRWXU) == -1)
    {
      if (errno != EEXIST)
	{
	  assertFunction(-1, "FIFO already exists");
	}
    }
  fdFIFO = open("xoSync", O_RDONLY);
  if (fdFIFO == -1)
    {
      perror("Failed to open the FIFO(Player 1)\n");
      exit(EXIT_FAILURE);
    }

  /* Receive the 2 random numbers from process 1 */
  assertFunction(read(fdFIFO, &rand1, sizeof(int)), "Failed to read #1");
  assertFunction(read(fdFIFO, &rand2, sizeof(int)), "Failed to read #2");
  close(fdFIFO);

  wait(5);
  
  /*Generate keys for the semaphor set and the shared memory */
  shmKey = ftok("./key", rand1);
  semKey = ftok("./key", rand2);

  /* Retrieve the shared memory and semaphore set */
  shmID = checkCall(shmget(shmKey, 0, 0), "shmget");
  semID = checkCall(semget(semKey, 0, 0), "semget");

  /* Declare the shared memoory thing */
  struct tictactoe *game;
  
  /* Attach the shared memory */
  game = (struct tictactoe *) shmat(shmID, NULL, 0);
  if (game == (void *) -1) checkCall(-1, "shmat in player 1");

  while(game->turnCounter != 5)
    {
      continue;
    }
  for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 3; j++)
      {
	printf("%d ", game->gameBoard[i][j]);
      }
      printf("\n");
    }
  
  /* Detach the shared memory/delete the semaphore set */
  shmdt(game);
  checkCall(shmctl(shmID, IPC_RMID, NULL), "shmctl");
  checkCall(semctl(semID, 0, IPC_RMID), "semctl");
  
  exit(EXIT_SUCCESS);
  
}
