/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/12 13:51:52 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "token.h"
#include <sys/stat.h>

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

int		handle_heredoc(t_lst *pipelinelst)	
{
	char	*delim;
	char	*heredoc_line;
	int		fdin;
	int		fdtmp;
	char	hist[MAXCOM];

	if (pipelinelst->next != NULL)
	{
		fdtmp = open(".chillytmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		delim = pipelinelst->next->next->cmd[0];
		heredoc_line = NULL;
		heredoc_line = readline("> ");
		while (ft_strncmp(delim, heredoc_line, ft_strlen(delim)) != 0 || heredoc_line[0] == '\0')
		{
			write(fdtmp, heredoc_line, ft_strlen(heredoc_line));
			write(fdtmp, "\n", 1);
			heredoc_line = readline("> ");
		}
		close(fdtmp);
		fdin = open(".chillytmp", O_RDONLY);
		return (fdin);
	}
	return (0);
}

char	*get_path_to_exe_heplper(char **path, char *command)
{
	char	*slash;
	char	*with_slash;
	char	*full_path;
	struct stat buf;

	slash = "/";
	while (*path != 0)
	{
		with_slash = ft_strjoin(slash, command);
		full_path = ft_strjoin(*path, with_slash);
		free(with_slash);
		if (stat(full_path, &buf) != -1)
		{
			while (*path)
				free(*path++);
			// free(path);
			return (full_path);
		}
		free(full_path);
		free(*path);
		path++;
	}
	return (NULL);
}

int		get_slash_cnt(char *name)
{
	int i;
	int cnt;
	
	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			cnt++;
		i++;
	}
	return (cnt);	
}

char	*get_path_to_exe(t_env *env, char *name)
{
	char	**path;
	char	*res;
	struct stat buf;

	if (get_slash_cnt(name) > 0 && stat(name, &buf) != -1)
		return (name);
	while (env != NULL)
	{
		if (ft_strncmp(env->key, "PATH", ft_strlen(env->key)) == 0)
			break ;
		env = env->next;
	}
	path = ft_split(env->value, ':');
	res = get_path_to_exe_heplper(path, name);
	if (res != NULL)
		return (res);
	else
		printf("%s: command not found\n", name);
	return (NULL);
}

