/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/20 10:16:59 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_is_exists(t_env *env, char *key, char *value)
{
	int	key_len;

	while (env)
	{
		key_len = ft_strlen(key);
		if (ft_strlen(env->key) > ft_strlen(key))
			key_len = ft_strlen(env->key);
		if (ft_strncmp(env->key, key, key_len) == 0)
		{
			free(env->value);
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	builtin_export_helper(char *key, char *value)
{
	if (key == NULL)
		printf("minishell: export: '=%s': not a valid identifier\n", value);
	else
		printf("minishell: export: '%s': not a valid identifier\n", key);
	if (key)
		free(key);
	if (value)
		free(value);
	return (1);
}

void	add_env(t_env *env, char *key, char *value)
{
	t_env	*env_tmp;

	if (!env_is_exists(env, key, value))
	{
		env_tmp = ft_calloc(1, sizeof(t_env));
		env_tmp->key = key;
		env_tmp->value = value;
		env_tmp->next = NULL;
		find_last_env(env)->next = env_tmp;
	}
}
