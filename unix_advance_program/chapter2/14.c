#include<stdio.h>
 
int main ()
{
   FILE *fp;
   char str[] = "This is runoob.com";
 
   fp = fopen( "file.txt" , "w" );
 
   printf("ftel:%ld\n",ftell(fp));

   if(fseek(fp,0,SEEK_END)==0){
	printf("ftel:%ld\n",ftell(fp));
   }
	  
   return(0);
}
