/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_idk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:47:41 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/18 09:33:53 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*env_array_find_key(char *ep)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (ep[i] != '\0' && ep[i] != '=')
		i++;
	if (i > 0)
		key = ft_substr(ep, 0, i);
	return (key);
}

t_env	*find_last_env(t_env *head_env)
{
	while (head_env->next != NULL)
		head_env = head_env->next;
	return (head_env);
}

void	error_message(char *str)
{
	ft_putendl_fd(str, 2);
}

int	check_line_helper(char *line, int *i)
{
	int	dqoute;
	int	sqoute;

	dqoute = 1;
	sqoute = 1;
	if (line[*i] == '\'')
	{
		sqoute = sqoute * -1;
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '\'')
			(*i)++;
		if (line[*i] != '\'')
			return (1);
	}
	if (line[*i] == '"')
	{
		dqoute = dqoute * -1;
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '"')
			(*i)++;
		if (line[*i] != '"')
			return (1);
	}
	return (0);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_line_helper(line, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}
