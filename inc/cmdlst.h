/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/06 21:21:59 by rcarmen          ###   ########.fr       */
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

void	collect_cmd_and_args(t_token *token, t_lexer **lexer, t_cmdlst **cmdlst);

void	cmdlst_push_back(t_token *token, t_lexer **lexer, t_cmdlst **cmdlst);

t_cmdlst	*init_cmdlst(char *line);

#endif