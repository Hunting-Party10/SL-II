#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
 
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#include"shm_com.h"

int main(int argc, char const *argv[])
{
	int running =1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_buff;
	int shmid;

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *) - 1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n",(int)shared_memory);
	shared_buff = (struct shared_use_st *)shared_memory;
	/* Using our predefined structure as a typecast to the memory pointer*/

	//Marking that the shared buffer has not been written yet
	shared_buff->written_by = 0;

	while(running)
	{
		if(shared_buff->written_by == 0)
		{
			printf("Enter a String :");
			scanf("%s",shared_buff->text_space);
			if (strncmp(shared_buff->text_space,"end",3) == 0)
			{
				printf("Client Exiting\n");
				running = 0;
			}
			shared_buff->written_by =1;
		}
	}

	return 0;
}