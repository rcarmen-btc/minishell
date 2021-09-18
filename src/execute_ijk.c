/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ijk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:13:35 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/18 20:05:14 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	in_redir_fd_find(t_lst *pipelinelst, int *fd)
{
	if (pipelinelst->next->type == TOKEN_LREDIR)
		fd[0] = open(pipelinelst->next->next->cmd[0], O_RDONLY);
	else if (pipelinelst->next->type == TOKEN_HERE_DOC)
		fd[0] = handle_heredoc(pipelinelst);
	if (pipelinelst->next->next->next && is_out_redir(pipelinelst, 1) == 1)
		fd[1] = open(pipelinelst->next->next->next->next->cmd[0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipelinelst->next->next->next && is_out_redir(pipelinelst, 1) == -1)
		fd[1] = open(pipelinelst->next->next->next->next->cmd[0], \
		O_WRONLY | O_CREAT | O_APPEND, 0666);
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
	int		tmp;

	fd[0] = dup(0);
	fd[1] = dup(1);
	tmp = fd[1];
	cmd = redirections_handling_helper(pipelinelst, fd, in_out_files);
	if (*pipelinelst != NULL && (*pipelinelst)->type == TOKEN_CMD_ARGS && \
		fork() == 0)
	{
		if (fd[1] == tmp && pd != NULL)
			fd[1] = pd[1];
		set_out_and_in(fd);
		time_to_execute_the_command(cmd, env, ep);
	}
	wait(&status);
	pd_helper(pd);
	return (WEXITSTATUS(status));
}
