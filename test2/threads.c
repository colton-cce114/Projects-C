#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <errno.h>

/*We need to implement three threads ...
 *prints evens
 *prints odds
 *main thread
 */

int threadError(int err, char *str)
{
  if (err > 0)
    {
      errno = err;
      perror(str);
      exit(EXIT_FAILURE);
    }
  return err;
  
}

void *evenThread(void *args) //Sets up the thread
{
  int n = 0;
  struct timespec tv; //Set a timer
  pthread_t tid;

  //pthread can detach itself
  tid = pthread_self();
  threadError(pthread_detach(tid), "pthread_detach");
  
  tv.tv_sec = 1;
  tv.tv_nsec = 0;
  for (n=0; n<61; n+=2)
    {
      printf("E: %d\n", n);
      nanosleep(&tv, NULL);
    }
  pthread_exit(NULL);
}

void *oddThread(void *args)
{
  int n = 1;
  struct timespec tv;
  pthread_t tid;

  //pthread can detach itself
  tid = pthread_self();
  threadError(pthread_detach(tid), "pthread_detach");
  
  tv.tv_sec = 1;
  tv.tv_nsec = 0;
  for (n=1; n<61; n+=2)
    {
      printf("O: %d\n", n);
      nanosleep(&tv, NULL);
    }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t tid[2]; //We're making 2 threads
  int err;
  struct timespec tv;

  tv.tv_sec = 35;
  tv.tv_nsec = 0;
  
  //create the threads (attach)
  threadError(pthread_create(&tid[0], NULL, evenThread, NULL), "pthread_create");
  threadError(pthread_create(&tid[1], NULL, oddThread, NULL), "pthread_create");
  //detach the threads here (thread is independent, no return values)
  //                   terminates itself and cleans up when done
  //threadError(pthread_detach(tid[0]), "pthread_detach");
  //threadError(pthread_detach(tid[1]), "pthread_detach");
  //join the threads here (
  //threadError(pthread_join(tid[0], NULL), "pthread_join");
  //threadError(pthread_join(tid[1], NULL), "pthread_join");
  nanosleep(&tv, NULL);
}
