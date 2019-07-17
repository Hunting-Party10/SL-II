#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int Orphan()
{
	printf("Main Process:%d\n",getpid());
	pid_t child = fork();
	if(child > 0)
	{
		printf("Main Process Going to Exit:%d\n",getpid());
		return 0;
	}
	else
	{
		printf("Child Process Sleeping:%d\n",getpid());
		sleep(5);
		printf("Child Process Exiting:%d\n",getppid());
		return 0;
	}
}

int main()
{
	Orphan();
	return 0;
}
