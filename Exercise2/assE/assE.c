#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>
#include <semaphore.h>

//pilosopher = []
//forks = []

sem_t fork1;
sem_t fork2;
sem_t fork3;
sem_t fork4;

void* phil1(){
	printf("Phil 1 starting\n");
	while(1){
		sem_wait(&fork1);
		sem_wait(&fork4);
		printf("Phil 1 eating\n");
		sleep(1);
		sem_post(&fork4);
		sem_post(&fork1);
		sleep(1);
	}
	return NULL;
}

void* phil2(){
	printf("Phil 2 starting\n");
	while(1){
		sem_wait(&fork2);
		sem_wait(&fork1);
		printf("Phil 2 eating\n");
		sleep(1);
		sem_post(&fork1);
		sem_post(&fork2);
		sleep(1);
	}
	return NULL;
}

void* phil3(){
	printf("Phil 3 starting\n");
	while(1){
		sem_wait(&fork3);
		sem_wait(&fork2);
		printf("Phil 3 eating\n");
		sleep(1);
		sem_post(&fork2);
		sem_post(&fork3);
		sleep(1);
	}
	return NULL;
}

void* phil4(){
	printf("Phil 4 starting\n");
	while(1){
		sem_wait(&fork3);
		sem_wait(&fork4);
		printf("Phil 4 eating\n");
		sleep(1);
		sem_post(&fork4);
		sem_post(&fork3);
		sleep(1);
	}
	return NULL;
}

int main(){
	sem_init(&fork1, 0, 1);
	sem_init(&fork2, 0, 1);
	sem_init(&fork3, 0, 1);
	sem_init(&fork4, 0, 1);

	pthread_t phil_1;
	pthread_create(&phil_1, NULL, phil1, NULL);
	
	pthread_t phil_2;
	pthread_create(&phil_2, NULL, phil2, NULL);
	
	pthread_t phil_3;
	pthread_create(&phil_3, NULL, phil3, NULL);

	pthread_t phil_4;
	pthread_create(&phil_4, NULL, phil4, NULL);

	pthread_join(phil_1, NULL);
	pthread_join(phil_2, NULL);
	pthread_join(phil_3, NULL);
	pthread_join(phil_4, NULL);

	return 0;
}
