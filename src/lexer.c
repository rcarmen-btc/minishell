/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:25:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:31:25 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "main.h"

int	is_reserved_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"')
		return (1);
	return (0);
}

t_lexer	*init_lexer(char *str)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->str = str;
	lexer->i = 0;
	lexer->c = str[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->str))
	{
		lexer->i++;
		lexer->c = lexer->str[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	if (lexer->c == ' ' || lexer->c == 10)
		while (lexer->c == ' ' || lexer->c == 10)
			lexer_advance(lexer);
}

t_token	*lexer_rredir(t_lexer *lexer)
{
	if (lexer->str[lexer->i + 1] == '>' && \
		(lexer->i == 0 || lexer->str[lexer->i - 1] != '>'))
	{
		lexer_advance(lexer);
		return (lexer_advance_with_token(lexer, \
		init_token(TOKEN_APPRDIR, ft_strdup(">>"), lexer->c, lexer)));
	}
	else
		return (lexer_advance_with_token(lexer, \
		init_token(TOKEN_RREDIR, \
		lexer_get_current_char_as_string(lexer), lexer->c, lexer)));
}
