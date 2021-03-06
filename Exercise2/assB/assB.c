#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/times.h>

int global_counter = 0;

void* thread(){
	int local_counter = 0;
	
	int i;
	for(i = 0 ; i < 500 ; i++){
		global_counter += 1;
		local_counter += 1;
		//sleep(1);
	}
	
	printf("Local: %i\n", local_counter);
	return NULL;
}

int main(){
	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread, NULL);
	
	pthread_t thread_2;
	pthread_create(&thread_2, NULL, thread, NULL);
	
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	
	printf("Global: %i\n", global_counter);
	
	return 0;
}
