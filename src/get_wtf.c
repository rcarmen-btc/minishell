/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wtf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:43:06 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:50:12 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_str_befor(char *value, int *i)
{
	int		len;
	int		j;
	char	*res;

	len = 0;
	j = *i;
	while (value[j] != '\0' && value[j] != '$')
	{
		len++;
		j++;
	}
	if (len == 0)
		return (NULL);
	res = ft_substr(value, *i, len);
	*i = j;
	return (res);
}

char	*get_env_str_helper(char *res, t_env *tmp_env, char *doll)
{
	if (tmp_env == NULL)
		return (doll);
	else
	{
		res = ft_strjoin(doll, tmp_env->value);
		free(doll);
	}
	return (res);
}

void	get_env_str_helper_zero(char *value, int *tmp_i, int *cnt_doll)
{
	while (value[*tmp_i] != '\0' && value[*tmp_i] == '$')
	{
		(*cnt_doll)++;
		(*tmp_i)++;
	}
}

void	get_env_str_helper_one(char *value, int *tmp_i, int *var_len)
{
	while (value[*tmp_i] && value[*tmp_i] != '$' && \
		!ft_isspace(value[*tmp_i]) && ft_isalnum(value[*tmp_i]))
	{
		(*var_len)++;
		(*tmp_i)++;
	}
}

char	*get_env_str(char *value, int *i, t_env *env, char *doll)
{
	int		doll_and_var_len[2];
	int		tmp_i;
	char	*res;
	char	*tmp;
	t_env	*tmp_env;

	doll_and_var_len[0] = 0;
	doll_and_var_len[1] = 0;
	tmp_i = *i;
	get_env_str_helper_zero(value, &tmp_i, &doll_and_var_len[0]);
	doll = ft_substr(value, *i, doll_and_var_len[0]);
	*i = tmp_i;
	get_env_str_helper_one(value, &tmp_i, &doll_and_var_len[1]);
	res = ft_substr(value, *i, doll_and_var_len[1]);
	if (doll_and_var_len[1] != 0)
		doll[ft_strlen(doll) - 1] = 0;
	*i = tmp_i;
	tmp = res;
	tmp_env = get_el_env(env, res);
	free(tmp);
	return (get_env_str_helper(res, tmp_env, doll));
}
