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
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int	builtin_cd(char *cmd)
{
	if (!cmd)
	{
		if (chdir(getenv("HOME")) == -1)
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
