/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:38 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/19 13:37:51 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "main.h"

t_token	*init_token(int type, char *value, char lexer_c)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (type == TOKEN_CMD && (lexer_c == '\'' || lexer_c == '"'))
		token->e_str_position = ARG_IN_ONE_WITH_NEXT;
	else if ((type == TOKEN_DSTRING || type == TOKEN_SSTRING)
		&& (lexer_c == '\'' || lexer_c == '"' || ft_isalpha(lexer_c)))
		token->e_str_position = ARG_IN_ONE_WITH_NEXT;
	else
		token->e_str_position = ARG_ALONE;
	token->e_type = type;
	token->value = value;
	return (token);
}
