/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:46:19 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/20 10:17:44 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "main.h"

int		builtins(char **cmd, t_env *env);

int		builtin_echo(char **cmd);

int		builtin_export_helper(char *key, char *value);

int		builtin_cd(char *cmd, t_env *env);

int		builtin_pwd(void);

int		builtin_export(char **cmd, t_env *env, int i);

int		builtin_unset(char **cmd, t_env *env);

int		builtin_env(t_env *env);

int		builtin_exit(char **cmd, t_env *env);

#endif
