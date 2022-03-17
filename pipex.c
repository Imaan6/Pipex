#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		int fd[2];
		pid_t pid;
		char cmd[] = "/bin/ls";
		char *argVec[] = {"ls", "-l",NULL};
		char *envVec[] = {NULL};
		if(pipe(fd) == -1)
		{
			perror("Error :(. Could not execute pipe. \n");
			return 1;
		}
		//int in = fd[0];
		//int out = fd[1];
		pid = fork();
		if(pid == -1)
		{
			perror("Error :(. Could not execute fork. \n");
			return 1;
		}
		if(pid == 0)
		{
			close(fd[1]);
			printf("I am a child process %d \n", pid);
			if(execve(cmd, &av[1], env) == -1)
			{
				perror("Error: Could not execute execve");
				exit(1);
			}
		}
		wait(NULL);
		printf("I am a parent process %d \n", pid);
		exit (1);
	}
	return 0;
}