/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 19:53:35 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/06 21:32:13 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int cmd_i;

int		is_id_or_sring(int token)
{
	if (token >= TOKEN_CMD && token <= TOKEN_IN_ONE_SSTRING)
		return (1);
	return (0);
}

void	collect_cmd_and_args(t_token *token, t_lexer **lexer, t_cmdlst **cmdlst)
{
	(*cmdlst)->type = TOKEN_EXEC_ARGS;
	(*cmdlst)->cmdline = ft_calloc(2, sizeof(char *));
	(*cmdlst)->cmdline[cmd_i] = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
	ft_strlcpy((*cmdlst)->cmdline[cmd_i], token->value, ft_strlen(token->value) + 1);
	while ((token = lexer_get_next_token(*lexer)) != (void *)0 && \
	is_id_or_sring(token->type))
	{
	    // printf("%d: %s\n", token->type, token->value);
		cmd_i++;
		(*cmdlst)->cmdline = ft_realloc((*cmdlst)->cmdline, cmd_i, (cmd_i + 2) * sizeof(char *));
		(*cmdlst)->cmdline[cmd_i] = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		ft_strlcpy((*cmdlst)->cmdline[cmd_i], token->value, ft_strlen(token->value) + 1);
		if (token)
		{
			free(token->value);
			free(token);
		}
	}
	cmd_i++;
	(*cmdlst)->cmdline[cmd_i] = NULL;
	// if (token != NULL)
	// 	printf("%d: %s\n", token->type, token->value);
	cmd_i = 0;
}

t_cmdlst	*get_last_cmdlst(t_cmdlst *cmdlst)
{
	while (cmdlst != NULL)
		cmdlst = cmdlst->next;
	return (cmdlst);
}

void	cmdlst_push_back(t_token *token, t_lexer **lexer, t_cmdlst **cmdlst)
{
	t_cmdlst	*tmp; 

	if (is_id_or_sring(token->type))
	{
		tmp = ft_calloc(1, sizeof(t_cmdlst));
		tmp->next = NULL;
		collect_cmd_and_args(token, lexer, &tmp);
		if (*cmdlst == NULL)
			*cmdlst = tmp;
		else
		{
			printf("%d\n",(get_last_cmdlst(*cmdlst)->type));
			get_last_cmdlst(*cmdlst)->next = tmp;
		}
	}
	if (token != NULL)
		printf("<>%d: %s\n", token->type, token->value);
	if (!is_id_or_sring(token->type))
	{
		tmp = ft_calloc(1, sizeof(t_cmdlst));
		tmp->next = NULL;
		tmp->cmdline = ft_calloc(1, sizeof(char *));
		tmp->cmdline[0] = ft_calloc(ft_strlen(token->value) + 1, sizeof(char));
		ft_strlcpy(tmp->cmdline[0], token->value, ft_strlen(token->value) + 1);
		tmp->type = token->type;
		if (*cmdlst == NULL)
			*cmdlst = tmp;
		else
			get_last_cmdlst(*cmdlst)->next = tmp;
	}
}

t_cmdlst	*init_cmdlst(char *line)
{
	t_lexer *lexer;
	t_token	*token;
	t_cmdlst *cmdlst;

	cmdlst = NULL;
	lexer = init_lexer(line);
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		cmd_i = 0;
		// printf("%d: %s\n", token->type, token->value);
		cmdlst_push_back(token, &lexer, &cmdlst);
		if (token)
		{
			free(token->value);
			free(token);
		}
	}
	free(lexer);
	return (cmdlst);
}