int	execute(t_lst *pipelinelst, char **line, t_env *env, char **ep)
{
	pid_t pid1;
	pid_t pid2;
	int fdin;	
	int	fdout;
	char *outfile;
	char *infile;
	int tmpin;
	int tmpout;
    int i;
	int pd[2];

	ex_signals();
	
	// in_signals();
	tmpin = dup(0);
	fdin = dup(0);
	fdout = dup(1);
	infile = get_infile_name(pipelinelst);
	i = 0;
	if (pipelinelst && (pipelinelst->type == TOKEN_LREDIR || pipelinelst->type == TOKEN_RREDIR || pipelinelst->type == TOKEN_APPRDIR))
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
		pipe(pd);
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
				(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_LREDIR || pipelinelst->next->type == TOKEN_APPRDIR || pipelinelst->next->type == TOKEN_HERE_DOC) && \
				pipelinelst->next->next != NULL)
				{
					outfile = pipelinelst->next->next->cmd[0];
					// printf("%s\n", outfile);
					if (pipelinelst->next->type == TOKEN_RREDIR)
						fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
					else if (pipelinelst->next->type == TOKEN_APPRDIR)
						fdout = open(outfile, O_WRONLY | O_CREAT| O_APPEND, 0666);
					else if (pipelinelst->next->type == TOKEN_LREDIR)
					{
						fdin = open(outfile, O_RDONLY);
						dup2(fdin, 0);
						close(fdin);
						fdout = dup(pd[1]);
					}
					else if (pipelinelst->next->type == TOKEN_HERE_DOC)
					{
						fdin = handle_heredoc(pipelinelst);	
						dup2(fdin, 0);
						close(fdin);
						fdout = dup(pd[1]);
					}
				}
				else
					fdout = dup(pd[1]);
				dup2(fdout, 1);
				close(fdout);
				if (is_builtin_cmd(pipelinelst->cmd) == 1)
				{
					dup2(tmpin, 0);
					builtins(pipelinelst->cmd, pipelinelst, env);
					exit(0);
				}
				else
				{
					execvp(pipelinelst->cmd[0], pipelinelst->cmd);
					perror("exec+");
					exit(1);
				}
			}
			wait(&pid1);
			close(pd[1]);
			dup2(pd[0], 0);
			close(pd[0]);
			pipelinelst = pipelinelst->next;
			if (pipelinelst->type == TOKEN_HERE_DOC || pipelinelst->type == TOKEN_APPRDIR)
				pipelinelst = pipelinelst->next->next;
		} 
	}
	if (pipelinelst != NULL && pipelinelst->type == TOKEN_CMD_ARGS && is_builtin_cmd(pipelinelst->cmd) == 1)
	{
		int ret;
		dup2(tmpin, 0);
		if (pipelinelst->next != NULL && \
		(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_LREDIR || pipelinelst->next->type == TOKEN_APPRDIR || pipelinelst->next->type == TOKEN_HERE_DOC) && \
		pipelinelst->next->next != NULL)
		{
			outfile = pipelinelst->next->next->cmd[0];
			if (pipelinelst->next->type == TOKEN_RREDIR)
			{
				fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				dup2(fdout, 1);
				close(fdout);
			}
			dup2(fdin, 0);
		}
		ret = builtins(pipelinelst->cmd, pipelinelst, env);
		dup2(tmpout, 1);
		dup2(tmpin, 0);
		return (ret);
	}
	else if (pipelinelst != NULL && pipelinelst->type == TOKEN_CMD_ARGS && (pid2 = fork()) == 0)
	{
		if (pipelinelst->next != NULL && \
		(pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_LREDIR || pipelinelst->next->type == TOKEN_APPRDIR || pipelinelst->next->type == TOKEN_HERE_DOC) && \
		pipelinelst->next->next != NULL)
		{
			if (pipelinelst->next->type == TOKEN_RREDIR || pipelinelst->next->type == TOKEN_APPRDIR)
			{
				outfile = pipelinelst->next->next->cmd[0];
				if (pipelinelst->next->type == TOKEN_RREDIR)
					fdout = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
				else
					fdout = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
				if (pipelinelst->next->type == TOKEN_RREDIR && \
					pipelinelst->next->next->next && pipelinelst->next->next->next->type == TOKEN_LREDIR)
				{
					infile = pipelinelst->next->next->next->next->cmd[0];
					fdin = open(infile, O_RDONLY);
				}
				else if (pipelinelst->next->type == TOKEN_APPRDIR && \
					pipelinelst->next->next->next && pipelinelst->next->next->next->type == TOKEN_LREDIR)
				{
					infile = pipelinelst->next->next->next->next->cmd[0];
					fdin = open(outfile, O_RDONLY);
				}

			}
			else if (pipelinelst->next->type == TOKEN_LREDIR)
			{
				infile = pipelinelst->next->next->cmd[0];
				fdin = open(infile, O_RDONLY);
				if (pipelinelst->next->next->next && pipelinelst->next->next->next->type == TOKEN_RREDIR)
				{
					outfile = pipelinelst->next->next->next->next->cmd[0];
					fdout = open(outfile, O_WRONLY | O_CREAT| O_TRUNC, 0666);
				}
				else if (pipelinelst->next->next->next && pipelinelst->next->next->next->type == TOKEN_APPRDIR)
				{
					fdout = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
					infile = pipelinelst->next->next->next->next->cmd[0];
				}
			}
			else if (pipelinelst->next->type == TOKEN_HERE_DOC)
			{
				dup2(tmpin, 0);
				fdin = handle_heredoc(pipelinelst);	
				// dup2(fdin, 0);
				// close(fdin);
			}
			fdin = open(infile, O_RDONLY);
			dup2(fdin, 0);
			close(fdin);
			dup2(fdout, 1);
			close(fdout);
		}
		if (is_builtin_cmd(pipelinelst->cmd) == 1)
		{
			dup2(tmpin, 0);
			builtins(pipelinelst->cmd, pipelinelst, env);
			exit(0);
		}
		else
		{
			char *path_to_exe = get_path_to_exe(env, pipelinelst->cmd[0]);
			if (path_to_exe == NULL)
				exit(1);
			execve(path_to_exe, pipelinelst->cmd, ep);
			perror(pipelinelst->cmd[0]);
			exit(1);
		}
	}
	int status;
	pid2 = wait(&status);
	status = WEXITSTATUS(status);
	dup2(tmpin, 0);
	close(tmpin);
	return (status);
}