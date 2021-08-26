/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:28:33 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 15:42:20 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "builtins.h"

int		is_builtin_cmd(char *name)
{
	char *builtins;
	char **builtins_split;
	int	i;

	builtins = "echo cd pwd export unset env exit";
	builtins_split = ft_split(builtins, ' ');
	i = 0;
	while (builtins_split[i] != NULL)
	{
		if (ft_strncmp(name, builtins_split[i], ft_strlen(name)) == 0)
			return (i);
		i++;
	}
	// TODO: free the builtins_split
	return (-1);
}

void	cmd_without_pipes(char **cmd)
{
	int res;
    pid_t pid; 

	res = is_builtin_cmd(cmd[0]); 
	if (res != -1)
	{
		builtins(res, cmd);
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