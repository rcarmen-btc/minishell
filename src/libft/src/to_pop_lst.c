/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 01:42:08 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pop(t_lst **head)
{
	t_lst	*prev;
	int		val;

	if (head == NULL)
		exit (1);
	if (*head == NULL)
		exit (1);
	prev = (*head);
	val = prev->val;
	(*head) = (*head)->next;
	free(prev);
	return (val);
}

int	pop_back(t_lst **head)
{
	t_lst	*sec_to_last;
	int		val;

	if (!head)
		exit (1);
	if (!(*head))
		exit (1);
	sec_to_last = get_sec_to_last(*head);
	if (sec_to_last == NULL)
	{
		val = (*head)->val;
		free(*head);
		*head = NULL;
		return (val);
	}
	else
	{
		val = sec_to_last->next->val;
		free(sec_to_last->next);
		sec_to_last->next = NULL;
		return (val);
	}
}
