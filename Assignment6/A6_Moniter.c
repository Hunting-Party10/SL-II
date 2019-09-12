#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALLIZER;

int* init(int n)
{
	int *temp = malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i)
		temp[i] = 0;
	return temp;	 
}

void *simulateDPP(void *args)
{
	int n = *(int *)args;
	int *chopsticks;
	chopsticks = init(n);
	return;
}

int main(int argc, char const *argv[])
{
	int n;
	printf("Enter Number of Philosophers\n");
	scanf("%d".&n);
	int dpp_id;
	printf("Starting Simulation of Dining Philosophers Problem\n");
	pthread_create(&dpp_id,NULL,simulateDPP,n);
	pthread_join(dpp_id,NULL);
	printf("Simulation Complete\n");
	return 0;

}