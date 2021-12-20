#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
   char buffer[L_tmpnam];
   char *ptr;


   mkstemp(buffer);
   printf("temp file name:%s\n", buffer);
   sleep(5);
   return(0);
}
