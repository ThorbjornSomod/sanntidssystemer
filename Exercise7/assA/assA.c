#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sched.h>
#include <pthread.h>
#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>
#include <rtdk.h>
#include <sys/io.h>

RT_SEM semaphore;

void taskone(){
	rt_sem_p(&semaphore, TM_INFINITE);
	printf("Task 1 running!\n");
}

void tasktwo(){
	rt_sem_p(&semaphore, TM_INFINITE);
	printf("Task 2 running!\n");
}

int main(){

	mlockall(MCL_CURRENT|MCL_FUTURE);

	rt_sem_create(&semaphore, "sem", 0, S_PRIO);

	RT_TASK task1, task2;

	rt_task_create(&task1, "task1", 0, 1, T_CPU(1)|T_JOINABLE);
	rt_task_create(&task2, "task2", 0, 2, T_CPU(1)|T_JOINABLE);

	rt_task_shadow(NULL, "main", 4, T_CPU(1)|T_JOINABLE);

	rt_task_start(&task1, &taskone, (void*) 0);
	rt_task_start(&task2, &tasktwo, (void*) 0);

	usleep(100000);

	rt_sem_broadcast(&semaphore);

	usleep(100000);

	rt_sem_delete(&semaphore);


	return 0;
}
