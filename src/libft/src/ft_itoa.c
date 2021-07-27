/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:49:01 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:27:56 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nbr_cnt(int n)
{
	size_t	nbr_cnt;

	if (n == 0)
		return (1);
	nbr_cnt = 0;
	if (n < 0)
		nbr_cnt++;
	while (n != 0)
	{
		nbr_cnt++;
		n /= 10;
	}
	return (nbr_cnt);
}

char	*ft_itoa(int n)
{
	size_t		nbr_cnt;
	char		*nbr_str;
	long		tmp_n;

	nbr_cnt = get_nbr_cnt(n);
	tmp_n = n;
	nbr_str = ft_strnew(nbr_cnt + 1);
	if (tmp_n < 0)
	{
		nbr_str[0] = '-';
		tmp_n = -tmp_n;
	}
	else if (tmp_n == 0)
		nbr_str[0] = '0';
	while (tmp_n > 0)
	{
		nbr_str[--nbr_cnt] = '0' + tmp_n % 10;
		tmp_n /= 10;
	}
	return (nbr_str);
}
