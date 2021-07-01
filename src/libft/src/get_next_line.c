/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 13:45:31 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/11 00:47:23 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ha_rem_li(ssize_t rs, char **line,
char **rema_pr_li, char *tmp)
{
	size_t			distance_to_n;

	distance_to_n = 0;
	if (rs < 0)
	{
		ft_memdel(rema_pr_li);
		return (-1);
	}
	else if (rs == 0)
	{
		*line = ft_strdup(*rema_pr_li);
		ft_memdel(rema_pr_li);
		return (0);
	}
	else if (rs > 0)
	{
		distance_to_n = ft_strchr(*rema_pr_li, '\n') - *rema_pr_li;
		*line = ft_substr(*rema_pr_li, 0, distance_to_n);
		distance_to_n += 1;
	}
	tmp = ft_strdup(*rema_pr_li + distance_to_n);
	ft_memdel(rema_pr_li);
	*rema_pr_li = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	ssize_t			rs;
	char			*tmp;
	char			*buf;
	static char		*remain_pre_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	rs = 1;
	tmp = NULL;
	if (NULL == remain_pre_line)
		remain_pre_line = ft_strnew(1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	rs = read(fd, buf, BUFFER_SIZE);
	while (ft_strchr(remain_pre_line, '\n') == 0 && rs > 0)
	{
		*(buf + rs) = '\0';
		tmp = ft_strjoin(remain_pre_line, buf);
		ft_memdel(&remain_pre_line);
		remain_pre_line = tmp;
	}
	ft_memdel(&buf);
	return (ft_ha_rem_li(rs, line, &remain_pre_line, tmp));
}
