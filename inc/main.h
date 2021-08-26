/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 14:29:45 by rcarmen          ###   ########.fr       */
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
# define MAXCOM 1024 

void	*ft_realloc(void *ptr, size_t origsize ,size_t newsize);

void	get_tokenlst(char *line, t_lst **tokenlst);

int		is_str_token(int type);

int		get_cmd_args_cnt(t_lst *tokenlst);

void	get_pipelinelst(t_lst *tokenlst, t_lst **pipelinelst);

// сигналы
void	in_signals(void);
void	ex_signals(void);

#endif
