#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

sem_t sem;

void* thread1(){
	sem_wait(&sem);
	printf("Thread 1 entered\n");
	sleep(1);
	printf("Thread 1 exit\n");
	sem_post(&sem);
	
	return NULL;
}

void* thread2(){
	sem_wait(&sem);
	printf("Thread 2 entered\n");
	sleep(1);
	printf("Thread 2 exit\n");
	sem_post(&sem);
	
	return NULL;
}

void* thread3(){
	sem_wait(&sem);
	printf("Thread 3 entered\n");
	sleep(1);
	printf("Thread 3 exit\n");
	sem_post(&sem);
	
	return NULL;
}

void* thread4(){
	sem_wait(&sem);
	printf("Thread 4 entered\n");
	sleep(1);
	printf("Thread 4 exit\n");
	sem_post(&sem);
	
	return NULL;
}

void* thread5(){
	sem_wait(&sem);
	printf("Thread 5 entered\n");
	sleep(1);
	printf("Thread 5 exit\n");
	sem_post(&sem);
	
	return NULL;
}

int main(){

	sem_init(&sem, 0, 3);

	pthread_t thread_1;
	pthread_create(&thread_1, NULL, thread1, NULL);
	
	pthread_t thread_2;
	pthread_create(&thread_2, NULL, thread2, NULL);
	
	pthread_t thread_3;
	pthread_create(&thread_3, NULL, thread3, NULL);
	
	pthread_t thread_4;
	pthread_create(&thread_4, NULL, thread4, NULL);
	
	pthread_t thread_5;
	pthread_create(&thread_5, NULL, thread5, NULL);
	
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
	pthread_join(thread_4, NULL);
	pthread_join(thread_5, NULL);
	
	return 0;
	
}



