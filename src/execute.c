/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/31 04:05:01 by rcarmen          ###   ########.fr       */
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
				save = pipelinelst->value;
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

int		is_exists_pipe(t_lst *pipelinelst)
{
	while (pipelinelst != NULL)
	{
		if (pipelinelst->type == TOKEN_PIPE)
			return (1);
		pipelinelst = pipelinelst->next;
	}
	return (0);
}

void	execute(t_lst *pipelinelst)
{
	pid_t pid2 = -1;
	int tmpin = dup(0);
    int i = 0;
	
	int fdin = -1;	
	int	fdout = -1;
	char *outfile;
	char *infile = get_infile_name(pipelinelst);
	if (pipelinelst->type == TOKEN_LREDIR)
		pipelinelst = pipelinelst->next->next;
	if (infile != NULL)
		fdin = open(infile, O_RDONLY);
	else	
		fdin = dup(0);
	dup2(fdin, 0);
	close(fdin);
	// while(pipelinelst != NULL &&
	// 	(pipelinelst->type == TOKEN_CMD_ARGS || pipelinelst->type == TOKEN_PIPE || 
	// 	pipelinelst->type == TOKEN_RREDIR || pipelinelst->type == TOKEN_LREDIR) &&
	// 	pipelinelst->next != NULL)
	while (pipelinelst != NULL && is_exists_pipe(pipelinelst))
    {
		if (pipelinelst->type == TOKEN_PIPE)
		{
			pipelinelst = pipelinelst->next;
			continue ;
		}
		else if (pipelinelst->type == TOKEN_RREDIR || pipelinelst->type == TOKEN_LREDIR)
		{
			pipelinelst = pipelinelst->next->next;
			continue ;
		}
		else if (pipelinelst->type == TOKEN_CMD_ARGS)
		{
			int pd[2];
			pipe(pd);
			pid_t pid1 = -1;
			if ((pid1 = fork()) == 0) 
			{
				close(pd[0]);
				if (pipelinelst->next != NULL && 
				(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_APPRDIR))
				{
					if (pipelinelst->next->next != NULL)
					{
						outfile = pipelinelst->next->next->cmd[0];
						if (pipelinelst->type == TOKEN_RREDIR)
							fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
						else if (pipelinelst->type == TOKEN_APPRDIR)
							fdout = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0666);
					}
				}
				else
				{
					fdout = pd[1];
				}
				dup2(fdout, 1); 	// remap output back to parent
				close(fdout);
				if (is_builtin_cmd(pipelinelst->cmd) == 1)
				{
					builtins(pipelinelst->cmd, pipelinelst);
					exit(0);
				}
				else
					execvp(pipelinelst->cmd[0], pipelinelst->cmd);
				perror("exec");
				exit(1);
			}
			// if (pid1 != -1)
			wait(&pid1);
			// remap output from previous child to input
			close(pd[1]);
			dup2(pd[0], 0);
			close(pd[0]);
			pipelinelst = pipelinelst->next;
		} 
    }
	if (pipelinelst != NULL && pipelinelst->type == TOKEN_CMD_ARGS && is_builtin_cmd(pipelinelst->cmd) == 1)
	{
		builtins(pipelinelst->cmd, pipelinelst);
		return ;
	}
	if (pipelinelst != NULL && (pid2 = fork()) == 0)
	{
		// printf("sadf\n");
		if (pipelinelst->next != NULL && (pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_APPRDIR))
		{
			if (pipelinelst->next->next != NULL)
			{
				printf("%s\n", pipelinelst->next->next->cmd[0]);
				outfile = pipelinelst->next->next->cmd[0];
				if (pipelinelst->type == TOKEN_RREDIR)
					fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else if (pipelinelst->type == TOKEN_APPRDIR)
					fdout = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0666);
				dup2(fdout, 1);
				close(fdout);
			}
		}
		execvp(pipelinelst->cmd[0], pipelinelst->cmd);
 		perror("exec");
		exit(1);
	}
	wait(&pid2);
	dup2(tmpin, 0);
	close(tmpin);
}