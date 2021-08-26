/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_push_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/26 11:21:10 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	push(t_lst **head, int val)
// {
// 	t_lst	*tmp;

// 	tmp = (t_lst *)malloc(sizeof(t_lst));
// 	tmp->val = val;
// 	tmp->next = (*head);
// 	(*head) = tmp;
// }


void	push_back_pipelinelst(t_lst **head, char *val, int type, int str_position)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	ft_memcpy(tmp->value, val, ft_strlen(val));
	tmp->type = type;
	tmp->str_position = str_position;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
		get_last(*head)->next = tmp;
}

void	push_back_tokenlst(t_lst **head, char *val, int type, int str_position)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	ft_memcpy(tmp->value, val, ft_strlen(val));
	tmp->str_position = str_position;
	tmp->type = type;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
		get_last(*head)->next = tmp;
}

void	push_back(t_lst **head, char *val, int type, int str_position)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	// tmp->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	tmp->value = ft_strdup(val);
	// ft_memcpy(tmp->value, val, ft_strlen(val));
	tmp->str_position = str_position;
	tmp->type = type;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
		get_last(*head)->next = tmp;
}
