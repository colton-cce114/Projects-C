/* Name: Colton Earls
   NetID: cce114
   Compiler: gcc
   Program Description: This program reads from a flowData.dat file. 
                        It is simulating a flow governor. It reports low and
                        high values to the screen, and also the time since
                        the last alert. 
                        Low Range   Nominal Range   High Range
                        450 - 550     950 - 1050    1450 - 1550

			This program takes 2 optional arguments. The first is 
                        the name of a .dat file. The second is the amount 
                        to read from the file.
			Ex.) ./program2test newflowData.dat 69420
*/

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <stdio.h> //basic io stuff?
#include <stdlib.h> //Random numbers
#include <unistd.h> //read, write, open, close
#include <errno.h>
#include <string.h> //Extracting filename parameters
#include <time.h> //Random numbers

//Preprocessor constants must be defined before main
#define BUF_SIZE 4 

union dtob //printf("%d") its the d thing to convert
{
  int value;
  char bytes[4];
};

//Parameters: filename, count)
int inBytes(const char *in, int count)
{
  int inputFd, numRead, i;
  int timesince = 0;
  int times = 0;
  union dtob inBytes; //Call union in for conversion

  inputFd = open(in, O_RDONLY); //Need FD and permission only

  if (inputFd == -1) //Check to see if it opened correctly
    {
      perror("open for read");
      return -1;
    }

  for (i = 0; i < count; i++)
    {
      //AmountofStuffRead = (FD, union.whatwereading, how many to read)
      numRead = read(inputFd, inBytes.bytes, 4);
      if(numRead > 0) //While stuff is availible to be read
	{
	  if (inBytes.value < 550 && inBytes.value > 450) //450<data<550
	    {
	      printf("%d  - WARNING; LOW LINE PRESSURE---%d Entries since last alert\n", inBytes.value, timesince);
	      //printf("       %d Entries since last alert\n", timesince);
	      timesince = 1;
	      times++;
	    }
	  else if (inBytes.value <=  950 && inBytes.value >= 550) //550<=data<=950
	    {
	      printf("%d  - low pressure\n", inBytes.value);
	      timesince++;
	    }
	  else if (inBytes.value > 950 && inBytes.value < 1050) //950<data<1050
	    {
	      //The if's here are just for formatting
	      if (inBytes.value < 1000) 
		{
		  printf("%d  - nominal pressure\n", inBytes.value); //950<data<1000
		  timesince++;
		}
	      else
		{
		  printf("%d - nominal pressure\n", inBytes.value); //1000<=data<1050
		  timesince++;
		}
	    }
	  else if (inBytes.value <= 1450 && inBytes.value >= 1050) //1050<=data<=1450
	    {
	      printf("%d - high pressure\n", inBytes.value);
	      timesince++;
	    }
	  else if (inBytes.value < 1550 && inBytes.value > 1450) //1450<data<1550
	    {
	      printf("%d - WARNING; HIGH LINE PRESSURE---%d Entries since last alert\n", inBytes.value, timesince);
	      //printf("      %d Entries since last alert\n", timesince);
	      timesince = 1;
	      times++;
	    }
	}
      else
	{
	  break;
	}
    }

  printf("END SIMULATION\n");
  printf("Warnings: %d\n", times);

  close(inputFd);
  return 0;
}

//Put in the char string literal, receive allocated string.
//Passing in string literal, gotta make pointer to char value const
//Returns pointer to newly allocated string thing
char *dupString(const char *val)
{
  int len = strlen(val);
  char *outStr = (char *) calloc(len + 1, sizeof(char));
  if (outStr == NULL) //IF allocation failed and returned NULL
    {
      perror("calloc");
      exit(EXIT_FAILURE);
    }
  strcpy(outStr, val);
  return outStr;
}

int main(int argc, char *argv[])
{
  char *inFile = NULL; //FD pointer
  int count = 60; //Default values

  if (argc != 1 && argc != 2 && argc != 3)
    {
      perror("incorrect number of arguments");
      exit(EXIT_FAILURE);
    }

  if (argc == 1) //No arguments
    {
      inFile = dupString("flowData.dat");
    }
  
  else if (argc == 2) //Filename argument
    {
      inFile = dupString(argv[1]);
    }
  else if (argc == 3) //Filename and count
    {
      inFile = dupString(argv[1]);
      count = atoi(argv[2]);
      
    }

  printf("Commencing data flow from flowData.dat\n");
  if (inBytes(inFile, count) == -1) //Check to see if it worked
    {
      perror("failed to read");
      exit(EXIT_FAILURE);
    }
  
  exit(EXIT_SUCCESS);
}
