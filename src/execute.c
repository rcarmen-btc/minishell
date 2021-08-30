/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/30 11:58:07 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "token.h"

int		is_builtin_cmd(char **cmd)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
		|| !(ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
		|| !(ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")))
		|| !(ft_strncmp(cmd[0], "export", ft_strlen("export")))
		|| !(ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
		|| !(ft_strncmp(cmd[0], "env", ft_strlen("env")))
		|| !(ft_strncmp(cmd[0], "exit", ft_strlen("exit"))))
		return (1);
	return (-1);
}

char	*get_infile_name(t_lst *pipelinelst)
{
	char *save;

	save = NULL;
	while (pipelinelst)
	{	
		if (pipelinelst->type == TOKEN_LREDIR)
		{
			pipelinelst = pipelinelst->next;
			if (pipelinelst)	
				save = pipelinelst->cmd[0];
		}
		if (pipelinelst)	
			pipelinelst = pipelinelst->next;
	}
	return (save);
}

char	*get_outfile_name(t_lst *pipelinelst)
{
	while (pipelinelst)
	{	
		if (pipelinelst->type == TOKEN_RREDIR)
		{
			pipelinelst = pipelinelst->next;
			if (pipelinelst)	
				return (pipelinelst->cmd[0]);
		}
		if (pipelinelst)	
			pipelinelst = pipelinelst->next;
	}
	return (NULL);
}

void	execute(t_lst *pipelinelst)
{
	pid_t pid2;
	int tmpin = dup(0);
    int i = 0;
	while(pipelinelst != NULL &&
		(pipelinelst->type == TOKEN_CMD_ARGS || pipelinelst->type == TOKEN_PIPE) &&
		pipelinelst->next != NULL)
    {
		if (pipelinelst->type == TOKEN_CMD_ARGS)
		{
			int pd[2];
			pipe(pd);
			pid_t pid1;
			if (is_builtin_cmd(pipelinelst->cmd) == 1)
			{
				builtins(pipelinelst->cmd, pipelinelst);
				return ;
			}
			if ((pid1 = fork()) == 0) 
			{
				close(pd[0]);
				dup2(pd[1], 1); // remap output back to parent
				execvp(pipelinelst->cmd[0], pipelinelst->cmd);
				perror("exec");
				exit(1);
			}
			// remap output from previous child to input
			wait(&pid1);
			close(pd[1]);
			dup2(pd[0], 0);
			close(pd[0]);
		} 
		pipelinelst = pipelinelst->next;
    }
	if (is_builtin_cmd(pipelinelst->cmd) == 1)
	{
		builtins(pipelinelst->cmd, pipelinelst);
		return ;
	}
	if (pipelinelst != NULL && pipelinelst->type == TOKEN_CMD_ARGS && (pid2 = fork()) == 0)
	{
		// printf("%d\n", );
		execvp(pipelinelst->cmd[0], pipelinelst->cmd);
 		perror("exec");
		exit(1);
	}
	wait(&pid2);
	dup2(tmpin, 0);
	close(tmpin);
}