/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/22 04:27:22 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H
# include <stdlib.h>

typedef struct s_lst
{
	int				type;
	char			*value;
	char			**cmd;
	int				str_position;
	struct s_lst	*next;
}					t_lst;

// void	push(t_lst **head, int val);

void	push_back_tokenlst(t_lst **head, char *val, int type, int str_position);

void	push_back(t_lst **head, char *val, int type, int str_position);
// int		pop(t_lst **head);

// int		pop_back(t_lst **head);

// t_lst	*get_nth(t_lst *head, int n);

t_lst	*get_last(t_lst *head);

// t_lst	*get_sec_to_last(t_lst *head);

// size_t	get_lst_len(t_lst *head);

#endif