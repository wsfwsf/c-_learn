#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
 
void main()
{
    char str[6]="hello";
 
    pid_t pid=fork();
 
    if(pid==0)
	{
        str[0]='b';
        printf("子进程中str=%s\n",str);
        //printf("子进程中str指向的首地址:%x\n",(unsigned int)str);
    }
    else
	{
        sleep(1);
        printf("父进程中str=%s\n",str);
        //printf("父进程中str指向的首地址:%x\n",(unsigned int)str);
    }
}
