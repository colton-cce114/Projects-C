#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void childstuff(int pos)
{
  printf("I am child number %d\n", pos);
}

int main(int argc, char *argv[])
{
  
  int userin; //Amount of children.
  int i;

  printf("Enter an integer between 1 and 10: ");
  scanf("%d", &userin);

  pid_t pidarray[userin]; //Make an array of pid's for <userin> children.

  //Fork every element from 0 to <userin>. Determine what to do with them. 
  for(i = 0; i < userin; i++)
    {
      if ((pidarray[i] = fork()) == -1) //IF WE FAILED TO FORK
	{
	  perror("Failed to fork");
	  exit(EXIT_FAILURE);
	}
      else if (pidarray[i] == 0) //IF WE SUCCESSFULLY FORKED
	{
	  childstuff(i);
	  exit(EXIT_SUCCESS);
	}
      
    }
  printf("We are all done");

  exit(EXIT_SUCCESS);
}
