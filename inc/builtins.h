/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:46:19 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/10 01:55:34 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "main.h"

int		builtins(char **cmd, t_lst *pipelinelst, t_env *env);
int		builtin_echo(char **cmd, t_lst *pipelinelst);
int		builtin_cd(char *cmd);
int		builtin_pwd(void);
int		builtin_export(char **cmd, t_env *env);
int		builtin_unset(char **cmd, t_env *env);
int		builtin_env(t_env *env);
int		builtin_exit(char **cmd);

#endif
