/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:31:24 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:43:07 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_head(char const *str, char const *set)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (str[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static size_t	get_tail(char const *str, char const *set)
{
	size_t		i;
	size_t		j;

	i = ft_strlen(str) - 1;
	j = 0;
	while (set[j])
	{
		if (str[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		head;
	size_t		tail;
	char		*new_str;

	head = get_head(s1, set);
	if (head == ft_strlen(s1))
		return ((char *)malloc(sizeof(char) * 1));
	tail = get_tail(s1, set);
	new_str = (char *)malloc(sizeof(char) * (tail - head + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (head <= tail)
		new_str[i++] = s1[head++];
	new_str[i] = '\0';
	return (new_str);
}
