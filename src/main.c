/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:12:15 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	error(char *output, int id, t_args *args)
{
	if (id == 0)
	{
		write(1, output, ft_strlen(output));
		free_and_exit(args, 0);
	}
	else if (id == 1)
	{
		write(1, output, ft_strlen(output));
		write(1, ": command not found\n", ft_strlen(": command not found\n"));
		free_and_exit(args, 1);
	}
	else if (id == 2)
	{
		perror(args->file1);
		free_and_exit(args, 2);
	}	
}

int	is_exists_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t				len;
	size_t				i;
	char				*mem;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
		return (NULL);
	while (*s1 != '\0')
		mem[i++] = *s1++;
	mem[i++] = ' ';
	while (*s2 != '\0')
		mem[i++] = *s2++;
	mem[i] = '\0';
	return (mem);
}

char	*join_in_one_arr(char **args, int start, int end)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin_space(args[start], args[start + 1]);
	start = start + 2;
	while (start <= end)
	{
		tmp = res;
		res = ft_strjoin_space(res, args[start]);
		free(tmp);
		start++;
	}
	return (res);
}

char 	**new_arr_args(char **args, char *qstr, int len)
{	
	char	**res;
	int		i;

	res = (char **)ft_calloc(sizeof(char **), len + 2);
	res[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		res[i] = ft_strdup(args[i]);
		i++;
	}
	res[i] = ft_strdup(qstr);
	return (res);
}

void	find_start_and_end(int *i, int *j, char **args)
{
	while (args[*i])
	{
		if (is_exists_quotes(args[*i]) && *j == 0)
			*j = *i;
		(*i)++;
	}
}

char	**join_in_qoutes(char **args, char *s, char **tmp1)
{
	int		i;
	int		j;
	char	*qstr;
	char	**all;
	char	*tmp;

	i = 0;
	j = 0;
	args = ft_split(s, ' ');
	find_start_and_end(&i, &j, args);
	qstr = join_in_one_arr(args, j, i - 1);
	tmp = qstr;
	if (qstr[0] == '"')
		qstr = ft_strtrim(qstr, "\"");
	else
		qstr = ft_strtrim(qstr, "'");
	free(tmp);
	all = new_arr_args(args, qstr, j);
	tmp1 = args;
	while (*args)
		free(*args++);
	free(tmp1);
	free(qstr);
	return (all);
}

int	init_args(t_args *args, int ac, char **av)
{
	if (ac != 5)
		return (1);
	args->file1 = ft_strdup(av[1]);
	if (is_exists_quotes(av[2]))
		args->command1 = join_in_qoutes(args->command1, av[2], NULL);
	else
		args->command1 = ft_split(av[2], ' ');
	if (is_exists_quotes(av[3]))
		args->command2 = join_in_qoutes(args->command2, av[3], NULL);
	else
		args->command2 = ft_split(av[3], ' ');
	args->file2 = ft_strdup(av[4]);
	return (0);
}

void	first_child(t_args *args, int *fd)
{
	int	outfile_fd;

	if (fork() == 0)
	{
		outfile_fd = open(args->file2, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (outfile_fd == -1)
			error("Man, I love frogs\n", 2, args);
		close(fd[1]);
		dup2(outfile_fd, 1);
		close(outfile_fd);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(args->full_path2, args->command2, NULL);
		perror(args->command2[0]);
		exit(1);
	}
}

void	second_child(t_args *args, int *fd)
{
	int	outfile_fd;

	if (fork() == 0)
	{
		outfile_fd = open(args->file1, O_RDONLY);
		if (outfile_fd == -1)
			error("Man, I love frogs\n", 2, args);
		close(fd[0]);
		dup2(outfile_fd, 0);
		close(outfile_fd);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(args->full_path1, args->command1, NULL);
		perror(args->command1[0]);
		exit(1);
	}
}

int	main(int ac, char **av, char **ep)
{
	int		fd[2];
	t_args	*args;

	args = (t_args *)ft_calloc(sizeof(t_args), 1);
	if (init_args(args, ac, av) == 1)
		error("Error.\n", 0, args);
	args->full_path1 = get_path_to_exe(ep, args->command1[0], args);
	args->full_path2 = get_path_to_exe(ep, args->command2[0], args);
	pipe(fd);
	first_child(args, fd);
	second_child(args, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	free_and_exit(args, 2);
	return (0);
}
