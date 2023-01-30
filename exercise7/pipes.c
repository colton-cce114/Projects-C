#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <wait.h>

void signalHandler(int sig)
{
  pid_t pid;

  if (sig == SIGCHLD)
    {
      while((pid == waitpid(-1, NULL, 0)) > 0) continue;
    }
	
}

int getRand(int low, int high)
{
  int rng = high - low + 1;
  double drnd = rand();
  int irnd = drnd/((double) RAND_MAX + 1) * rng;
  return low + irnd;
}

int main(int argc, char *argv[])
{
  int cnt, val;
  int i, total;
  int fd[2]; //Pipe is stored in an array 
  pid_t pid;
  struct timespec uslp;
  uslp.tv_sec = 0;
  uslp.tv_sec = 500000;

  srand(time(NULL)); //Seed rang with time

  /* Before making the child, open the pipe */
  if (pipe(fd) == -1)
    {
      perror("Failure to pipe");
      exit(EXIT_FAILURE);
    }
  
  pid = fork();
  switch(pid)
    {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      /* in the producer, close the read side */
      close(fd[0]);
      /* In the child */
      cnt = getRand(1,10);
      if (write(fd[1], &cnt, sizeof(int)) == -1)
	{
	  perror("Failure to write to pipe");
	  exit(EXIT_FAILURE);
	}
      usleep(3);
      for (i = 0; i < val; i++)
	{
	  val = getRand(1, 100);
	  if (write(fd[1], &val, sizeof(int)) == -1)
	    {
	      perror("Failure to write to pipe(2)");
	      exit(EXIT_FAILURE);
	    }
	  
	}
      /* Close the right side of the pipe */
      close(fd[1]); 
      exit(EXIT_SUCCESS);

    default:
      /* in the consumer, close the write side of the pipe */
      close(fd[1]);
      total = 0;
      /* read a value here */
      if (read(fd[0], &cnt, sizeof(int)) == -1)
	{
	  perror("Failure to read from pipe");
	  exit(EXIT_FAILURE);
	}
      printf("Reading %d values from the pipe\n", cnt);
      for (i = 0; i < cnt; i++)
	{
	  /* read a value here */
	  if (read(fd[0], &val, sizeof(int)) == -1)
	    {
	      perror("Failure to read from pipe(2)");
	    }
	  printf("Value %d = %d\n", (i + 1), val);
	  total += val;
	}
      printf("%d\n", total);
      close(fd[0]);
      exit(EXIT_SUCCESS);
      
    }
  
}
