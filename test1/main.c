/*Name: Colton Earls
  NetID: cce114
  Compiler: gcc
  Program Description: Program for test1

  Problem 1  - DONE
  Problem 2  - DONE
  Problem 3  - DONE
  Problem 4  - 50%
  Problem 5  - 0%
  Problem 6a - DONE
  Problem 6b - 50%
  Problem 6c - DONE
  Problem 6d - DONE
  Problem 7  - DONE
  Problem 8  - DONE
  Problem 9  - 
  Problem 10 - 
  Problem 11 - 
  Problem 12 - DONE
*/

#include <stdio.h> //Problem 1 DONE
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <string.h> //Eh. Why not

#define BUF_SIZE 1024

static int timed;

int myPrint(const char *str) //Problem 2 DONE
{
  int len = strlen(str);
  if (write(1, str, len) == 0)
    {
      return 1;
    }
  return 0;
}

myPrintInt(const int val) //Problem 3 DONE
{
  char buffer[1024];
  sprintf(buffer, "%i", val); //Formats int in to buffer
  if (write(1, buffer, strlen(buffer)) == 0)
    {
      return 1;
    }
  return 0;
}

/* implement the signal hadler below ...
 * use the provided prototype
 * It must handle two signals, SIGINT and SIGALRM
 */
void signalHandler(int sig) //Problem 4
{
  if (sig == SIGINT) //Handler for keyboard interrupts
    {
      write(1, "EXIT: Are you sure you want to exit? (Y/n): ", 44);
    }
  if (sig == SIGALRM) //What to do when the alarm signal happens
    {
      write(1, "Time is up! Next question:\n", 28);
    }
}

/* This function reads a line of text from a file
 * we are simulating another functions behavior here ..
 * Return a 0 if no characters were read, return a 1 otherwise
 */
int readLine(int fd, char *line) //Problem 5
{
  if (
}

/* This function reads a question answer pairing
 * from the provided pair of file descriptors
 * It returns 0 if the files are empty
 * and 1 if if successfully reads the pairing
 */
int readQA(int questFd, int ansFd, char *quest, char *ans)
{
  if (readLine(questFd,quest) == 0) return 0; 
  if (readLine(ansFd, ans) == 0) return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  int numRead = 0; //Amount of stuff to read
  int numWrite = 0; //Amount of stuff to write
  int question = 1;
  int correct = 0;
  char buf[BUF_SIZE];
  char quest[BUF_SIZE];
  char ans[BUF_SIZE];
  int questFd, ansFd;

  //Problem 6a
  struct sigaction handler; //Sig action declaration
  struct itimerval tvOn; //30 second timeer
  struct itimerval tvOff; //0 second disable timer


  //Problem 6b
  sigemptyset(&sa.sa_mask); //Empty the mask
  handler.sa_handler = signalHandler; //Assign the signal handler
  handler.sa_flags = 0; //Assign the handling flags

  //Problem 6c 
  tvOn.it_interval.tv_sec = 0; //No interval for active timer
  tvOn.it_interval.tv_userc = 0;
  tvOn.it_value.tv_sec = 30;
  tvOn.it_value.tv_usec = 0; //Time until it triggers the first time

  //Problem 6d
  tvOff.it_interval.tv_sec = 0;
  tvOff.it_interval.tv_usec = 0;
  tvOff.it_value.tv_sec = 0; //Disable timer set to 0
  tvOff.it_value.tv_usec = 0;

  //Problem 7
  if (sigaction(SIGINT,&handler, NULL) == -1)
    {
      perror("sigint");
      exit(EXIT_FAILURE);
    }
  if (sigaction(SIGALRM,&handler, NULL) == -1)
    {
      perror("sigalarm");
      exit(EXIT_FAILURE);
    }
  
  //Problem 8 DONE
  questFd = open("quest.txt", O_RDONLY);
  ansFd = open("ans.txt", O_RDONLY);
  if (questFd == -1)
    {
      perror("failed to open quest.txt");
      exit(EXIT_FAILURE);
    }
  if (ansFd == -1)
    {
      perror("failed to open ans.txt");
      exit(EXIT_FAILURE);
    }
    
   /* this loop handles the Q/A stuff 
    * I have included some of it to make you life simpler 
    * I have also left some commnents to assist you as well 
    *
    * read the first question, answer pairing prior to entering the loop
    */
    readQA(questFd, ansFd, quest, ans);
  while (1)
    {
      /* output the current question */
      myPrint("#");
      myPrintInt(question);
      myPrint(" ");
      myPrint(quest);
      myPrint("? ");
      /* we will set the timedout flag to 0, since it hasn't yet */
      timed = 0;

      //Starts the 30 second timer
      if (setitimer((ITIMER_REAL, &tvOn, NULL) == -1)
	{
	  perror("setitimer");
	  exit(EXIT_FAILURE);
	}
      
 /*  Problem 9 */
      /* read in the user's response, this is systems programming so don't use 
       * scanf */
 /* Problem 10 */
      /* test to see if the user responded and if an error has occurred 
       * an error can actually occur as part of the functionality of this program 
       * both SIGINT and SIGALRM will cause the read call to return a -1 
       * this can be recognized by testing for a specific error number ...  
       * The error is known as interrupted systems call 
       * Should this be the case, do the following .... 
       * If the read call was interrupted and the timedout flag isn't set 
       * just continue 
       * if the timedout flag was set, inform the user that time is up 
       * then go to the next question
       */
      if (numRead == 0) break;
      if (numRead == -1)
{
  if (errno == EINTR)
    {
      if (timed)
{
  myPrint("\nTime's up, next question\n");
  if (readQA(questFd, ansFd, quest, ans) == 0) break;
  question++;
}
      continue;
    }
  perror("read");
  exit(EXIT_FAILURE);
}
      /* disable the timer here */
	
	
      /* we will convert the buf being read in to a c-string by tacking on a 0 */
buf[numRead-1] = 0;
/* check the answer */
if (strcmp(buf,ans) == 0)
  {
    correct++;
    myPrint("\ncorrect\n");
  } else
  {
    myPrint(ans);
    myPrint("\nwrong\n");
  }
/* read the next question .. break if there are no more questions */
if (readQA(questFd, ansFd, quest, ans) == 0) break;
question++;
    }
  myPrint("final score is ");
  myPrintInt(correct);
  myPrint(" out of ");
  myPrintInt(question);
  
  close(questFd);
  close(ansFd);
}
