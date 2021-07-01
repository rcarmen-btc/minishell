/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/02 01:27:39 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_path_to_exe(char **ep, char *command, t_args *args)
{
	char	**path;
	char	*slash;
	
	slash = "/";
	while (*ep != NULL)
	{
		if (ft_strncmp(*ep, "PATH", 4) == 0)
			break ;
		ep++;
	}
	path = ft_split(*ep, ':');
	args->tmp_path = path;
	while (*path != 0)
	{
		args->with_slash = ft_strjoin(slash, command);	
		args->full_path = ft_strjoin(*path, args->with_slash);
		free(args->with_slash);
		if (access(args->full_path, 0) == 0)
		{
			while (*path)
				free(*path++);
			free(args->tmp_path);
			return (args->full_path);
		}
		free(args->full_path);
		free(*path);
		*path++;
	}
	error(command, 1, args);
	return (NULL);
}

int	init_args(t_args *args, int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5)
		return (1);
	args->file1 = ft_strdup(av[1]);
	args->command1 = ft_split(av[2], ' ');
	args->command2 = ft_split(av[3], ' ');
	args->file2 = ft_strdup(av[4]);	
	return (0);
}

void		free_and_exit(t_args *args, int id)
{
	char	**tmp;

	if (id == 0)	
	{
		free(args);
		exit(1);
	}
	else if (id == 1)
	{
		free(args->tmp_path);
		free(args->full_path1);
		free(args->full_path2);
		free(args->file1);
		free(args->file2);
		tmp = args->command1;
		while (*args->command1)
			free(*args->command1++);
		free(tmp);
		tmp = args->command2;
		while (*args->command2)
			free(*args->command2++);
		free(tmp);
		free(args);
		exit(1);
	}
	else if (id == 2)
	{
		free(args->full_path1);
		free(args->full_path2);
		free(args->file1);
		free(args->file2);
		tmp = args->command1;
		while (*args->command1)
			free(*args->command1++);
		free(tmp);
		tmp = args->command2;
		while (*args->command2)
			free(*args->command2++);
		free(tmp);
		free(args);
		exit(1);
	}
	else if (id == 3)
	{
		free(args->full_path1);
		free(args->full_path2);
		free(args->file1);
		free(args->file2);
		tmp = args->command1;
		while (*args->command1)
			free(*args->command1++);
		free(tmp);
		tmp = args->command2;
		while (*args->command2)
			free(*args->command2++);
		free(tmp);
		free(args);
		exit(1);
	}
}

void		error(char *output, int id, t_args *args)
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
	else if (id == 3)
	{
		perror(args->file1);
		free_and_exit(args, 3);
	}
}

int	main(int ac, char **av, char **ep)
{
	int		fd[2];
	t_args	*args;
	int		outfile_fd;

	args = (t_args *)ft_calloc(sizeof(t_args), 1);
	if (init_args(args, ac, av) == 1)
		error("Error.\n", 0, args);
	args->full_path1 = get_path_to_exe(ep, args->command1[0], args);
	args->full_path2 = get_path_to_exe(ep, args->command2[0], args);
	pipe(fd);
	if (fork() == 0)
	{
		outfile_fd = open(args->file1, O_RDONLY);
		if (outfile_fd == -1)
			error("Man, I love frogs\n", 3, args);
		close(fd[0]);
		dup2(outfile_fd, 0);
		close(outfile_fd);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(args->full_path1, args->command1, NULL);
		perror(args->command1[0]);
		exit(1);
	}
	if (fork() == 0)
	{
		outfile_fd = open(args->file2, O_CREAT|O_WRONLY|O_TRUNC, 0666);
		if (outfile_fd == -1)
			error("Man, I love frogs\n", 3, args);
		close(fd[1]);
		dup2(outfile_fd, 1);
		close(outfile_fd);
		dup2(fd[0], 0);
		close(fd[0]);
		execve(args->full_path2, args->command2, NULL);
		perror(args->command2[0]);
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	wait(NULL);
	free_and_exit(args, 2);
	return (0);
}