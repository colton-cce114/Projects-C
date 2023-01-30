#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>

/*
  THE SECOND PROGRAM
  1. Use fork to create a child process and use one of the exec functions
     to run the myRand program. You can simply use wait or waitpid for 
     this one; you don't need to write a signal handler for SIGCHLD unless
     you choose to. 
     Remember that you need to use WEXITSTATUS to convert the status 
     returned by wait to the actual value. 

  2. Open the fild dataX.dat where X is the number returned from the system. 
  
  3. Read the 60 values from the file, display them, compute the average, 
     and output the average. 

  4. Unlink the data file. 
*/
