/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sheesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:24:26 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/18 10:06:05 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*get_path_to_exe_heplper(char **path, char *command)
{
	char			*slash;
	char			*with_slash;
	char			*full_path;
	struct stat		buf;
	int				i;

	i = 0;
	slash = "/";
	while (path[i] != 0)
	{
		with_slash = ft_strjoin(slash, command);
		full_path = ft_strjoin(path[i], with_slash);
		free(with_slash);
		if (stat(full_path, &buf) != -1)
		{
			while (path[i])
				free(path[i++]);
			return (full_path);
		}
		free(full_path);
		free(path[i]);
		i++;
	}
	return (NULL);
}

int	get_slash_cnt(char *name)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (name[i])
	{
		if (name[i] == '/')
			cnt++;
		i++;
	}
	return (cnt);
}

int get_max_nbr(int first, int second)
{
	int nbr;
	nbr = first; 
	if (second > first)
		nbr = second;
	return (nbr);
}