/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:25:50 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/22 18:10:24 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "main.h"

int	is_reserved_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return(0);
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
		{
			lexer_advance(lexer);
		}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && \
		lexer->i < ft_strlen(lexer->str))
	{
		lexer_skip_whitespace(lexer); //пропускаем пробелы и табы
		if (lexer->c == '"' || lexer->c == '\'') //если на данный момент мы находимся на символе " или '
			return (lexer_collect_string(lexer, lexer->c));
		if (ft_isprint(lexer->c) && !ft_isspace(lexer->c) && \
		!is_reserved_symbol(lexer->c))
			return (lexer_collect_cmd(lexer));
		if (lexer->c == '|') //находим пайпы и возвращаем 
			return (lexer_advance_with_token(lexer, \
			init_token(TOKEN_PIPE, \
			lexer_get_current_char_as_string(lexer), lexer->c)));
		if (lexer->c == '>')
		{
			if (lexer->str[lexer->i + 1] == '>' && \
				lexer->str[lexer->i - 1] != '>')
			{
				lexer_advance(lexer);
				return (lexer_advance_with_token(lexer, \
				init_token(TOKEN_APPRDIR, ft_strdup(">>"), lexer->c)));
			}
			else
				return (lexer_advance_with_token(lexer, \
				init_token(TOKEN_RREDIR, \
				lexer_get_current_char_as_string(lexer), lexer->c)));
		}
		if (lexer->c == '<')
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
				lexer_get_current_char_as_string(lexer),  lexer->c)));
		}
		lexer_advance(lexer);
	}
	return (NULL);
}

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

t_token	*lexer_collect_cmd(t_lexer *lexer)
{
	char	*value;
	int		len_val;
	char	*s;

	// value = ft_calloc(1, sizeof(char *));
	value = NULL;
	len_val = 1;
	while (ft_isalnum(lexer->c) && !ft_isspace(lexer->c) && \
	!is_reserved_symbol(lexer->c))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, len_val, \
		(len_val + ft_strlen(s) + 1) * sizeof(char));
		len_val = ft_strlen(value) + ft_strlen(s) + 1;
		ft_strlcat(value, s, ft_strlen(value) + ft_strlen(s) + 1);
		free(s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_CMD, value, 0));
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
