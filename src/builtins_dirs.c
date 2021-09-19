/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/19 16:33:49 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"

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

int	ft_open_in(char *name, int type, int fd)
{
	int resfd;

	resfd = open(name, type);
	if (resfd == -1)
		perror(name);
	close(fd);
	return (resfd);
}

int	ft_open_out(char *name, int type, int fd)
{
	int resfd;

	resfd = open(name, type, 0666);
	if (resfd == -1)
		perror(name);
	close(fd);
	return (resfd);
}




