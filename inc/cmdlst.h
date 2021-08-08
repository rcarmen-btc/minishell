/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/07 20:38:53 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLST_H
# define CMDLST_H
# include "token.h"

typedef struct s_cmdlst
{
	int				type;
	char			**cmdline;
	struct s_cmdlst	*next;
}					t_cmdlst;

void	collect_cmd_and_args(t_lst **linelst, t_cmdlst **cmdlst);

void	cmdlst_push_back(t_lst **linelst, t_cmdlst **cmdlst);

void	init_cmdlst(t_lst *linelst, t_cmdlst **cmdlst);

#endif