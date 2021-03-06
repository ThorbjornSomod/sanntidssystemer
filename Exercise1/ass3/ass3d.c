#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/times.h>

void busy_wait_delay(int seconds) 
{ 
	int i, dummy; 
	int tps = sysconf(_SC_CLK_TCK);
	printf("%i\n", tps);
	clock_t start; 
	struct tms exec_time; 
	times(&exec_time); 
	start = exec_time.tms_utime; 
	while( (exec_time.tms_utime - start) < (seconds * tps)) 
	{ 
		for(i=0; i<1000; i++) 
		{ 
			dummy = i; 
		} 
		times(&exec_time); 
	}  
} 

void* threadOne(){
	//while(1){
	printf("Thread 1!\n");
	//sleep(5);
	busy_wait_delay(5);
	//}
}

void* threadTwo(){
	//while(1){
	printf("Thread 2!\n");
	//sleep(5);
	busy_wait_delay(5);
	//}
}

int main(){
	printf("MAIN\n");
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, threadOne, NULL);

	//sleep(2);

	pthread_t thread_2;
	pthread_create(&thread_2, NULL, threadTwo, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return 0;
}
