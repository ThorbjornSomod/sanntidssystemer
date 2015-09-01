#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

sem_t sem;

int running = 1;
int var1 = 0;
int var2 = 0;

void* thread1(){
	while(running){
		sem_wait(&sem);
		var1 = var1 + 1;
		var2 = var1;
		sem_post(&sem);
	}
	return NULL;
}

void* thread2(){
	int i;
	for (i = 1; i < 21; i++){
		sem_wait(&sem);
		printf("Number 1 is %i, number 2 is %i, \n", var1, var2);
		sem_post(&sem);
		usleep(100000);
	}
	running = 0; 
	return NULL;
}

int main(){

	sem_init(&sem, 0, 1);

	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread1, NULL);
	
	pthread_t thread_2;
	pthread_create(&thread_2, NULL, thread2, NULL);
	
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	
	return 0;
	
}
