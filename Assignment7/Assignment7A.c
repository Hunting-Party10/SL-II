#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	int fd1[2],fd2[2];
	char name[20];
	printf("Enter file name:");
	scanf("%s",name);
	int status1 = pipe(fd1);
	if (status1 == -1)
	{
		printf("Error in creating pipe\n");
		return 0;
	}
	int status2 = pipe(fd2);
	if (status2 == -1)
	{
		printf("Error in creating pipe\n");
		return 0;
	}

	pid_t p;
	p = fork();
	if (p<0)
	{
		printf("Fork Error\n");
		return 0;
	}
	if (p == 0)
	{
		close(fd1[1]);
		char filename[20];
		read(fd1[0],filename, 21);
		close(fd1[0]);
		char contents[100] ;
		memset(contents, '\0',100*sizeof(char));
		FILE *f;
		f = fopen(filename,"r");
		int i = 0;
		while(!feof(f))
			contents[i++] = fgetc(f);
		close(fd2[0]);
		write(fd2[1],contents,strlen(contents));
		close(fd2[1]);
	}
	else
	{
		close(fd1[0]);
		write(fd1[1],name,strlen(name));
		close(fd1[0]);
		wait(NULL);
		char filecontents[100];
		close(fd2[1]);
		read(fd2[0],filecontents,101);
		printf("%s",filecontents );
		printf("Done\n");
	}
	return 0;
}