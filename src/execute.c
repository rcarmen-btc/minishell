/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:13:29 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "token.h"
#include <sys/stat.h>

int	is_builtin_cmd(char **cmd)
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
	char	*save;

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

int	is_exists_pipe(t_lst *pipelinelst)
{
	while (pipelinelst != NULL)
	{
		if (pipelinelst->type == TOKEN_PIPE)
			return (1);
		pipelinelst = pipelinelst->next;
	}
	return (0);
}

int	handle_heredoc(t_lst *pipelinelst)
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
		while (ft_strncmp(delim, heredoc_line, ft_strlen(delim)) != 0 || \
			heredoc_line[0] == '\0')
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
	char			*slash;
	char			*with_slash;
	char			*full_path;
	struct stat		buf;
	int				i;

	i = 0;
	slash = "/";
	while (path[i] != 0)
	{
		with_slash = ft_strjoin(slash, command);
		full_path = ft_strjoin(path[i], with_slash);
		free(with_slash);
		if (stat(full_path, &buf) != -1)
		{
			while (path[i])
				free(path[i++]);
			return (full_path);
		}
		free(full_path);
		free(path[i]);
		i++;
	}
	return (NULL);
}

int	get_slash_cnt(char *name)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
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

