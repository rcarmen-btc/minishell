/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/03 17:10:22 by rcarmen          ###   ########.fr       */
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

int		handle_heredoc(t_lst *pipelinelst, char **line)	
{
	char	*delim;
	char	*heredoc_line;
	int		fdin;
	int		fdtmp;
	char	hist[MAXCOM];

	printf("%s\n", pipelinelst->cmd[0]);
	if (pipelinelst->next != NULL)
	{
		fdtmp = open(".chillytmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		delim = pipelinelst->next->next->cmd[0];
		heredoc_line = NULL;
		heredoc_line = readline("> ");
		while (ft_strncmp(delim, heredoc_line, ft_strlen(heredoc_line)) != 0)
		{
			write(fdtmp, heredoc_line, ft_strlen(heredoc_line));
			write(fdtmp, "\n", 1);
			heredoc_line = readline("> ");
		}
		close(fdtmp);
		// fdtmp = open(".chillytmp", O_RDONLY);
		// read(fdin, hist, MAXCOM);
		// close(fdin);
		// *line = ft_strjoin(*line, "\n");
		// *line = ft_strjoin(*line, hist);
		fdin = open(".chillytmp", O_RDONLY);
		printf("herein: %d\n", fdin);
		return (fdin);
	}
	return (0);
}

void	execute(t_lst *pipelinelst, char **line)
{
	pid_t pid1;
	pid_t pid2;
	int fdin;	
	int	fdout;
	char *outfile;
	char *infile;
	int tmpin;
    int i;
	int pd[2];

	tmpin = dup(0);
	// fdout = dup(1);
	infile = get_infile_name(pipelinelst);
	i = 0;
	pipe(pd);
	if (pipelinelst->type == TOKEN_LREDIR || pipelinelst->type == TOKEN_RREDIR || pipelinelst->type == TOKEN_APPRDIR)
	{
		if (pipelinelst->type == TOKEN_RREDIR || pipelinelst->type == TOKEN_APPRDIR)
		{
			fdout = open(pipelinelst->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fdout);
		}
		pipelinelst = pipelinelst->next->next;
	}
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
			if ((pid1 = fork()) == 0) 
			{
				close(pd[0]);
				if (pipelinelst->next != NULL && \
				(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_APPRDIR || pipelinelst->next->type == TOKEN_HERE_DOC) && \
				pipelinelst->next->next != NULL)
				{
					outfile = pipelinelst->next->next->cmd[0];
					if (pipelinelst->next->type == TOKEN_RREDIR)
						fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
					else if (pipelinelst->next->type == TOKEN_APPRDIR)
						fdout = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0666);
					else if (pipelinelst->next->type == TOKEN_HERE_DOC)
					{
						fdin = handle_heredoc(pipelinelst, line);	
						dup2(fdin, 0);
						close(fdin);
						fdout = pd[1];
						// dup2(fdout, 1);
						// close)
						// printf("%d %d\n", fdin, fdout);
					}
				}
				else
					fdout = dup(pd[1]);
				dup2(fdout, 1);
				if (pd[1] != fdout)
					close(fdout);
				if (is_builtin_cmd(pipelinelst->cmd) == 1)
				{
					builtins(pipelinelst->cmd, pipelinelst);
					exit(0);
				}
				else
				{
					execvp(pipelinelst->cmd[0], pipelinelst->cmd);
				}
				perror("exec");
				exit(1);
			}
			wait(&pid1);
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
	if (pipelinelst != NULL && pipelinelst->type == TOKEN_CMD_ARGS && (pid2 = fork()) == 0)
	{
		// sleep(20);
		if (pipelinelst->next != NULL && \
		(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_APPRDIR || pipelinelst->next->type == TOKEN_HERE_DOC) && \
		pipelinelst->next->next != NULL)
		{
			outfile = pipelinelst->next->next->cmd[0];
			if (pipelinelst->next->type == TOKEN_RREDIR)
				fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (pipelinelst->next->type == TOKEN_APPRDIR)
				fdout = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0666);
			else if (pipelinelst->next->type == TOKEN_HERE_DOC)
			{
				fdin = handle_heredoc(pipelinelst, line);	
				dup2(fdin, 0);
				close(fdin);
			}
			dup2(fdout, 1);
			// close(fdout);
		}
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
	wait(&pid2);
	dup2(tmpin, 0);
	close(tmpin);
}