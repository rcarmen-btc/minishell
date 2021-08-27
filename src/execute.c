/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/27 15:38:59 by rcarmen          ###   ########.fr       */
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

void	cmd_without_pipes(char **cmd, t_lst *pipelinelst)
{
    pid_t pid;

	if (is_builtin_cmd(cmd) == 1)
	{
		builtins(cmd, pipelinelst);
		return ;
	}
	pid = fork(); 
    if (pid == -1)
	{
		perror("fork");
        return;
    }
	else if (pid == 0)
	{
        if (execvp(cmd[0], cmd) < 0)
		{
        }
        exit(0);
    }
	else
	{
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}	

int		is_penultimate_cmd(t_lst *pipelinelst)
{
	if (pipelinelst && pipelinelst->next != NULL && pipelinelst->next->next != NULL  && pipelinelst->next->next->next == NULL)	
		return (1);
	return (0);
}

void	pipeline(t_lst *pipelinelst)
{
    int i;

	while (pipelinelst->type == TOKEN_CMD_ARGS && is_penultimate_cmd(pipelinelst))
    {
		int pd[2];
		pipe(pd);
		pid_t pid; 

		if ((pid = fork()) == 0) {
			dup2(pd[1], 1); // remap output back to parent
			execvp(pipelinelst->cmd[0], pipelinelst->cmd);
			perror("exec");
			abort();
		}
		// remap output from previous child to input
		wait(NULL);
		dup2(pd[0], 0);
		close(pd[1]);
		pipelinelst = pipelinelst->next;
	}
	if (!fork()) {
		execvp(pipelinelst->cmd[0], pipelinelst->cmd);
		perror("exec");
		abort();
	}
	wait(NULL);
}

void	execute(t_lst *pipelinelst)
{
	if (get_lst_len(pipelinelst) == 1)
		cmd_without_pipes(pipelinelst->cmd, pipelinelst);	
	// pipeline(pipelinelst);
	// if (get_lst_len(pipelinelst) > 1)
	// 	cmd_with_pipes();	

	// builtin_pwd();
	// builtin_cd(pipelinelst->cmd);
}