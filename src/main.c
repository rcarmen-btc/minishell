/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:23:51 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
