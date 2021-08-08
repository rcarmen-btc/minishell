/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 19:53:35 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/08 20:19:43 by rcarmen          ###   ########.fr       */
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

void	collect_cmd_and_args(t_lst **linelst, t_cmdlst **cmdlst)
{
	(*cmdlst)->type = TOKEN_EXEC_ARGS;
	// (*cmdlst)->cmdline = ft_calloc(3, sizeof(char *));
	(*cmdlst)->cmdline = NULL;
	(*cmdlst)->cmdline[cmd_i] = ft_calloc(ft_strlen((*linelst)->value) + 1, sizeof(char));
	ft_strlcpy((*cmdlst)->cmdline[cmd_i], (*linelst)->value, ft_strlen((*linelst)->value) + 1);
	while (*linelst && \
	is_id_or_sring((*linelst)->type))
	{
		(*cmdlst)->cmdline = ft_realloc((*cmdlst)->cmdline, cmd_i, (cmd_i + 2) * sizeof(char *));
		(*cmdlst)->cmdline[cmd_i] = ft_calloc(ft_strlen((*linelst)->value) + 1, sizeof(char));
		ft_strlcpy((*cmdlst)->cmdline[cmd_i], (*linelst)->value, ft_strlen((*linelst)->value) + 1);
		*linelst = (*linelst)->next; 
		cmd_i++;
	}
	cmd_i++;
	(*cmdlst)->cmdline[cmd_i] = NULL;
	cmd_i = 0;
}

t_cmdlst	*get_last_cmdlst(t_cmdlst *cmdlst)
{
	t_cmdlst	*tmp;

	tmp = cmdlst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	cmdlst_push_back(t_lst **linelst, t_cmdlst **cmdlst)
{
	t_cmdlst	*tmp; 

	if (*linelst && is_id_or_sring((*linelst)->type))
	{
		tmp = ft_calloc(1, sizeof(t_cmdlst));
		tmp->next = NULL;
		cmd_i = 0;
		collect_cmd_and_args(linelst, &tmp);
		if (*cmdlst == NULL)
			*cmdlst = tmp;
		else
		{
			// printf("%d\n",(get_last_cmdlst(*cmdlst)->type));
			get_last_cmdlst(*cmdlst)->next = tmp;
		}
	}
	// if (*linelst) 
		// printf("%d: %s\n", (*linelst)->type, (*linelst)->value);
	if (*linelst && !is_id_or_sring((*linelst)->type))
	{
		tmp = ft_calloc(1, sizeof(t_cmdlst));
		tmp->next = NULL;
		tmp->cmdline = ft_calloc(1, sizeof(char *));
		tmp->cmdline[0] = ft_calloc(ft_strlen((*linelst)->value) + 1, sizeof(char));
		ft_strlcpy(tmp->cmdline[0], (*linelst)->value, ft_strlen((*linelst)->value) + 1);
		tmp->type = (*linelst)->type;
		if (*cmdlst == NULL)
			*cmdlst = tmp;
		else
			get_last_cmdlst(*cmdlst)->next = tmp;
	}
}

void	init_cmdlst(t_lst *linelst, t_cmdlst **cmdlst)
{
	while (linelst)
	{
		// printf("> %d: %s\n", linelst->type, linelst->value);
		cmdlst_push_back(&linelst, cmdlst);
		if (linelst)
			linelst = linelst->next;
	}
}