#include<unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include<string.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#include"shm_com.h"

int main()
{
	int running =1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_buff;
	int shmid;

	//sudo random number gen 
	//srand((unsigned int)getpid());

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	/*
	shm get  tries to find a segment with the given key

	0666 is the usual access permision in linux in rwx octal format 

	IPC_CREAT is redundant but is need when creation of new segment is needed

	IPC_CREAT is used to create a new segment of given size
	If this is not used the system tries to find a segment with the given key and checks if user has access to it
	
	shmid is -1 when a segment cannot be created or accessed
	*/

	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	/*
	server program is attaching to the confirming segmenty id to perform opertations
	*/
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *) - 1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n",(int )shared_memory);


	shared_buff = (struct shared_use_st *)shared_memory;
	/* Using our predefined structure as a typecast to the memory pointer*/

	//Marking that the shared buffer has not been written yet
	shared_buff->written_by = 0;


	//Jamming the server program in infinite loop till end string is occured
	while(running){
		if (shared_buff->written_by){
			//It becomes 1 when shared memory is written b y the client program
			printf("You wrote: %s\n",shared_buff->text_space);
			sleep(rand() % 4);

			//Once string is read and printed on client the state of buffer is reset
			shared_buff->written_by = 0;
			if(strncmp(shared_buff->text_space,"end",3) == 0){
				running = 0;
			}
		}
	}


	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	if (shmctl(shmid,IPC_RMID, 0 ) == -1)
	{
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return 0;
}