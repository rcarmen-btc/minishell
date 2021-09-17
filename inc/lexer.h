/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:27:00 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 17:35:18 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "token.h"
# include "main.h"

typedef struct s_lexer
{
	unsigned int	i;
	char			c;
	char			*str;
}					t_lexer;

t_lexer	*init_lexer(char *str);

void	lexer_advance(t_lexer *lexer);

void	lexer_skip_whitespace(t_lexer *lexer);

t_token	*lexer_get_next_token(t_lexer *lexer);

t_token	*lexer_collect_string(t_lexer *lexer, char type);

t_token	*lexer_collect_cmd(t_lexer *lexer);

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token);

char	*lexer_get_current_char_as_string(t_lexer *lexer);

t_token	*init_token(int type, char *value, char lexer_c);

int		is_reserved_symbol(char c);

t_token	*lexer_rredir(t_lexer *lexer);

t_token	*lexer_lredir(t_lexer *lexer);

t_token	*return_based_on_type(char type, char in_one, \
char *value, t_lexer *lexer);

#endif