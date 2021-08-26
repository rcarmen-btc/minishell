/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:36:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 15:40:13 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtins(int cmd_number, char **cmd)
{
	// if (cmd_number == 0)
	if (cmd_number == 1)
		builtin_cd(cmd);
	if (cmd_number == 2)
		builtin_pwd();
	// if (cmd_number == 3)
	// if (cmd_number == 4)
	// if (cmd_number == 5)
	// if (cmd_number == 6)
}

void	builtin_pwd()
{
	char buff[1024];
	if (getcwd(buff, sizeof(buff)) == NULL)
        perror("getcwd");
    else
        printf("%s\n", buff);
}

void	builtin_cd(char **cmd)
{
	chdir(cmd[1]);
}