/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:51:57 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:31:14 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmplst;
	t_list	*new;

	if (!lst || !f)
		return (NULL);
	tmplst = ft_lstnew(f(lst->content));
	if (!tmplst)
		return (NULL);
	new = tmplst;
	lst = lst->next;
	while (lst != NULL)
	{
		tmplst = ft_lstnew(f(lst->content));
		if (!tmplst)
			ft_lstclear(&new, del);
		lst = lst->next;
		ft_lstadd_back(&new, tmplst);
	}
	return (new);
}
