/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_to_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:21:13 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_path_to_exe_heplper(char **path, char *command, t_args *args)
{
	char	*slash;

	slash = "/";
	while (*path != 0)
	{
		args->with_slash = ft_strjoin(slash, command);
		args->full_path = ft_strjoin(*path, args->with_slash);
		free(args->with_slash);
		if (access(args->full_path, 0) == 0)
		{
			while (*path)
				free(*path++);
			free(args->tmp_path);
			return (args->full_path);
		}
		free(args->full_path);
		free(*path);
		path++;
	}
	return (NULL);
}

char	*get_path_to_exe(char **ep, char *command, t_args *args)
{
	char	**path;
	char	*res;

	while (*ep != NULL)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	path = ft_split(*ep, ':');
	args->tmp_path = path;
	res = get_path_to_exe_heplper(path, command, args);
	if (res)
		return (res);
	else
		error(command, 1, args);
	return (NULL);
}
