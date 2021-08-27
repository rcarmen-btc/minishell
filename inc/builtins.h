/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:46:19 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/27 15:36:44 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "main.h"

void	builtins(char **cmd, t_lst *pipelinelst);
void	builtin_echo(char **cmd, t_lst *pipelinelst);
void	builtin_cd(char *cmd);
void	builtin_pwd(void);
void	builtin_export(char **cmd);
void	builtin_unset(char **cmd);
void	builtin_env(void);
void	builtin_exit(char **cmd);

#endif
