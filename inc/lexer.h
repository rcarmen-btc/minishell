/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:27:00 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/28 21:27:02 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"

typedef struct s_lexer
{
	unsigned int	i;
	char			c;
	char			*str;
}					t_lexer;

t_lexer *init_lexer(char *str);

void	lexer_advance(t_lexer *lexer);

void	lexer_skip_whitespace(t_lexer *lexer);

t_token *lexer_get_next_token(t_lexer *lexer);

t_token	*lexer_collect_string(t_lexer *lexer, char type);

t_token	*lexer_collect_id(t_lexer *lexer);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

char *lexer_get_current_char_as_string(t_lexer *lexer);

#endif