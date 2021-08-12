/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/12 14:34:08 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>

void *ft_realloc(void *ptr, size_t origsize, size_t newsize)
{
	void	*ptrNew; 

	if (newsize == 0)
	{
		free(ptr);
		return NULL;
	}
	else if (!ptr)
	{
		return ft_calloc(newsize, sizeof(char));
	}
	else if (newsize <= origsize)
	{
		return ptr;
	}
	else
	{
		ptrNew = ft_calloc(newsize, sizeof(char));
		if (ptrNew)
		{
			ft_memmove(ptrNew, ptr, newsize);
			// memmove(ptrNew, ptr, newsize);
			// ft_bcopy(ptr, ptrNew, newsize);
			free(ptr);
		}
		return ptrNew;
	}
}

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

// void	collect_cmd_and_args(t_lst **tokenlst, t_lst **pipelinelst)
// {
// 	t_lst	*pipeline_tmp;
// 	t_lst	*token_tmp;
// 	int		arg_cout;
// 	int		i;
// 	int		prev_type;

// 	pipeline_tmp = *pipelinelst;
// 	token_tmp = *tokenlst;
// 	while (token_tmp && \
// 		(token_tmp->type == TOKEN_CMD || \
// 		token_tmp->type == TOKEN_DSTRING || \
// 		token_tmp->type == TOKEN_SSTRING))
// 	{
// 		if (token_tmp->arg_position == 1) 
// 			token_tmp = token_tmp->next;
// 		else
// 			arg_cout++;
// 		token_tmp = token_tmp->next;
// 	}
// 	pipeline_tmp = ft_calloc(1, sizeof(t_lst));
// 	pipeline_tmp->cmd = ft_calloc(arg_cout + 1, sizeof(char *));
// 	pipeline_tmp->value = "";
// 	pipeline_tmp->type = TOKEN_CMD_ARGS;
// 	pipeline_tmp->next = NULL;
// 	while (*tokenlst && \
// 	((*tokenlst)->type == TOKEN_CMD || \
// 	(*tokenlst)->type == TOKEN_DSTRING || (*tokenlst)->type == TOKEN_SSTRING))
// 	{
// 		arg_cout = 0;
// 		i = 0;
// 		while (*tokenlst && (((((*tokenlst)->type == TOKEN_DSTRING) || \
// 			((*tokenlst)->type == TOKEN_SSTRING)) && \
// 			(*tokenlst)->arg_position == ARG_ALONE) || (*tokenlst)->type == TOKEN_CMD)) 
// 		{
// 			pipeline_tmp->cmd[i] = ft_strdup((*tokenlst)->value);
// 			*tokenlst = (*tokenlst)->next;
// 			i++;
// 		}	
// 		while (*tokenlst && ((*tokenlst)->type == TOKEN_DSTRING || \
// 			(*tokenlst)->type == TOKEN_SSTRING) && \
// 			(*tokenlst)->arg_position == ARG_IN_ONE_WITH_NEXT)
// 		{
// 			pipeline_tmp->cmd[i] = ft_realloc(pipeline_tmp->cmd[i], ft_strlen(pipeline_tmp->value) + 1, \
// 				ft_strlen(pipeline_tmp->value) + ft_strlen((*tokenlst)->value) + 1);
// 			ft_strlcat(pipeline_tmp->cmd[i], (*tokenlst)->value, ft_strlen(pipeline_tmp->cmd[i]) + ft_strlen((*tokenlst)->value) + 1);
// 			*tokenlst = (*tokenlst)->next;
// 		}
// 	}
// 	if (*pipelinelst == NULL)
// 		*pipelinelst = pipeline_tmp;
// 	else
// 		get_last(*pipelinelst)->next = pipeline_tmp;
// 	// if (*tokenlst)
// 	// 	(*tokenlst) = (*tokenlst)->next;
// 	// printf("%s\n", (*tokenlst)->value);
// }

// void	get_pipelinelst(t_lst *tokenlst, t_lst **pipelinelst)
// {
// 	while (tokenlst)
// 	{
// 		if (tokenlst->type == TOKEN_CMD || tokenlst->type == TOKEN_DSTRING || tokenlst->type == TOKEN_IN_ONE_DSTRING)
// 			collect_cmd_and_args(&tokenlst, pipelinelst);
// 		else
// 		{
// 			printf("--->%d: %s %d\n", tokenlst->type, tokenlst->value, tokenlst->arg_position);
// 			push_back(pipelinelst, tokenlst->value, tokenlst->type, tokenlst->arg_position);
// 			if (tokenlst)
// 				tokenlst = tokenlst->next;
// 		}
// 	}
// }

int	main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*tokenlst;
	t_lst		*pipelinelst;

	while (1)
	{
		tokenlst = NULL;
		pipelinelst = NULL;
		printf("\033[0;32m"); 
		line = readline("chillyshell$ \033[0m");
		// printf("\033[0m");
		get_tokenlst(line, &tokenlst);
		
		// get_pipelinelst(tokenlst, &pipelinelst);
		while (pipelinelst)
		{	
			int	i = 0;
			while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
			{
				printf("%s\n", pipelinelst->cmd[i]);

				i++;
			}
			if (pipelinelst->type != TOKEN_CMD_ARGS)
				printf("\n+%s\n", pipelinelst->value);
			pipelinelst = pipelinelst->next;
		}
		
		// while (tokenlst)
		// {
		// 	printf("%d: %s %d\n", tokenlst->type, tokenlst->value, tokenlst->arg_position);
		// 	tokenlst = tokenlst->next;
		// }
		add_history(line);
	}	
}
