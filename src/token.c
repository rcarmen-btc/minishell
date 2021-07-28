/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:38 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/28 21:26:38 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "main.h"

t_token	*init_token(int type, char *value)
{
	t_token *token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}