/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wtf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:12:34 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/24 03:43:01 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_next_is_rdir(t_lst *pipelinelst)
{
	if (pipelinelst->next != NULL && pipelinelst->next->next != NULL && \
	(pipelinelst->next->type == TOKEN_RREDIR || \
	pipelinelst->next->type == TOKEN_LREDIR || \
	pipelinelst->next->type == TOKEN_APPRDIR || \
	pipelinelst->next->type == TOKEN_HERE_DOC))
		return (1);
	return (0);
}

int	last_builtin_cmd(t_lst *pipelinelst, int tmpin, int tmpout, t_env *env)
{
	int		ret;
	int		fd[2];
	char	*in_out_files[2];
	t_lst	*tmp;

	dup2(tmpin, 0);
	fd[0] = dup(0);
	fd[1] = dup(1);
	tmp = redirections_handling_helper(&pipelinelst, fd, in_out_files);
	set_out_and_in(fd);
	ret = 0;
	if (is_builtin_cmd(tmp->cmd) == 1)
		ret = builtins(tmp->cmd, env);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	return (ret);
}

int	skip_pipes_and_rdirs(t_lst **pipelinelst, char **ep, t_env *env, int *pd)
{
	if ((*pipelinelst)->type == TOKEN_PIPE)
	{
		*pipelinelst = (*pipelinelst)->next;
		return (1);
	}
	else if ((*pipelinelst)->type == TOKEN_RREDIR || \
		(*pipelinelst)->type == TOKEN_LREDIR)
	{
		*pipelinelst = (*pipelinelst)->next->next;
		return (1);
	}
	if ((*pipelinelst)->type == TOKEN_CMD_ARGS)
	{
		redirections_handling(pipelinelst, ep, env, pd);
		*pipelinelst = (*pipelinelst)->next;
	}
	return (0);
}

int	check_builtins(t_lst *pipelinelst)
{
	if (ft_strncmp(pipelinelst->cmd[0], "cd", 2) == 0 || \
	ft_strncmp(pipelinelst->cmd[0], "env", 3) == 0 || \
	ft_strncmp(pipelinelst->cmd[0], "unset", 5) == 0 || \
	ft_strncmp(pipelinelst->cmd[0], "export", 6) == 0 || \
	ft_strncmp(pipelinelst->cmd[0], "export", 6) == 0)
		return (1);
	return (0);
}

int	execute(t_lst *pipelinelst, t_env *env, char **ep)
{
	int	pd[2];
	int	tmpin;
	int	tmpout;
	int	status;

	tmpin = dup(0);
	tmpout = dup(1);
	ex_signals();
	while (pipelinelst != NULL && is_exists_pipe(pipelinelst))
	{
		pipe(pd);
		if (skip_pipes_and_rdirs(&pipelinelst, ep, env, pd))
			continue ;
		if (pipelinelst->type == TOKEN_HERE_DOC || \
			pipelinelst->type == TOKEN_APPRDIR)
			pipelinelst = pipelinelst->next->next;
	}
	if (pipelinelst != NULL && \
		pipelinelst->type == TOKEN_CMD_ARGS && \
		is_builtin_cmd(pipelinelst->cmd) == 1)
		return (last_builtin_cmd(pipelinelst, tmpin, tmpout, env));
	status = redirections_handling(&pipelinelst, ep, env, NULL);
	dup2(tmpin, 0);
	close(tmpin);
	return (status);
}
