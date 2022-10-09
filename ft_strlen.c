/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:09:48 by iel-moha          #+#    #+#             */
/*   Updated: 2022/04/01 16:46:38 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	error_handling(int i, char *str)
{
	if (i == -1)
	{
		perror(str);
		exit(1);
	}	
}

void	ft_free(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	free(*str);
}
