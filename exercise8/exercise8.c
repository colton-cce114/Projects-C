#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char * argv[])
{
  int i, size;
  int fd;
  char arr[1024];

  if (mkfifo("FIFOthing", S_IRWXU) == -1)
    {
      if (errno != EEXIST)
	{
	  perror("mkfifo producer failed");
	  exit(EXIT_FAILURE);
	}
      
    }

  fd = open("FIFOthing", O_WRONLY);
  if (fd = -1)
  {
    perror("Failed to open fifo");
    exit(EXIT_FAILURE);
  }
  
  
  write(1, "Enter text: ", 12);
  scanf("%s", arr);
  size = strlen(arr);
  write(1, "\n", 2);
  write(1, "Sending data size...\n", 20);
  if (write(fd, &size, sizeof(int)) == -1)
    {
      perror("Failed to send size");
      exit(EXIT_FAILURE);
    }

  for (i = 0; i < strlen(arr); i++)
    {
      if (write(fd, &arr[i], sizeof(char)) == -1)
	{
	  perror("Failed to send data");
	  exit(EXIT_FAILURE);
	}
    }

  close(fd);
  exit(EXIT_SUCCESS);
}
