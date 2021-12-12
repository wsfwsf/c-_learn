#include "apue.h"
#include <string.h>
int main(){
	char buf[1024];
	memset(buf,0,sizeof(buf));
	getcwd(buf,sizeof(buf));
	printf("%s\n",buf);
	return 0;
}
