/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/10 13:40:39 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins(char **cmd, t_lst *pipelinelst, t_env *env)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo"))))
		return (builtin_echo(cmd, pipelinelst));
	else if (!(ft_strncmp(cmd[0], "cd", ft_strlen("cd"))))
		return (builtin_cd(cmd[1]));
	else if (!(ft_strncmp(cmd[0], "pwd", ft_strlen("pwd"))))
		return (builtin_pwd());
	else if (!(ft_strncmp(cmd[0], "export", ft_strlen("export"))))
		return (builtin_export(cmd, env));
	else if (!(ft_strncmp(cmd[0], "unset", ft_strlen("unset"))))
		return (builtin_unset(cmd, env));
	else if (!(ft_strncmp(cmd[0], "env", ft_strlen("env"))))
		return (builtin_env(env));
	else if (!(ft_strncmp(cmd[0], "exit", ft_strlen("exit"))))
		return (builtin_exit(cmd));
	return (0);
}

int	builtin_echo(char **cmd, t_lst *pipelinelst)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		n_flag = 1;
		i = 2;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) // если последняя команда не ставим пробел
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int	builtin_cd(char *cmd)
{
	if(!cmd)
	{
		if(chdir(getenv("HOME")) == -1)
		{
			perror(cmd);
			return (1);
		}
	}
	else if (chdir(cmd) == -1)
	{
		perror(cmd);
		return (1);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	buff[1024];

	if (getcwd(buff, sizeof(buff)) != NULL)
		printf("%s\n", buff);
	else
		perror("getcwd");
	return (0);
}

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
	while (tmp && tmp->next && ft_strncmp(key, tmp->next->key, ft_strlen(key)) != 0)
		tmp = tmp->next;
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

static void	parse_first_arg(char *arg)
{
	int	status;

	if (!arg)
		return ;
	status = ft_atoi(arg);
	while (*arg)
		if (ft_isdigit(*arg++))
			return ;
	error_message("exit: numeric argument required");
	exit(status);
}

int	builtin_exit(char **cmd)
{
	int	status;

	status = 1;
	while (cmd[status])
		status++;
	parse_first_arg(*(cmd + 1));
	if (status > 2)
	{
		error_message("exit: too many arguments");
		return (1);
	}
	printf("exit\n");
	exit(status);
}
