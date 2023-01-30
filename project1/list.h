#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Node
{
  char buf[1024];
  int len;
  struct Node *next;
  struct Node *prev;
};

struct LinkedList
{
  struct Node *head;
  struct Node *tail;
};

struct LinkedList *makeList();
void append(struct LinkedList *l, char buf
