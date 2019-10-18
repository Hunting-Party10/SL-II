/*This is the template for DPP it can be used for all solutions.
Write your code in start() function
*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
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
	printf("This is Philosopher Number %d\n",p->number);
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
	printf("Starting Dining Philosophers Problem\n");
	init();	
	pthread_create(&dpp_id,NULL,simulateDPP,NULL);
	pthread_join(dpp_id,NULL);
	printf("Simulation Complete\n");
	return 0;
}