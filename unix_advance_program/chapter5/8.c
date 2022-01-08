#include "apue.h"
#include <setjmp.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo);
unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void){
	unsigned int unsleep;
	if(signal(SIGINT,sig_int)==SIG_ERR)
		err_sys("signal SIGINT error");
	//unsleep = sleep2(5);
	unsleep=sleep(5);
	printf("sleep2 returned :%u\n",unsleep);
	return 0;
}

static void sig_int(int signo){
	int i,j;
	volatile int k;
	printf("\n sig_int startint \n");
	for(i=0;i<300000;i++)
		for(j=0;j<4000;j++)
			k+= i*j;
	printf("sig_int finished \n");
}

unsigned int sleep2(unsigned int nsecs){
        if(signal(SIGALRM,sig_alrm)==SIG_ERR)
                return nsecs;
        if(setjmp(env_alrm)==0){
                alarm(nsecs);
                pause();
        }
        return alarm(0);
}

static void sig_alrm(int signo){
        longjmp(env_alrm,1);
}
