#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define thinking rand()%10
#define eating rand()%5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALLIZER;
int *chopsticks;
int max;

int* init(int n)
{
	int *temp = malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		temp[i] = 0;
	return temp;	 
}

void *start(void * args)
{
	int n = *(int *)args;
	int *count = malloc(sizeof(int));
	*count = 0; 
	while(count<5)
	{
		printf("Philosopher %d is thinking\n\n",n );
		thinkng;
		printf("Philosopher %d is waiting for left chopstick\n",n);
		while(chopsticks[(n+1)%max] != 1);

		printf("Philosopher %d has picked up left chopstick\n\n",n );
		printf("Philosopher %d is waiting for right chopstick\n",n);
		while(chopsticks[n] != 1);


		printf("Philosopher %d has picked up right chopstick\n\nEating now\n",n );
		eating;
		printf("Eating Complete\n");
		count++:
	}
}

void *simulateDPP(void *args)
{
	int n = *(int *)args;
	int philosopher_id[n];
	for (int i = 0; i < n; ++i)
		pthread_create(&philosopher_id[i],NULL,start,i);
	for (int i = 0; i < n; ++i)
		pthread_join(philosopher_id[i],NULL);
	return;
}

int main(int argc, char const *argv[])
{
	int n;
	printf("Enter Number of Philosophers\n");
	scanf("%d",&n);
	max =n;
	chopsticks = init(n);
	int dpp_id;
	printf("Starting Simulation of Dining Philosophers Problem Symmetric Solution\n");
	pthread_create(&dpp_id,NULL,simulateDPP,n);
	pthread_join(dpp_id,NULL);
	printf("Simulation Complete\n");
	return 0;

}
