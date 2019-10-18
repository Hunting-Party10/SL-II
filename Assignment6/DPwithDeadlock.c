/*
Deadlock is only possible when every Philosopher has one chopstick in hand.
This can be done by making all the philosophers pick up the left chopstick then
the right chopstick.

The problem is simulated for 5 Philosophers

due to thread slicing it may or may not result in deadlock, to endsure a deadlock
put a one second delay between picking up chopsticks 

*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define OBJECTS 5

pthread_mutex_t *chopsticks = NULL;

typedef struct Philosopher
{
	int number;
	pthread_t philosopher_id;
}Philosopher;

void init()
{
	chopsticks = malloc(OBJECTS * sizeof(pthread_mutex_t));
	for(int i = 0 ; i <OBJECTS; i++)
		pthread_mutex_init((chopsticks +i),NULL);
}

void *start(void *args)
{
	int eat_count =0;
	Philosopher *p  = args;
	//printf("This is Philosopher Number %d\n",p->number);

	while(eat_count < 5)
	{
		printf("Philosopher %d is picking up left chopstick\n",p->number);
		pthread_mutex_lock(chopsticks + p->number -1);
		//sleep(1); UN comment this to ensure a deadlock happens
		printf("Philosopher %d is picking up right chopstick\n",p->number);
		pthread_mutex_lock(chopsticks + (p->number)%OBJECTS );
		printf("Philosopher %d is eating\n",p->number);
		printf("Philosopher %d has finished\n",p->number);
		pthread_mutex_unlock(chopsticks + p->number -1);
		pthread_mutex_unlock(chopsticks + (p->number)%OBJECTS );
		eat_count++;
		printf("\n\n");
	}
	return NULL;
}

void *simulateDPP(void *args)
{
	Philosopher p[OBJECTS];
	for (int i = 0; i < OBJECTS; ++i){
		p[i].number = i+1;
		pthread_create(&p[i].philosopher_id,NULL,start,&p[i]);
	}
		

	for (int i = 0; i < OBJECTS; ++i)
		pthread_join(p[i].philosopher_id,NULL);
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