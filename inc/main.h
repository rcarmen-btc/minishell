/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/21 01:13:15 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <math.h>
# include <term.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "libft.h"
# include "lexer.h"
# include "token.h"
# define MAXCOM 1024 

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

void	*ft_realloc(void *ptr, size_t origsize, size_t newsize);

void	get_tokenlst(char *line, t_lst **tokenlst);

int		ft_open_in(char *name, int type, int fd);

int		ft_open_out(char *name, int type);

int		is_str_token(int type);

int		get_cmd_args_cnt(t_lst *tokenlst);

void	add_env(t_env *env, char *key, char *value);

int		get_max_nbr(int first, int second);

void	get_pipelinelst(t_lst *tokenlst, t_lst **pipelinelst);

char	*env_array_find_key(char *ep);

char	*env_array_find_value(char *ep);

int		env_is_exists(t_env *env, char *key, char *value);

t_env	*find_last_env(t_env *head_env);

void	freeenv(t_env *env);

void	freelst(t_lst *tokenlst, t_lst *pipelinelst);

void	in_signals(void);

void	ex_signals(void);

void	error_message(char *str);

void	init_shell(void);

int		get_cmd_line_helper(char *line, char *str);

int		get_cmd_line(char *str, char *line);

void	freelst(t_lst *tokenlst, t_lst *pipelinelst);

char	*env_array_find_value(char *ep);

char	*env_array_find_key(char *ep);
t_env	*find_last_env(t_env *head_env);

void	init_env(char **ep, t_env **head_env);

void	create_outfiles(t_lst *pipelinelst);

int		check_the_dollar_and_get_cnt(char *str);
t_env	*get_el_env(t_env *env, char *key);

char	*get_str_befor(char *value, int *i);

char	*get_env_str_helper(char *res, t_env *tmp_env, char *doll);

void	get_env_str_helper_zero(char *value, int *tmp_i, int *cnt_doll);

void	get_env_str_helper_one(char *value, int *tmp_i, int *var_len);

char	*get_env_str(char *value, int *i, t_env *env, char *doll);

void	expand_env_vars_helper(char **res, t_lst *tokenlst, int *i, t_env *env);

void	expand_env_vars(t_lst *tokenlst, t_env *env, int i);

void	add_exit_code(t_env **head_env, int code);

void	error_message(char *str);

int		check_line_helper(char *line, int *i);

int		check_line(char *line);

void	freeenv(t_env *env);

void	print_tokenlst(t_lst *tokenlst);

void	print_pipelinelst(t_lst *pipelinelst);

int		loop(char *line, t_env *env, char **ep, t_lst *tokenlst);

#endif
