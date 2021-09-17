/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ijk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:31:03 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 17:40:53 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer_lredir(t_lexer *lexer)
{
	if (lexer->str[lexer->i + 1] == '<' && \
		lexer->str[lexer->i - 1] != '<')
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer, \
		init_token(TOKEN_HERE_DOC, ft_strdup("<<"), lexer->c)));
	}
	else
		return (lexer_advance_with_token(lexer, \
		init_token(TOKEN_LREDIR, \
		lexer_get_current_char_as_string(lexer), lexer->c)));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && \
		lexer->i < ft_strlen(lexer->str))
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '"' || lexer->c == '\'')
			return (lexer_collect_string(lexer, lexer->c));
		else if (ft_isprint(lexer->c) && !ft_isspace(lexer->c) && \
		!is_reserved_symbol(lexer->c))
			return (lexer_collect_cmd(lexer));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, \
			init_token(TOKEN_PIPE, \
			lexer_get_current_char_as_string(lexer), lexer->c)));
		else if (lexer->c == '>')
			return (lexer_rredir(lexer));
		else if (lexer->c == '<')
			return (lexer_lredir(lexer));
	}
	return (NULL);
}

t_token	*return_based_on_type(char type, char in_one, \
char *value, t_lexer *lexer)
{
	if (type == '"' && in_one != '"' && in_one != '\'')
		return (init_token(TOKEN_DSTRING, value, lexer->c));
	else if (type == '\'' && in_one != '"' && in_one != '\'')
		return (init_token(TOKEN_SSTRING, value, lexer->c));
	else if (type == '"' && (in_one == '"' || in_one == '\''))
		return (init_token(TOKEN_DSTRING, value, lexer->c));
	else if (type == '\'' && (in_one == '"' || in_one == '\''))
		return (init_token(TOKEN_SSTRING, value, lexer->c));
	else
		return (init_token(TOKEN_NULL, value, lexer->c));
}
