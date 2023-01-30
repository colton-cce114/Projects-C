/*
  Name: Cooper Earls
  NetID: cce114
  Compiler: gcc
  Program Description: This program counts the number of words or characters
                        in a file. 

                       It is called like: ./program.exe w c <filename>                               Those parameters being wordcount,charcount,filename

                       ****MAKE THE FILENAME LAST****

		       I'm not gonna lie some of the error checking could've
                       been way better but I just got back from Missouri
                       and I didn't have much time to work on this last 
                       week and it's 10:32 p.m. on Sunday so. It'll do for now.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
void signalHandler(int signum)
{
  if (signum == )
    {

    }
}
*/

void readStats(int type)
{
  if (type == 1) //c
    {
      
    }
  if (type == 2) //w
    {
      
    }
  if (type == 3) //c AND w
    {
      
    }
  
  if (type == 4) //c AND filename
    {
      
    }
  if (type == 5) //w AND filename
    {
      
    }
  if (type == 6) //c w AND filename
    {
      
    }
}

int main(int argc, char *argv[])
{
  char buf[1024];
  char chr;
  int readFd;
  int cont = 1;
  int numChar;
  int numWord;

  //struct sigaction handler; //Creates a sigaction
  //handler.sa_handler = signalHandler; //Assigns the signal handler to sigaction

  if (argc == 2)
    {
      if (strcmp(argv[1], "c")) //c
	{
	  readStats(1);
	}
      if (strcmp(argv[1], "w")) //w
	{
	  readStats(2);
	}
      perror("Can't have filename as only parameter");
      exit(EXIT_FAILURE);
    }
  
  if (argc == 3)
    {
      if (strcmp(argv[1], "c")) //Filename and c
	{
	  if (strcmp(argv[2], "w"))
	    {
	      readStats(3);
	    }
	  readFd = open(argv[2], O_RDONLY);
	  if (readFd == -1)
	    {
	      perror("Failed to find/open the file!");
	      exit(EXIT_FAILURE);
	    } 
	  readStats(4);
	}
      if (strcmp(argv[1], "w")) //Filename and w
	{
	  if (strcmp(argv[2], "c"))
	    {
	      readStats(3);
	    }
	  readFd = open(argv[2], O_RDONLY);
	  if (readFd == -1)
	    {
	      perror("Failed to find/open the file!");
	      exit(EXIT_FAILURE);
	    }
	  readStats(5);
	}
    }

  if (argc == 4)
    {
      if (strcmp(argv[1], "c"))
	{
	  if (strcmp(argv[2], "w"))
	    {
	      readFd = open(argv[3], O_RDONLY);
	      if (readFd == -1)
		{
		  perror("Failed to find/open the file!");
		  exit(EXIT_FAILURE);
		}
	      readStats(6);
	    }
	}
    }
  
  if ((argc<2) || (argc>4)) //3 < arguments < 1    (incorrect)
    {
      perror("Invalid number of arguments");
      exit(EXIT_FAILURE);
    }
  
}
