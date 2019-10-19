#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


sem_t writer_semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int read_limit = 0,readcnt = 0;

void *readfile(void *args)
{
	printf("Waiting to check condition\n");
	pthread_mutex_lock(&mutex);
	if (readcnt == 0)
	{
		readcnt++;
		pthread_mutex_unlock(&mutex);
		printf("No readers Present,trying to lock semaphore\n");
		sem_wait(&writer_semaphore);
	}
	else
	{
		readcnt++;
		pthread_mutex_unlock(&mutex);
	}
	printf("Condition Checked\nReading.\n");

	printf("trying to decrement reader count\n");
	pthread_mutex_lock(&mutex);
	readcnt--;
	printf("Reader count decremented\n");


	if (readcnt == 0)
	{
		printf("No readers detected, Releasing all locks\n");
		sem_post(&writer_semaphore);
		printf("Locks Released\n");
	}
	pthread_mutex_unlock(&mutex);
}

void *writefile(void *args)
{
	printf("Writer waiting\n");
	sem_wait(&writer_semaphore);
	printf("Writing\n");
	sem_post(&writer_semaphore);
	printf("Writer exiting\n");
}

void *reader(void *args)
{
	int count = 0;
	pthread_t *thread_id = malloc(sizeof(pthread_t) * *(int *)args);
	for (int i = 0; i < *(int *)args; ++i)
		thread_id[i] = -1;
	while(read_limit <= 10)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i){
				if (thread_id[i] == -1){
					printf("Reader Created\n");
					pthread_create((thread_id +i),NULL,&readfile,NULL);

				}
			}
		}
		for (int i = 0; i < *(int *)args; ++i){
			if (thread_id[i] != -1){
				pthread_join(*(thread_id +i),NULL);
				read_limit++;
				thread_id[i] = -1;
			}
		}
	}
}

void *writer(void * args)
{
	int count = 0;
	pthread_t *thread_id = malloc(sizeof(pthread_t) * *(int *)args);
	for (int i = 0; i < *(int *)args; ++i)
		thread_id[i] = -1;
	while(read_limit <= 10)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i){
				if (thread_id[i] == -1){
					printf("Writer Created\n");
					pthread_create((thread_id +i),NULL,&writefile,NULL);
				}
			}
		}
		for (int i = 0; i < *(int *)args; ++i){
			if (thread_id[i] != -1){
				pthread_join(*(thread_id +i),NULL);
				thread_id[i] = -1;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int r,w;
	printf("Enter Number of Reader:");
	scanf("%d",&r); 
	printf("Enter Number of Writer:");
	scanf("%d",&w);
	pthread_t c_id,p_id;
	sem_init(&writer_semaphore,0,1);
	pthread_create(&p_id,NULL,&reader,&r);
	pthread_create(&c_id,NULL,&writer,&w);
	pthread_join(p_id,NULL);
	pthread_join(c_id,NULL);
	return 0;
}