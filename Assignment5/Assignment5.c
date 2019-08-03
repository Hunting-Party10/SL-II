#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int read_limit = 0,readcnt = 0;

void *readfile(void *args)
{
	if (readcnt == 0){
		printf("No readers currently,trying to lock mutex\n\n");
		while(pthread_mutex_lock(&mutex) != 0);
	}
	readcnt++;
	//read
	printf("Reading..\n\n");
	sleep(3);
	readcnt--;
	if(readcnt == 0){
		pthread_mutex_unlock(&mutex);
		printf("No readers detected,Unlocking Mutex\n");
		return(void *)0;
	}
	else{
		printf("Some readers are reading,Exiting without unlocking mutex\n");
		pthread_exit(NULL);
		
	}
}

void *writefile(void *args)
{
	while(pthread_mutex_lock(&mutex) != 0);
	//write
	printf("Writing\n");
	sleep(5);
	printf("Writing Complete Unlocking Mutex\n");
	pthread_mutex_unlock(&mutex);
	return(void *) 0;
}

void *reader(void *args)
{
	int count = 0;
	pthread_t *thread_id = malloc(sizeof(pthread_t) * *(int *)args);
	for (int i = 0; i < *(int *)args; ++i)
		thread_id[i] = -1;
	while(read_limit <= 50)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i){
				if (thread_id[i] == -1){
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
	while(read_limit <= 50)
	{
		if (count < *(int *)args)
		{
			for (int i = 0; i < *(int *)args; ++i){
				if (thread_id[i] == -1){
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
	pthread_create(&p_id,NULL,&reader,&r);
	pthread_create(&c_id,NULL,&writer,&w);
	pthread_join(p_id,NULL);
	pthread_join(c_id,NULL);
	return 0;
}