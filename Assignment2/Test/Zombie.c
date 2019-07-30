#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int Zombie()
{
	printf("Main Process:%d\n",getpid());
	pid_t child = fork();
	if(child > 0)
	{
		printf("Main Process Going to Sleep:%d\n",getpid());
		sleep(30);
		return 0;
	}
	else
	{
		printf("Child Process Exiting:%d\n",getpid());
		return 0;
	}
}

int main()
{
	Zombie();
	return 0;
}
