/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:38 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/10 20:19:22 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "main.h"

t_token	*init_token(int type, char *value, char lexer_c)
{
	t_token *token = ft_calloc(1, sizeof(t_token));
	if (lexer_c != ' ' && lexer_c != '\0')
		token->arg_position = ARG_IN_ONE_WITH_NEXT;
	else
		token->arg_position = ARG_ALONE;
	token->type = type;
	token->value = value;
	return (token);
}