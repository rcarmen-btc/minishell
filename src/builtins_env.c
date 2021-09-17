/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 14:55:42 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_is_exists(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			free(env->value);
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	builtin_export(char **cmd, t_env *env)
{
	t_env	*env_tmp;
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (cmd[i])
	{
		key = env_array_find_key(cmd[i]);
		value = env_array_find_value(cmd[i]);
		if (!env_is_exists(env, key, value))
		{
			env_tmp = ft_calloc(1, sizeof(t_env));
			env_tmp->key = key;
			env_tmp->value = value;
			env_tmp->next = NULL;
			find_last_env(env)->next = env_tmp;
		}
		i++;
	}
	return (0);
}

void	env_find_and_del(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp && tmp->next && \
		ft_strncmp(key, tmp->next->key, ft_strlen(key)) != 0)
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

int	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		if (env->key[0] != '?')
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
