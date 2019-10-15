#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	char buff[20];
	int pipe_id = mkfifo("coms", 0777);
	if (pipe_id == 0) printf("Fifo Created\n");

	pipe_id = open("coms", O_WRONLY);
	printf("Write a messge :");
	scanf("%s",buff);

	if (res != -1) (void)close(res);
	exit(EXIT_SUCCESS);
	return 0;
}