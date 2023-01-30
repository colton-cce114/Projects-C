#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int fd;
  int i, size;
  char arr[1024];

  if (mkfifo("FIFOthing", S_IRWXU) == -1)
    {
      if (errno != EEXIST)
	{
	  perror("mkfifoproducer");
	  exit(EXIT_FAILURE);
	}
      
    }
  
  fd = open("FIFOthing", O_RDONLY);
  if (fd = -1)
    {
      perror("Failed to open fifo");
      exit(EXIT_FAILURE);
    }

  write(1, "Reading data size...\n", 22);
  if (read(fd, &size, sizeof(int)) == -1)
    {
      perror("Failed to read size");
      exit(EXIT_FAILURE);
    }
  write(1, "Reading data...\n", 17);
  for (i = 0; i < size; i++)
    {
      if (read(fd, &arr[i], sizeof(char)) == -1)
	{
	  perror("Failed to read data");
	  exit(EXIT_FAILURE);
	}
	
    }
  write(1, "Data Read: ", 11);
  write(1, "\n", 2);
  close(fd);
  exit(EXIT_SUCCESS);
}
