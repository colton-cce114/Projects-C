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

int main(int argc, char *argv[])
{
  int i, size;
  char *arr[1024];
  char buf[1024];
  int fd[2]; //Pipes
  pid_t pid;
 
  if (pipe(fd) == -1)
    {
      perror("Failure to create pipes");
      exit(EXIT_FAILURE);
    }

  /* Fork the child */
  pid = fork();
  switch(pid)
    {
    case -1:
      perror("Failure to fork child");
      exit(EXIT_FAILURE);
  
    case 0:
      /* Consumer(child) stuff */
      close(fd[1]); //Close child output leaving input open

      /* Read size of data from pipe */
      //write(1, "Reading datasize...\n", 21);
      usleep(50000);
      if (read(fd[0], &size, sizeof(int)) == -1)
	{
	  perror("Failure to read size from the pipe");
	  exit(EXIT_FAILURE);
	}
      /* Read data from the pipe */
      write(1, "Reading data...\n", 17);
      for (i = 0; i < size; i++)
	{
	  if (read(fd[0], &buf[i], sizeof(char)) == -1)
	    {
	      perror("Failure to read data from the pipe");
	      exit(EXIT_FAILURE);
	    }
	
	}
      write(1, "Data received: ", 15);
      write(1, &buf, strlen(buf));
      write(1, "\n", 2);
      close(fd[0]);
      exit(EXIT_SUCCESS);
	       
    default:
      /* Producer(parent) stuff */
      close(fd[0]); //Close parent input leaving output open
      write(1, "Please enter text: ", 19);
      scanf("%s", buf);
      write(1, "\nTransmitting datasize...\n", 28);

      /* Write size of data to the pipe */
      if (write(fd[1], &size, sizeof(int)) == -1)
	{
	  perror("Failure to write size to pipe");
	  exit(EXIT_FAILURE);
	}
      /* Write data to the pipe */
      write(1, "Transmitting data...\n", 22);
      for (i = 0; i < strlen(buf); i++)
	{
	  if (write(fd[1], &buf[i], sizeof(char)) == -1)
	    {
	      perror("Failure to write data to pipe");
	      exit(EXIT_FAILURE);
	    }
	}
      write(1, "Data sent!\n", 12);
      close(fd[1]);
      exit(EXIT_SUCCESS);

    }
}
