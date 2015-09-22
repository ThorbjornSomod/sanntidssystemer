#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/times.h>
#include <sched.h>

void timespec_add_us(struct timespec *t, long us) 
{ 
    // add microseconds to timespecs nanosecond counter 
    t->tv_nsec += us*1000; 
    // if wrapping nanosecond counter, increment second counter 
    if (t->tv_nsec > 1000000000) 
	{ 
		t->tv_nsec = t->tv_nsec - 1000000000; 
		t->tv_sec += 1; 
	} 
} 

int set_cpu(int cpu_number) 
{ 
    // setting cpu set to the selected cpu 
	cpu_set_t cpu; 
	CPU_ZERO(&cpu); 
	CPU_SET(cpu_number, &cpu); 
    // set cpu set to current thread and return 
    return pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu); 
}

void* a(){
	set_cpu(1);
	io_write(1,0);

	struct timespec next;

	while(1){
		if(io_read(1)==0){
			io_write(1,1);
			usleep(5);
			io_write(1,0);
		}
		clock_gettime(CLOCK_REALTIME, &next);
		timespec_add_us(&next, 1000);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
	}
}

void* b(){
	set_cpu(1);
	io_write(2,0);

	struct timespec next;
	
	while(1){
		if(io_read(2)==0){
			io_write(2,1);
			usleep(5);
			io_write(2,0);
		}
		clock_gettime(CLOCK_REALTIME, &next);
		timespec_add_us(&next, 10);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
	}
}

void* c(){
	set_cpu(1);
	io_write(3,0);

	struct timespec next;

	while(1){
		if(io_read(3)==0){
			io_write(3,1);
			usleep(5);
			io_write(3,0);
		}
		clock_gettime(CLOCK_REALTIME, &next);
		timespec_add_us(&next, 10);
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next, NULL);
	}
}

void* disturbance(){
	set_cpu(1);
	while(1){}
}


int main(){
	io_init();	

	printf("Starting\n");

	pthread_t thread_A;
	pthread_create(&thread_A, NULL, a, NULL);
	
	pthread_t thread_B;
	pthread_create(&thread_B, NULL, b, NULL);
	
	pthread_t thread_C;
	pthread_create(&thread_C, NULL, c, NULL);

	pthread_t d1;
	pthread_create(&d1, NULL, disturbance, NULL);
	pthread_t d2;
	pthread_create(&d2, NULL, disturbance, NULL);
	pthread_t d3;
	pthread_create(&d3, NULL, disturbance, NULL);
	pthread_t d4;
	pthread_create(&d4, NULL, disturbance, NULL);
	pthread_t d5;
	pthread_create(&d5, NULL, disturbance, NULL);
	pthread_t d6;
	pthread_create(&d6, NULL, disturbance, NULL);
	pthread_t d7;
	pthread_create(&d7, NULL, disturbance, NULL);
	pthread_t d8;
	pthread_create(&d8, NULL, disturbance, NULL);
	pthread_t d9;
	pthread_create(&d9, NULL, disturbance, NULL);
	pthread_t d10;
	pthread_create(&d10, NULL, disturbance, NULL);


	pthread_join(thread_A, NULL);
	pthread_join(thread_B, NULL);
	pthread_join(thread_C, NULL);
	
	pthread_join(d1, NULL);
	pthread_join(d2, NULL);
	pthread_join(d3, NULL);
	pthread_join(d4, NULL);
	pthread_join(d5, NULL);
	pthread_join(d6, NULL);
	pthread_join(d7, NULL);
	pthread_join(d8, NULL);
	pthread_join(d9, NULL);
	pthread_join(d10, NULL);

	return 0;
}
