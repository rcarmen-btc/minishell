/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 19:24:29 by hdanyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"
#include "../inc/builtins.h"

int		is_builtin_cmd(char **cmd)
{
	if (!(ft_strncmp(cmd[0], "echo", ft_strlen("echo")))
		|| !(ft_strncmp(cmd[0], "cd", ft_strlen("cd")))
		|| !(ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")))
		|| !(ft_strncmp(cmd[0], "export", ft_strlen("export")))
		|| !(ft_strncmp(cmd[0], "unset", ft_strlen("unset")))
		|| !(ft_strncmp(cmd[0], "env", ft_strlen("env")))
		|| !(ft_strncmp(cmd[0], "exit", ft_strlen("exit"))))
		return (1);
	return (-1);
}

void	cmd_without_pipes(char **cmd)
{
    pid_t pid;

	if (is_builtin_cmd(cmd) == 1)
	{
		builtins(cmd);
		return ;
	}
	pid = fork(); 
    if (pid == -1)
	{
		perror("fork");
        return;
    }
	else if (pid == 0)
	{
        if (execvp(cmd[0], cmd) < 0)
		{
        }
        exit(0);
    }
	else
	{
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}	

void	execute(t_lst *pipelinelst)
{
	if (get_lst_len(pipelinelst) == 1)
		cmd_without_pipes(pipelinelst->cmd);	
	
	// if (get_lst_len(pipelinelst) > 1)
		// cmd_with_pipes();	

	// builtin_pwd();
	// builtin_cd(pipelinelst->cmd);
}