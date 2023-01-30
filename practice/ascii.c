#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void ASCII(int argi)
{
  printf("'%c' is the ASCII value of %d\n", (char)argi, argi);
}

int main()
{
  ASCII(98);
  ASCII(113);
}
