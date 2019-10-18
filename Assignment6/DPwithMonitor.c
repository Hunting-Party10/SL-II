/*

To prevent starvation as well we must use a Monitor based solution.
Monitor simply means someone who can keep track of all the philosophers
In our case we will be using a superficial queue.

Conditional variables will act as monitor fro each philosopher will ensure no deadlock and starvation

*/


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#define OBJECTS 5

pthread_mutex_t *lock = NULL;
pthread_cond_t *self;
double avg_waiting[OBJECTS];

enum {thinking, hungry, eating} state [OBJECTS];

typedef struct Philosopher
{
	int number;
	pthread_t philosopher_id;
}Philosopher;



void init()
{
	self = malloc(OBJECTS * sizeof(pthread_cond_t));
	lock = malloc(sizeof(pthread_mutex_t));
	for(int i = 0 ; i <OBJECTS; i++){
		avg_waiting[i] = 0.0;
		pthread_cond_init ( &self [ i ], NULL );
	}
	pthread_mutex_init(lock,NULL);
}

void test(int id)
{
	pthread_mutex_lock(lock);
	if ((state[(id - 1)% OBJECTS]  != eating ) && (state[(id + 1)% OBJECTS] != eating) && (state[id] == hungry))
	{
			state[id] = eating ;
			pthread_cond_signal((self + id));
	}
	pthread_mutex_unlock(lock);
}

void put_down_forks(int id)
{
	pthread_mutex_lock(lock);
	state[id] = thinking;
	pthread_mutex_unlock(lock);
	test((id + 1)%5);
	test (id - 1);
}

void pickup_forks(int id)
{
	pthread_mutex_lock(lock);
	state[id] = hungry;
	pthread_mutex_unlock(lock);

	test(id);

	pthread_mutex_lock(lock);
	if (state[id] != eating)
	{
		pthread_cond_wait(&self[id],lock);
	}
	pthread_mutex_unlock(lock);
}




void *start(void *args)
{
	Philosopher *p  = args;
	int eat_count = 0;
	time_t start,end;
	double total_waiting_time = 0.0,time_of_wait;
	while(eat_count < 5){
		
		int rand_time = ( rand())%2 + 1;							
		printf ( "Philospher %d is Thinking for %d seconds. \n", p->number, rand_time );
		sleep ( rand_time );

		time(&start);
		pickup_forks(p->number -1);
		time(&end);
		time_of_wait = difftime ( end, start);	
		int rnd_time = ( rand())%2 + 1;								
		sleep ( rnd_time );
		printf ( "Philospher %d eating for %d seconds. \n", p->number, rnd_time );
		
		put_down_forks (p->number -1);
		total_waiting_time += time_of_wait;
		eat_count ++;
	}
	avg_waiting[p->number -1] = total_waiting_time/ 5.0;
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


	for (int i = 0; i < OBJECTS; ++i)
		printf("For Philosopher %d , Avg Waiting time is = %ld\n",p[i].number,avg_waiting[i]);

	return NULL;
}



int main(int argc, char const *argv[])
{
	pthread_t dpp_id;
	printf("Starting Dining Philosophers Problem\n\n");
	init();	
	pthread_create(&dpp_id,NULL,simulateDPP,NULL);
	pthread_join(dpp_id,NULL);
	printf("Simulation Complete\n");
	return 0;
}