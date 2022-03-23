/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:23:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/03/23 18:02:10 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void cmd_execution(char *av,char **env)
{
	char *cmd;
	char **argVec;
	char **path;
	path = ft_split(&env[6][5] , ':');
	argVec = ft_split(av, ' ');
	int i;
	i = 0;
	while(path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, argVec[0]);
		if((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
		{
			execve(cmd, argVec, env);
			//close(file);
			//close(fd[0]);
			//close(fd[1]);
			perror("Error: Could not execute execve");
			exit(1);
		}
		else
			printf("Command not found.\n");
		i++;
	}
}

void error_handling(int i)
{
	if(i == -1)
	{
		perror("Error, action failed.");
		exit(1);
	}	
}

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		int file[2];
		int fd[2];
		pid_t pid[2];
		error_handling(pipe(fd));
		pid[0] = fork();
		error_handling(pid[0] == -1);
		if(pid[0] == 0)
		{
			file[0] = open(av[1], O_RDONLY | O_CREAT, 0777);
			error_handling(file[0]);
			error_handling(dup2(fd[1], 1));
			error_handling(dup2(file[0], 0));
			cmd_execution(av[2], env);
		}
		pid[1] = fork();
		error_handling(pid[1] == -1);
		if(pid[1] == 0)
		{
			close(fd[1]);
			file[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			error_handling(file[1]);
			error_handling(dup2(file[1], 1));
			error_handling(dup2(fd[0], 0));
			cmd_execution(av[3], env);
		}
	}
}