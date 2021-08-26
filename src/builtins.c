/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 21:32:32 by hdanyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtins(char **cmd)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo"))))
		builtin_echo(cmd);
	else if (!(ft_strncmp(cmd[0], "cd", ft_strlen("cd"))))
		builtin_cd(cmd[1]);
	else if (!(ft_strncmp(cmd[0], "pwd", ft_strlen("pwd"))))
		builtin_pwd();
	else if (!(ft_strncmp(cmd[0], "export", ft_strlen("export"))))
		builtin_export(cmd);
	else if (!(ft_strncmp(cmd[0], "unset", ft_strlen("unset"))))
		builtin_unset(cmd);
	else if (!(ft_strncmp(cmd[0], "env", ft_strlen("env"))))
		builtin_env();
	else if (!(ft_strncmp(cmd[0], "exit", ft_strlen("exit"))))
		builtin_exit(cmd);
}

void	builtin_echo(char **cmd)
{
	int	n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2) == 0)
	{
		n_flag = 1;
		i = 2;
	}
	while (cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}

void	builtin_cd(char *cmd)
{
	if (!cmd)
	{
		if(chdir(getenv("HOME")) == -1)
			perror(cmd);
	}
	else
		if(chdir(cmd) == -1)
			perror(cmd);
}

void	builtin_pwd()
{
	char buff[1024];

	if (getcwd(buff, sizeof(buff)) != NULL)
		printf("%s\n", buff);
    else
		perror("getcwd");
}

void	builtin_export(char **cmd)
{

}

void	builtin_unset(char **cmd)
{

}

void	builtin_env(void)
{

}

void	builtin_exit(char **cmd)
{

}
