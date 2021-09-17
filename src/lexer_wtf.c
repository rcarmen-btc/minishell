/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_wtf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:25:35 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:50:25 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer_collect_string(t_lexer *lexer, char type)
{
	char	*value;
	char	*s;
	char	in_one;
	int		len_val;

	in_one = lexer->str[lexer->i];
	lexer_advance(lexer);
	value = NULL;
	len_val = 0;
	while (lexer->c != type)
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, len_val, \
		(len_val + ft_strlen(s) + 1) * sizeof(char));
		ft_strlcat(value, s, ft_strlen(value) + ft_strlen(s) + 1);
		len_val = ft_strlen(value) + ft_strlen(s) + 1;
		free(s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (return_based_on_type(type, in_one, value, lexer));
}

t_token	*lexer_collect_cmd(t_lexer *lexer)
{
	char	*value;
	int		len_val;
	char	*s;

	value = NULL;
	len_val = 0;
	while (ft_isprint(lexer->c) && !ft_isspace(lexer->c) && \
	!is_reserved_symbol(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, len_val, \
		(len_val + ft_strlen(s) + 1) * sizeof(char));
		len_val = ft_strlen(value) + ft_strlen(s);
		ft_strlcat(value, s, ft_strlen(value) + ft_strlen(s) + 1);
		free(s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_CMD, value, lexer->c, lexer));
}

t_token	*lexer_advance_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	*lexer_get_current_char_as_string(t_lexer *lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}
