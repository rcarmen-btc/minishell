/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/20 19:44:33 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins(char **cmd, t_env *env)
{
	if (!(ft_strncmp(cmd[0], "echo", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("echo")))))
		return (builtin_echo(cmd));
	else if (!(ft_strncmp(cmd[0], "cd", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("cd")))))
		return (builtin_cd(cmd[1], env));
	else if (!(ft_strncmp(cmd[0], "pwd", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("pwd")))))
		return (builtin_pwd());
	else if (!(ft_strncmp(cmd[0], "export", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("export")))))
		return (builtin_export(cmd, env, 1));
	else if (!(ft_strncmp(cmd[0], "unset", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("unset")))))
		return (builtin_unset(cmd, env));
	else if (!(ft_strncmp(cmd[0], "env", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("env")))))
		return (builtin_env(env));
	else if (!(ft_strncmp(cmd[0], "exit", get_max_nbr(ft_strlen(cmd[0]), \
		ft_strlen("exit")))))
		return (builtin_exit(cmd, env));
	return (0);
}

static void	parse_first_arg(char *arg)
{
	char	status;

	if (!arg)
		return ;
	status = (char)ft_atoi(arg);
	while (*arg)
	{
		if (!ft_isdigit(*arg++))
		{
			printf("minishell: exit: %s: numeric argument required\n", --arg);
			exit(2);
		}
	}
	exit(status);
}

int	builtin_exit(char **cmd, t_env *env)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 1;
	printf("exit\n");
	while (cmd[i])
	{
		cnt++;
		i++;
	}
	if (cnt == 1)
		parse_first_arg(cmd[1]);
	else if (cnt > 1)
	{
		error_message("exit: too many arguments");
		return (1);
	}
	while (env != NULL)
	{
		if (env->key[0] == '?')
			exit(ft_atoi(env->value));
		env = env->next;
	}
	exit(0);
}

int	builtin_echo(char **cmd)
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
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
