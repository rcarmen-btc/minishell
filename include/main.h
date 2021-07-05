/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:23:20 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# define EXIT_SUCCESS 0;
# define EXIT_EXIT_FAILURE 1;
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
# include "libft.h"

typedef struct s_args
{
	char	*file1;
	char	**command1;
	char	**command2;
	char	*file2;
	char	*full_path1;
	char	*full_path2;
	char	*with_slash;
	char	*full_path;
	char	**tmp_path;
}			t_args;

void		error(char *output, int id, t_args *args);
void		free_and_exit(t_args *args, int id);
int			init_args(t_args *args, int ac, char **av);
char		*get_path_to_exe(char **ep, char *command, t_args *args);
char		*ft_strjoin_space(char const *s1, char const *s2);
char		*join_in_one_arr(char **args, int start, int end);
char		**join_in_qoutes(char **args, char *s, char **tmp1);
void		find_start_and_end(int *i, int *j, char **args);
int			is_exists_quotes(char *s);

#endif
