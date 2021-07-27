/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/25 13:17:04 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	push(t_lst **head, int val)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->val = val;
	tmp->next = (*head);
	(*head) = tmp;
}

void	push_back(t_lst **head, int val)
{
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	tmp->val = val;
	tmp->next = NULL;
	if (*head == NULL)
		*head = tmp;
	else
		get_last(*head)->next = tmp;
}
