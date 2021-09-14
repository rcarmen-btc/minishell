/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelinelst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 02:00:01 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/14 18:07:41 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		is_str_token(int type)
{
	if (type == TOKEN_DSTRING || type == TOKEN_SSTRING)
		return (1);
	return (0);
}

int		get_cmd_args_cnt(t_lst *tokenlst)
{
	int		cmd_args_cnt;
	
	cmd_args_cnt = 0;
	while (tokenlst && (tokenlst->type == TOKEN_CMD || is_str_token(tokenlst->type)))
	{
		if (tokenlst->str_position == 0)
		{
			cmd_args_cnt++;
			tokenlst = tokenlst->next;
		}
		else
			tokenlst = tokenlst->next;
	}
	return (cmd_args_cnt);	
}

void	get_pipelinelst(t_lst *tokenlst, t_lst **pipelinelst)
{
	t_lst	*pipeline_tmp;
	int		cmd_args_cnt;
	int		cmd_index;
	int	prev_pos;

	while (tokenlst != NULL)
	{
		pipeline_tmp = ft_calloc(1, sizeof(t_lst));
		if (tokenlst->type == TOKEN_CMD || is_str_token(tokenlst->type))
		{
			cmd_args_cnt = get_cmd_args_cnt(tokenlst);
			pipeline_tmp->cmd = ft_calloc(cmd_args_cnt + 1, sizeof(char *));
			pipeline_tmp->cmd[cmd_args_cnt] = NULL;
			pipeline_tmp->type = TOKEN_CMD_ARGS;
			cmd_index = 0;
			while (tokenlst != NULL && \
				(tokenlst->type == TOKEN_CMD || is_str_token(tokenlst->type)))
			{
				if (tokenlst->str_position == ARG_ALONE)
				{
					pipeline_tmp->cmd[cmd_index] = ft_strdup(tokenlst->value);
					cmd_index++;
					tokenlst = tokenlst->next;
				}
				else if (tokenlst->str_position == ARG_IN_ONE_WITH_NEXT)
				{
					pipeline_tmp->cmd[cmd_index] = ft_strdup(tokenlst->value);
					prev_pos = tokenlst->str_position;
					tokenlst = tokenlst->next;
					while (tokenlst != NULL && \
						is_str_token(tokenlst->type) && prev_pos == ARG_IN_ONE_WITH_NEXT)
					{
						prev_pos = tokenlst->str_position;
						pipeline_tmp->cmd[cmd_index] = ft_realloc(pipeline_tmp->cmd[cmd_index], 1, \
							ft_strlen(pipeline_tmp->cmd[cmd_index]) + ft_strlen(tokenlst->value) + 1);
						ft_strlcat(pipeline_tmp->cmd[cmd_index], tokenlst->value, ft_strlen(tokenlst->value) + ft_strlen(pipeline_tmp->cmd[cmd_index]) + 1);
						if (tokenlst->type == TOKEN_CMD || is_str_token(tokenlst->type))
							tokenlst = tokenlst->next;
					}
					cmd_index++;
				}
				// else if (tokenlst && (tokenlst->type == TOKEN_CMD || is_str_token(tokenlst->type)))
				// else if (tokenlst)
			}
			if (*pipelinelst == NULL)
				*pipelinelst = pipeline_tmp;
			else
				get_last(*pipelinelst)->next = pipeline_tmp;
		}
		if (tokenlst && (tokenlst->type != TOKEN_CMD || !is_str_token(tokenlst->type)))
			push_back(pipelinelst, tokenlst->value, tokenlst->type, tokenlst->str_position);
		if (tokenlst)
			tokenlst = tokenlst->next;
	}
}