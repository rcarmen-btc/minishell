/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:30:55 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:40:16 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t				len;
	size_t				i;
	char				*mem;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
		return (NULL);
	while (*s1 != '\0')
		mem[i++] = *s1++;
	while (*s2 != '\0')
		mem[i++] = *s2++;
	mem[i] = '\0';
	return (mem);
}
