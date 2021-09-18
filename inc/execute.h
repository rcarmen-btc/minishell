/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:29:36 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/18 12:19:30 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "main.h"
# include "builtins.h"

int		is_builtin_cmd(char **cmd);

char	*get_infile_name(t_lst *pipelinelst);

char	*get_outfile_name(t_lst *pipelinelst);

int		is_exists_pipe(t_lst *pipelinelst);

int		handle_heredoc(t_lst *pipelinelst);

char	*get_path_to_exe_heplper(char **path, char *command);

int		get_slash_cnt(char *name);

char	*get_path_to_exe(t_env *env, char *name);

int		check_next(t_lst *pipelinelst, int lvl);

int		is_out_redir(t_lst *pipelinelst, int lvl);

int		is_in_redir(t_lst *pipelinelst, int lvl);

void	out_redir_fd_find(t_lst *pipelinelst, int *fd, char **in_out_files);

void	in_redir_fd_find(t_lst *pipelinelst, int *fd);

void	time_to_execute_the_command(t_lst *pipelinelst, t_env *env, char **ep);

void	set_out_and_in(int *fd);

t_lst	*redirections_handling_helper(t_lst **pipelinelst, int *fd, \
char **in_out_files);

int		redirections_handling(t_lst **pipelinelst, char **ep, \
t_env *env, int pd[2]);

int		check_next_is_rdir(t_lst *pipelinelst);

int		last_builtin_cmd(t_lst *pipelinelst, int tmpin, int tmpout, t_env *env);

int		skip_pipes_and_rdirs(t_lst **pipelinelst, char **ep, t_env *env, \
int *pd);

int		check_builtins(t_lst *pipelinelst);

int		execute(t_lst *pipelinelst, t_env *env, char **ep);

#endif