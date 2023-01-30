#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

static void signalHandler(int sig)
{
  if (sig = SIGINT) //If the signal is control c
    {
      printf("Ouch!\n");
    }
  if (sig == SIGALRM) //If the signal is an alarm
    {
      printf("Tick!\n");
    }
}

int main(int argc, char *argv[])
{
  int j;
  struct sigaction sa; //Sigaction
  struct itimerval itmr; //iTimer

  itmr.it_interval.tv_sec = 6; //Time between each alarm
  itmr.it_interval.tv_usec = 0;
  itmr.it_value.tv_sec = 3; //Time before alarm triggers
  itmr.it_value.tv_usec = 0;

  sigemptyset(&sa.sa_mask); //Empty the mask
  sa.sa_handler = signalHandler; //Set the handler for the SA
  sa.sa_flags = 0; //Set flags for the sigaction

  //type of action/ our signal handler pos./no old sig handler
  if (sigaction(SIGINT, &sa, NULL) == -1) //Action for sigint
    {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }
  if (sigaction(SIGALRM, &sa, NULL) == -1) //Action for alrm
    {
      perror("sigaction");
      exit(EXIT_FAILURE);
    }

  //type of timer/pointer to timer we use/ no old timer
  if (setitimer(ITIMER_REAL, &itmr, NULL) == -1) //Set real timer
    {
      perror("setitimer");
      exit(EXIT_FAILURE);
    }

  while (1)
    {
      //Usually use sleep here, but we have a timer
      pause(); //Waits until a signal generates
    }
}
