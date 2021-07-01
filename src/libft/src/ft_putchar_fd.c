/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:23:54 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:33:25 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_utf_4(int unicode, int fd)
{
	int				ws;
	unsigned char	buf;

	buf = (unicode >> 18 & 7) | 240;
	ws = write(fd, &buf, 1);
	buf = (unicode >> 12 & 63) | 128;
	ws = write(fd, &buf, 1);
	buf = (unicode >> 6 & 63) | 128;
	ws = write(fd, &buf, 1);
	buf = (unicode & 63) | 128;
	ws = write(fd, &buf, 1);
	(void)ws;
}

static void	ft_utf_3(int unicode, int fd)
{
	int				ws;
	unsigned char	buf;

	buf = (unicode >> 12 & 15) | 224;
	ws = write(fd, &buf, 1);
	buf = (unicode >> 6 & 63) | 128;
	ws = write(fd, &buf, 1);
	buf = (unicode & 63) | 128;
	ws = write(fd, &buf, 1);
	(void)ws;
}

static void	ft_utf_2(int unicode, int fd)
{
	int				ws;
	unsigned char	buf;

	buf = unicode >> 6 | 192;
	ws = write(fd, &buf, 1);
	buf = (unicode & 63) | 128;
	ws = write(fd, &buf, 1);
	(void)ws;
}

static void	ft_utf_1(char unicode, int fd)
{
	int				ws;

	ws = write(fd, &unicode, 1);
	(void)ws;
}

void	ft_putchar_fd(int unicode, int fd)
{
	int				ws;

	if ((unicode | UTF8_1) == UTF8_1)
		ft_utf_1(unicode, fd);
	else if ((unicode | UTF8_2) == UTF8_2)
		ft_utf_2(unicode, fd);
	else if ((unicode | UTF8_3) == UTF8_3)
		ft_utf_3(unicode, fd);
	else if ((unicode | UTF8_4) == UTF8_4)
		ft_utf_4(unicode, fd);
	else
		ws = write(fd, &unicode, 1);
	(void)ws;
}
