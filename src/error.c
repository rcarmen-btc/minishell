/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:20:45 by rcarmen          ###   ########.fr       */
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
