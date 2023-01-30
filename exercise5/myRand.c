/*
  THE FIRST PROGRAM
  1. Generate a new file named dataX.dat where X is a random number between
     0 and 255

  2. Generate 60 values between 0 and 100 and store them in the file

  3. Exit with an exit status of X
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

#define BUF_SIZE 4

union dtob
{
  int value;
  char bytes[4];
};

int outBytes()
{
  int outFd, openFlags, i, xNum;
  char *outName[1024] = {0};
  mode_t filePerms;

  union dtob outByte;

  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IWGRP | S_IRGRP | S_IROTH | S_IWOTH;

  xNum = rand() % 255; //SHOULD give rand int between 0-255
  sprintf(outName, "data%d.dat", xNum);
  
  outFd = open(out, openFlags, filePerms);

  if (outputFd == -1)
    {
      perror("Failed to open file for wite");
      exit(EXIT_FAILURE);
    }

  for (i = 0; i < cnt; i++)
    {
      outBytes.value = rand() % 100;
      if (write(outputFd, outBytes, 4) != 4)
	{
	  perror("Failed to write");
	  exit(EXIT_FAILURE);
	}
      
    }

  close(outFd);
  return 0;
}

inBytes(char *in int cnt)
{
  
}

int main()
{
  srand(time(NULL));
  outBytes();
}
