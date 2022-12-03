/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 08:23:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/04/01 20:17:14 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_finder(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(&env[i][5], ':');
			return (path);
		}
		i++;
	}
	return (0);
}

void	cmd_execution(char *av, char **env)
{
	char	*cmd;
	char	**argvec;
	char	**path;	
	int		i;

	path = path_finder(env);
	if (!path)
		error_handling(-1, "Path not found");
	argvec = ft_split(av, ' ');
	if (!argvec)
		error_handling(-1, "Malloc error");
	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, argvec[0]);
		if ((access(cmd, F_OK) == 0) && (access(cmd, X_OK) == 0))
			error_handling(execve(cmd, argvec, env), "Execve error");
		i++;
		free(cmd);
	}
	ft_free(path);
	ft_free(argvec);
	error_handling2(-1, 127);
}

void	child_p1(int *fd, char **env, char *av, char *txt)
{
	int	file;

	close(fd[0]);
	file = open(txt, O_RDONLY, 0777);
	error_handling(file, "File could not open");
	error_handling(dup2(fd[1], 1), "Dup2 failed");
	error_handling(dup2(file, 0), "Dup2 failed");
	cmd_execution(av, env);
}

void	child_p2(int *fd, char **env, char *av, char *txt)
{
	int	file;

	close(fd[1]);
	file = open(txt, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	error_handling(file, "File could not open");
	error_handling(dup2(file, 1), "Dup2 failed");
	error_handling(dup2(fd[0], 0), "Dup2 failed.");
	cmd_execution(av, env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid[2];
	int		var;
	{
		if (ac == 5)
		{
			error_handling(pipe(fd), "Could not pipe");
			pid[0] = fork();
			error_handling(pid[0], "Could not fork");
			if (pid[0] == 0)
				child_p1(fd, env, av[2], av[1]);
			pid[1] = fork();
			error_handling(pid[1], "Could not second fork");
			if (pid[1] == 0)
				child_p2(fd, env, av[3], av[4]);
			close(fd[0]);
			close(fd[1]);
			waitpid(pid[0], &var, 0);
			waitpid(pid[1], &var, 0);
			return (WEXITSTATUS(var));
		}
	}
}
