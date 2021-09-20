/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_wtf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:13:23 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/21 01:13:50 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "builtins.h"

int	ft_is_nbr(char *str)
{
	while (*str && !ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (0);
	return (1);
}

int	print_exenv(t_env *env)
{
	while (env != NULL)
	{
		if (env->key[0] != '?')
			printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_export(char **cmd, t_env *env, int i)
{
	char	*key;
	char	*value;

	while (cmd[i])
		i++;
	if (i == 1)
		return (print_exenv(env));
	i = 1;
	while (cmd[i])
	{
		key = env_array_find_key(cmd[i]);
		value = env_array_find_value(cmd[i]);
		if (key == NULL || ft_is_nbr(key))
			return (builtin_export_helper(key, value));
		else if (ft_strlen(value) == 0)
		{
			i++;
			continue ;
		}
		add_env(env, key, value);
		i++;
	}
	return (0);
}

void	env_find_and_del(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next && \
		ft_strncmp(key, tmp->next->key, \
		get_max_nbr(ft_strlen(key), ft_strlen(tmp->next->key))) != 0)
		tmp = tmp->next;
	if (tmp->next == NULL)
		return ;
	free(tmp->next->key);
	free(tmp->next->value);
	free(tmp->next);
	if (tmp->next->next == NULL)
		tmp->next = NULL;
	else
		tmp->next = tmp->next->next;
}

int	builtin_unset(char **cmd, t_env *env)
{
	int		i;
	char	*key;

	i = 1;
	while (cmd[i])
	{
		key = cmd[i];
		env_find_and_del(env, key);
		i++;
	}
	return (0);
}
