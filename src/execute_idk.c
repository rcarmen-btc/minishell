/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_idk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:17:11 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:50:37 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <sys/stat.h>

char	*get_path_to_exe(t_env *env, char *name)
{
	char			**path;
	char			*res;
	struct stat		buf;

	if (get_slash_cnt(name) > 0 && stat(name, &buf) != -1)
		return (name);
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", ft_strlen(env->key)) == 0)
			break ;
		env = env->next;
	}
	if (env == NULL || get_slash_cnt(name) > 0)
	{
		printf("%s: command not found\n", name);
		return (NULL);
	}
	path = ft_split(env->value, ':');
	res = get_path_to_exe_heplper(path, name);
	free(path);
	if (res != NULL)
		return (res);
	else
		printf("%s: command not found\n", name);
	return (NULL);
}

int	check_next(t_lst *pipelinelst, int lvl)
{
	if (lvl == 0)
	{
		if (pipelinelst->next != NULL && \
			pipelinelst->next->next != NULL && \
			pipelinelst->next->next->next != NULL)
			return (1);
		return (0);
	}
	else if (lvl == 1)
	{
		if (pipelinelst->next != NULL && \
			pipelinelst->next->next != NULL)
			return (1);
		return (0);
	}
	return (0);
}

int	is_out_redir(t_lst *pipelinelst, int lvl)
{
	if (lvl == 0)
	{
		if (pipelinelst->next != NULL && \
			pipelinelst->next->next != NULL && \
			(pipelinelst->next->type == TOKEN_RREDIR || \
			pipelinelst->next->type == TOKEN_APPRDIR))
			return (1);
		return (0);
	}
	else
	{
		if (check_next(pipelinelst, 0) && \
			pipelinelst->next->next->next->type == TOKEN_RREDIR)
			return (1);
		else if (check_next(pipelinelst, 0) && \
			pipelinelst->next->next->next->type == TOKEN_APPRDIR)
		{
			return (-1);
		}
	}
	return (0);
}

int	is_in_redir(t_lst *pipelinelst, int lvl)
{
	if (lvl == 0)
	{
		if (check_next(pipelinelst, 1) && \
			(pipelinelst->next->type == TOKEN_LREDIR || \
			pipelinelst->next->type == TOKEN_HERE_DOC))
			return (1);
		return (0);
	}
	else if (lvl == 1)
	{
		if (check_next(pipelinelst, 0) && \
			pipelinelst->next->next->next->type == TOKEN_LREDIR)
			return (1);
		return (0);
	}
	return (0);
}

void	out_redir_fd_find(t_lst *pipelinelst, int *fd, char **in_out_files)
{
	in_out_files[1] = pipelinelst->next->next->cmd[0];
	if (pipelinelst->next->type == TOKEN_RREDIR)
		fd[1] = open(in_out_files[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd[1] = open(in_out_files[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (is_in_redir(pipelinelst, 1))
		fd[0] = open(pipelinelst->next->next->next->next->cmd[0], O_RDONLY);
}
