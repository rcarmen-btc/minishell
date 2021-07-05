/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:21:23 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
