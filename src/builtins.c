/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 17:33:44 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtins(char **cmd, t_env *env)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo"))))
		return (builtin_echo(cmd));
	else if (!(ft_strncmp(cmd[0], "cd", ft_strlen("cd"))))
		return (builtin_cd(cmd[1], env));
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
