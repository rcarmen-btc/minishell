/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 01:57:46 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/19 13:21:35 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	get_tokenlst(char *line, t_lst **tokenlst)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer(line);
	token = lexer_get_next_token(lexer);
	while (token != NULL)
	{
		if (token->value == NULL)
		{
			token = lexer_get_next_token(lexer);
			if (token == NULL)
				break ;
			continue ;
		}
		push_back(tokenlst, token->value, token->e_type, token->e_str_position);
		free(token->value);
		free(token);
		token = lexer_get_next_token(lexer);
	}
	ft_bzero(line, MAXCOM);
	free(lexer);
}
