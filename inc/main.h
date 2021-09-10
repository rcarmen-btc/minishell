/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/10 02:16:39 by rcarmen          ###   ########.fr       */
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
# include "libft.h"
# include "lexer.h"
# include "token.h"
# define MAXCOM 1024 

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

void	*ft_realloc(void *ptr, size_t origsize ,size_t newsize);

void	get_tokenlst(char *line, t_lst **tokenlst);

int		is_str_token(int type);

int		get_cmd_args_cnt(t_lst *tokenlst);

void	get_pipelinelst(t_lst *tokenlst, t_lst **pipelinelst);

char	*env_array_find_key(char *ep);
char	*env_array_find_value(char *ep);
int		env_is_exists(t_env *env, char *key, char *value);
t_env	*find_last_env(t_env *head_env);

// сигналы
void	in_signals(void);
void	ex_signals(void);

#endif
