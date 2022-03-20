/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:23:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/03/20 17:26:51 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av, char **env)
{
	//if (ac == 2)
	//{
		int fd[2];
		pid_t pid[2];
		char *cmd;
		char **path = ft_split(&env[6][5] , ':');
		int i;
		char **argVec = ft_split(av[2], ' ');
		if(pipe(fd) == -1)
		{
			perror("Error :(. Could not execute pipe. \n");
			return 1;
		}
		int in = 0;
		int out = 1;
		int file;
		file = open("infile.txt", O_RDONLY | O_CREAT, 0777);
		if(file == -1)
		{
			perror("Could not open the outfile");
			exit(1);
		}
		pid[0] = fork();
		if(pid[0] == -1)
		{
			perror("Error :(. Could not execute fork. \n");
			return 1;
		}
		if(pid[0] == 0)
		{
			if(dup2(fd[1], 1) == -1)
			{
				perror("dup2 for sending output failed.");
				exit(1);
			}
			//close(1);
			if(dup2(file, 0) == -1)
			{
				perror("dup2 for getting input failed.");
				exit(1);
			}
			close(fd[0]);
			i = 0;
			while(path[i])
			{
				cmd = ft_strjoin(path[i], "/");
				cmd = ft_strjoin(cmd, argVec[0]);
				if((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
				{
					execve(cmd, argVec, env);
					close(file);
					close(fd[0]);
					perror("Error: Could not execute execve");
					exit(1);
				}
				i++;
			}
			printf("command does not exist \n");
			printf("I am a child process %d \n", pid);
		}
		close(fd[1]);
		wait(NULL);
		char** argVeco = ft_split(av[3], ' ');
		printf("I am a parent process %d \n", pid);
		int file1;
		file1 = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if(file1 == -1)
		{
			perror("Could not open the outfile");
			exit(1);
		}
		// close(fd[1]);
		if(dup2(file1, 1) == -1)
		{
			perror("dup2 for sending input failed.");
			exit(1);
		}
		
		if(dup2(fd[0], 0) == -1)
		{
			perror("dup2 for getting output failed.");
			exit(1);
		}
		// 	//close(0);
			// close(fd[0]);
			i = 0;
			while(path[i])
			{
				cmd = ft_strjoin(path[i], "/");
				cmd = ft_strjoin(cmd, argVeco[0]);
				if((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
				{
					printf("test\n");
					if(execve(cmd, argVeco, env) == -1)
					{
						perror("Error: Could not execute execve");
						exit(1);
					}	
				}
				i++;
			}
			close(file1);
			printf("command does not exist \n");
			printf("I am a child process %d \n", pid);
		exit (1);
	//}
	return 0;
}
