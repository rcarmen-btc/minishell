/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ijk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:13:35 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/24 11:10:56 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	in_redir_fd_find(t_lst *pipelinelst, int *fd)
{
	if (pipelinelst->next->type == TOKEN_LREDIR && \
		pipelinelst->next->next->type == TOKEN_CMD_ARGS)
		fd[0] = ft_open_in(pipelinelst->next->next->cmd[0], O_RDONLY, fd[0]);
	else if (pipelinelst->next->type == TOKEN_HERE_DOC && \
		pipelinelst->next->next->type == TOKEN_CMD_ARGS)
		fd[0] = handle_heredoc(pipelinelst);
	if (is_out_redir(pipelinelst, 1) == 1 && pipelinelst->next->next->next && \
		pipelinelst->next->next->next->next && \
		pipelinelst->next->next->next->next->type == TOKEN_CMD_ARGS)
		fd[1] = ft_open_out(pipelinelst->next->next->next->next->cmd[0], 0);
	if (is_out_redir(pipelinelst, 1) == -1 && pipelinelst->next->next->next && \
		pipelinelst->next->next->next->next && \
		pipelinelst->next->next->next->next->type == TOKEN_CMD_ARGS)
		fd[1] = ft_open_out(pipelinelst->next->next->next->next->cmd[0], 1);
}

void	time_to_execute_the_command(t_lst *pipelinelst, t_env *env, char **ep)
{
	char	*path_to_exe;

	if (is_builtin_cmd(pipelinelst->cmd) == 1)
	{
		builtins(pipelinelst->cmd, env);
		exit(0);
	}
	else
	{
		path_to_exe = get_path_to_exe(env, pipelinelst->cmd[0]);
		if (path_to_exe == NULL)
			exit(127);
		execve(path_to_exe, pipelinelst->cmd, ep);
		perror(pipelinelst->cmd[0]);
		exit(1);
	}
}

void	set_out_and_in(int *fd)
{
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	pd_helper(int *pd)
{
	if (pd != NULL)
	{
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
	}
}

int	redirections_handling(t_lst **pipelinelst, char **ep, \
t_env *env, int pd[2])
{
	char	*in_out_files[2];
	int		fd[2];
	int		status;
	t_lst	*cmd;

	fd[1] = dup(1);
	fd[0] = dup(0);
	cmd = redirections_handling_helper(pipelinelst, fd, in_out_files);
	if (*pipelinelst != NULL && (*pipelinelst)->type == TOKEN_CMD_ARGS && \
		fork() == 0)
	{
		if (pd != NULL)
		{
			close(fd[1]);
			fd[1] = pd[1];
		}
		set_out_and_in(fd);
		if (fd[0] != -1 && fd[1] != -1)
			time_to_execute_the_command(cmd, env, ep);
		else
			exit(0);
	}
	close(fd[1]);
	wait(&status);
	pd_helper(pd);
	return (WEXITSTATUS(status));
}
