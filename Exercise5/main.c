#include "io.h"
#include <sys/times.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	io_init();
	
	io_write(1,1);
	io_write(2,1);
	io_write(3,1);

	printf("%i \n", io_read(1));

	sleep(3);

	return 1;
}
