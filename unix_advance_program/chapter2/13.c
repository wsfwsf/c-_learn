#include<stdio.h>
 
int main ()
{
   FILE *fp;
   char str[] = "This is runoob.com";
 
   fp = fopen( "file.txt" , "w" );
   fwrite(str, sizeof(str) , 1, fp );
 
   fclose(fp);
  
   return(0);
}
