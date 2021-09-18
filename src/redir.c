/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 20:18:48 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/18 20:20:12 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

t_lst	*redirections_handling_helper(t_lst **pipelinelst, int *fd, \
char **in_out_files)
{
	t_lst	*cmd;

	cmd = *pipelinelst;
	while (*pipelinelst && is_out_redir(*pipelinelst, 0))
	{
		out_redir_fd_find(*pipelinelst, fd, in_out_files);
		*pipelinelst = (*pipelinelst)->next->next;
	}
	while (*pipelinelst && is_in_redir(*pipelinelst, 0))
	{
		in_redir_fd_find(*pipelinelst, fd);
		*pipelinelst = (*pipelinelst)->next->next;
	}
	return (cmd);
}

int	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->key[0] != '?')
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
