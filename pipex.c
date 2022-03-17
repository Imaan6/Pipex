/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:23:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/03/17 09:57:03 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
	//if (ac == 2)
	//{
		int fd[2];
		pid_t pid;
		char cmd[] = "/bin/ls";
		char **argVec = ft_split(av[1], ' ');
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
			if(execve(cmd, argVec, env) == -1)
			{
				perror("Error: Could not execute execve");
				exit(1);
			}
		}
		wait(NULL);
		printf("I am a parent process %d \n", pid);
		exit (1);
	//}
	return 0;
}
