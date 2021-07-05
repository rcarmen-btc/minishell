/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/05 13:24:11 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char 	**new_arr_args(char **args, char *qstr, int len)
{	
	char	**res;
	int		i;

	res = (char **)ft_calloc(sizeof(char **), len + 2);
	res[len + 1] = NULL;
	i = 0;
	while (i < len)
	{
		res[i] = ft_strdup(args[i]);
		i++;
	}
	res[i] = ft_strdup(qstr);
	return (res);
}

char	*ft_strjoin_space(char const *s1, char const *s2)
{
	size_t				len;
	size_t				i;
	char				*mem;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
		return (NULL);
	while (*s1 != '\0')
		mem[i++] = *s1++;
	mem[i++] = ' ';
	while (*s2 != '\0')
		mem[i++] = *s2++;
	mem[i] = '\0';
	return (mem);
}

char	*join_in_one_arr(char **args, int start, int end)
{
	char	*res;
	char	*tmp;

	res = ft_strjoin_space(args[start], args[start + 1]);
	start = start + 2;
	while (start <= end)
	{
		tmp = res;
		res = ft_strjoin_space(res, args[start]);
		free(tmp);
		start++;
	}
	return (res);
}

void	find_start_and_end(int *i, int *j, char **args)
{
	while (args[*i])
	{
		if (is_exists_quotes(args[*i]) && *j == 0)
			*j = *i;
		(*i)++;
	}
}

char	**join_in_qoutes(char **args, char *s, char **tmp1)
{
	int		i;
	int		j;
	char	*qstr;
	char	**all;
	char	*tmp;

	i = 0;
	j = 0;
	args = ft_split(s, ' ');
	find_start_and_end(&i, &j, args);
	qstr = join_in_one_arr(args, j, i - 1);
	tmp = qstr;
	if (qstr[0] == '"')
		qstr = ft_strtrim(qstr, "\"");
	else
		qstr = ft_strtrim(qstr, "'");
	free(tmp);
	all = new_arr_args(args, qstr, j);
	tmp1 = args;
	while (*args)
		free(*args++);
	free(tmp1);
	free(qstr);
	return (all);
}
