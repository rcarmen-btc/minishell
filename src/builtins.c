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
