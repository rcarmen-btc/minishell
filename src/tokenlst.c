/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 01:57:46 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/13 01:58:07 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_tokenlst(char *line, t_lst **tokenlst)
{
	t_lexer *lexer;
	t_token	*token;

	lexer = init_lexer(line);
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		push_back(tokenlst, token->value, token->type, token->arg_position);
		if (token)
		{
			free(token->value);
			free(token);
		}
	}
	free(lexer);
}