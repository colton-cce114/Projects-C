#ifndef BINARY_SEM_H
#define BINARY_SEM_H

#include <errno.h>

extern int bsUseSemUndo; //Starts at no. Don't undo
extern int bsRetryOnEintr; //Retry on interrupt. Starts on yes

int initSemAvailable(int semld, int semNum); //Is semaphore availible
int initSemInUse(int semld, int semNum); //It's in use
int reserveSem(int semId, int semNum); //Reserve
int releaseSem(int semId, int semNum); //Release

#endif
