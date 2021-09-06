/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/06 10:18:55 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtins(char **cmd, t_lst *pipelinelst, t_env *env)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo"))))
		builtin_echo(cmd, pipelinelst);
	else if (!(ft_strncmp(cmd[0], "cd", ft_strlen("cd"))))
		builtin_cd(cmd[1]);
	else if (!(ft_strncmp(cmd[0], "pwd", ft_strlen("pwd"))))
		builtin_pwd();
	else if (!(ft_strncmp(cmd[0], "export", ft_strlen("export"))))
		builtin_export(cmd, env);
	else if (!(ft_strncmp(cmd[0], "unset", ft_strlen("unset"))))
		builtin_unset(cmd);
	else if (!(ft_strncmp(cmd[0], "env", ft_strlen("env"))))
		builtin_env(env);
	else if (!(ft_strncmp(cmd[0], "exit", ft_strlen("exit"))))
		builtin_exit(cmd);
}

void	builtin_echo(char **cmd, t_lst *pipelinelst)
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
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL) // если последняя команда не ставим пробел
			printf(" ");
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
	{
		// printf("%s\n", cmd);
		if(chdir(cmd) == -1)
			perror(cmd);
	}
}

void	builtin_pwd()
{
	char buff[1024];

	if (getcwd(buff, sizeof(buff)) != NULL)
		printf("%s\n", buff);
    else
		perror("getcwd");
}

void	builtin_export(char **cmd, t_env *env)
{
	t_env	*env_tmp;
	t_env	*tmp;
	char	*key;
	char	*value;
	
	tmp = env;
	key = env_array_find_key(cmd[1]);
	value = env_array_find_value(cmd[1]);

	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (ft_strncmp(tmp->value, value, ft_strlen(value)) != 0)
			{
				free(tmp->value);
				tmp->value = value;
				return (0);
			}
		}
		tmp = tmp->next;
	}
	env_tmp->key = key;
	env_tmp->value = value;
	find_last_env(env)->next = env_tmp;
}

void	builtin_unset(char **cmd)
{
	
}

void	builtin_env(t_env *env)
{
	int	i;
	
	i = 0;
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	builtin_exit(char **cmd)
{

}
