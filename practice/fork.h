#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  pid_t childPID;

  printf("We are in the parent before creating the child\n");

  printf("Calling fork now ... a new child will soon be born\n\n");

  childPID = fork();
  /* 
     returns a -1 on error.
     returns a 0 in the child.
     returns the process id for the child in the parent
  */

  switch(childPID = fork())
    {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0: /* child */
      printf("We are in the child ... we will do child stuff\n");
      usleep(2000000);
      printf(">>Exiting the child ...\n");
      exit(EXIT_SUCCESS);
    default: /* parent */
      printf("<<We are in the parent, just after calling fork\n");
      printf("<<We will now wait on the child at pid %d to exit\n", childPID);
      while (1) //wait loop
	{
	  childPID = wait(NULL);
	  if (childPID == -1)
	    {
	      if (errno = ECHILD)
		{
		  printf("<<Our last child has stopped. Goodbye\n");
		  exit(EXIT_SUCCESS); //Exit parent
		}
	      else
		{
		  perror("wait");
		  exit(EXIT_FAILURE);
	        }
	    }
      }
   
}
}
