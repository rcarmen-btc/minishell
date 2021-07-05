/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 12:44:55 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_helper(t_args *args)
{
	char	**tmp;

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

void	free_and_exit(t_args *args, int id)
{
	if (id == 0)
	{
		free(args);
		exit(1);
	}
	else if (id == 1)
	{
		free(args->tmp_path);
		free_and_exit(args, 2);
	}
	else if (id == 2)
		free_helper(args);
}
