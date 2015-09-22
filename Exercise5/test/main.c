#include "io.h"
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	io_init();
	
	io_write(1,0);
	//io_write(2,1);
	//io_write(3,1);

	printf("%i \n", io_read(1));
	int toggle = 1;
	int i;
	for(i = 0; i < 10 ; i++){
		io_write(2,toggle);
		io_write(3,toggle);
		sleep(1);
		printf("%i \n", io_read(2));
		if(toggle){
			toggle = 0;
			continue;
		}
		toggle = 1;
	}

	return 1;
}
