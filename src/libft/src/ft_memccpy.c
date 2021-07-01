/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:30:25 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:32:09 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*d_tmp;
	size_t	i;

	i = 0;
	d_tmp = dest;
	while (i < n)
	{
		*(d_tmp + i) = *((unsigned char *)src + i);
		if (*(d_tmp + i) == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
