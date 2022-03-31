/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:23:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/03/31 16:17:01 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_handling(int i, char *str)
{
	if(i == -1)
	{
		perror(str);
		exit(1);
	}	
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(*str);
}

char **path_finder(char **env)
{
	int i;
	char **path;
	i = 0;
	while(env[i])
	{
		if(ft_strncmp("PATH=", env[i] , 5) == 0)
		{
			path = ft_split(&env[i][5], ':');
			return (path);		
		}
		i++;
	}
	return 0;
}

void cmd_execution(char *av,char **env)
{
	char	*cmd;
	char	**argvec;
	char	**path;	
	int		i;

	path = path_finder(env);
	if(path == 0)
		error_handling(-1, "Path not found");
	argvec = ft_split(av, ' ');
	i = 0;
	while(path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, argvec[0]);
		if((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
			error_handling(execve(cmd, argvec, env), "Execve could not execute.");
		i++;
		free(cmd);
	}
	ft_free(path);
	ft_free(argvec);
	perror("Command not found.\n");
}

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		int file[2];
		int fd[2];

		pid_t pid[2];
		error_handling(pipe(fd),"Could not pipe");
		pid[0] = fork();
		error_handling(pid[0], "Could not fork");
		if(pid[0] == 0)
		{
			close(fd[0]);
			file[0] = open(av[1], O_RDONLY, 0777);
			error_handling(file[0], "File could not open");
			error_handling(dup2(fd[1], 1), "Dup2 failed");
			error_handling(dup2(file[0], 0), "Dup2 failed");
			cmd_execution(av[2], env);
		}
		pid[1] = fork();
		error_handling(pid[1], "Could not second fork");
		if(pid[1] == 0)
		{	
			close(fd[1]);
			file[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			error_handling(file[1], "File could not open");
			error_handling(dup2(file[1], 1), "Dup2 failed");
			error_handling(dup2(fd[0], 0), "Dup2 failed.");
			cmd_execution(av[3], env);
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
}