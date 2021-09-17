/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:05:47 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cd_helper(t_env *env)
{
	char	*buff;

	buff = ft_calloc(MAXCOM, sizeof(char));
	getcwd(buff, MAXCOM);
	env_is_exists(env, "PWD", buff);
	return (0);
}

int	builtin_cd(char *cmd, t_env *env)
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
	else
		cd_helper(env);
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
