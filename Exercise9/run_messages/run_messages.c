#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/times.h>
#include <pthread.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	char buf[100];
	int fd;
	while(1){
		//printf("RUN MESSAGES\n");
		fd = open("/net/target_one/dev/myresource", O_RDWR);
		if(fd>0){
			read(fd,buf,100);
			printf("Linje: %s\n",buf);
		}
		delay(1000);
	}
}
