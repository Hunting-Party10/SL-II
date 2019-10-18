/*
This is the asymmetric solution to DPP
There are several different approches to this solution
The approch used here is 
1) All Odd Philosophers will pick the left chopstick first
2) All Even Philosophers will pick up right chopstick first

To show starvation we use the time module but due to uneven thread slicing we cannot
confirm its accuracy 

But this Solution does lead to starvation

Output for me was
For Philosopher 1 , Avg Waiting time is = 0
For Philosopher 2 , Avg Waiting time is = 1
For Philosopher 3 , Avg Waiting time is = 2
For Philosopher 4 , Avg Waiting time is = 3
For Philosopher 5 , Avg Waiting time is = 4


*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define OBJECTS 5

pthread_mutex_t *chopsticks = NULL;

typedef struct Philosopher
{
	int number;
	pthread_t philosopher_id;
	float avg_waiting;
}Philosopher;

void init()
{
	chopsticks = malloc(OBJECTS * sizeof(pthread_mutex_t));
	for(int i = 0 ; i <OBJECTS; i++)
		pthread_mutex_init((chopsticks +i),NULL);
}

void *start(void *args)
{
	Philosopher *p  = args;
	time_t start,end;
	int eat_count = 0;
	//printf("This is Philosopher Number %d\n",p->number);
	while(eat_count < 5){
		start = time(NULL);
		if((p->number) %2 == 0)
		{
			printf("Philosopher %d is picking up right chopstick\n",p->number);
			pthread_mutex_lock(chopsticks + (p->number)%OBJECTS );
			printf("Philosopher %d is picking up left chopstick\n",p->number);
			pthread_mutex_lock(chopsticks + p->number -1);
		}
		else
		{
			printf("Philosopher %d is picking up left chopstick\n",p->number);
			pthread_mutex_lock(chopsticks + p->number -1);
			printf("Philosopher %d is picking up right chopstick\n",p->number);
			pthread_mutex_lock(chopsticks + (p->number)%OBJECTS );
		}
		end = time(NULL);
		printf("Philosopher %d is eating\n",p->number);
		printf("Philosopher %d has finished\n",p->number);
		pthread_mutex_unlock(chopsticks + p->number -1);
		pthread_mutex_unlock(chopsticks + (p->number)%OBJECTS );
		sleep(1);
		p->avg_waiting += end - start;
		eat_count++;
	}
	p->avg_waiting = p->avg_waiting / eat_count;
	return NULL;
}

void *simulateDPP(void *args)
{
	Philosopher p[OBJECTS];
	for (int i = 0; i < OBJECTS; ++i){
		p[i].number = i+1;
		p[i].avg_waiting  = 0;
		pthread_create(&p[i].philosopher_id,NULL,start,&p[i]);
	}
		

	for (int i = 0; i < OBJECTS; ++i)
		pthread_join(p[i].philosopher_id,NULL);
	for (int i = 0; i < OBJECTS; ++i)
		printf("For Philosopher %d , Avg Waiting time is = %d\n",p[i].number,p[i].avg_waiting);

	return NULL;
}



int main(int argc, char const *argv[])
{
	pthread_t dpp_id;
	printf("Starting Dining Philosophers Problem\nThis Solution is prone to deadlock\n\n");
	init();	
	pthread_create(&dpp_id,NULL,simulateDPP,NULL);
	pthread_join(dpp_id,NULL);
	printf("Simulation Complete\n");
	return 0;
}