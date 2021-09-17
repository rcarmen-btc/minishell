/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:49:27 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:51:34 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	freeenv(t_env *env)
{
	t_env	*tmpenv;

	while (env)
	{
		tmpenv = env->next;
		free(env->value);
		free(env->key);
		free(env);
		env = tmpenv;
	}
}

void	print_tokenlst(t_lst *tokenlst)
{
	while (tokenlst)
	{
		printf("%s - %d - %d\n", tokenlst->value, tokenlst->type, \
		tokenlst->str_position);
		tokenlst = tokenlst->next;
	}
}

void	print_pipelinelst(t_lst *pipelinelst)
{
	int	i;

	while (pipelinelst)
	{	
		i = 0;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			printf("[%s | %d] ", pipelinelst->cmd[i], i);
			i++;
		}
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			printf("(%s)", pipelinelst->value);
		printf("\n");
		pipelinelst = pipelinelst->next;
	}
}
