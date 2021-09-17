/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:44:05 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 17:34:33 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	create_outfiles(t_lst *pipelinelst)
{
	int	fd;

	while (pipelinelst)
	{
		if (pipelinelst->type == TOKEN_RREDIR)
		{
			fd = open(pipelinelst->next->cmd[0], \
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
		}
		if (pipelinelst->type == TOKEN_APPRDIR)
		{
			fd = open(pipelinelst->next->cmd[0], \
			O_WRONLY | O_CREAT | O_APPEND, 0666);
			close(fd);
		}
		pipelinelst = pipelinelst->next;
	}
}

int	check_the_dollar_and_get_cnt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '$')
			return (1);
	return (0);
}

t_env	*get_el_env(t_env *env, char *key)
{
	int	klen;
	int	elen;
	int	max;

	klen = 0;
	elen = 0;
	while (env)
	{
		elen = ft_strlen(env->key);
		klen = ft_strlen(key);
		max = klen;
		if (elen > klen)
			max = elen;
		if (ft_strncmp(key, env->key, max) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	expand_env_vars_helper(char **res, t_lst *tokenlst, int *i, t_env *env)
{
	char	*env_str;
	char	*token_str;
	char	*tmp;

	token_str = get_str_befor(tokenlst->value, i);
	if (token_str)
	{
		tmp = *res;
		*res = ft_strjoin(*res, token_str);
		free(tmp);
		free(token_str);
	}
	env_str = get_env_str(tokenlst->value, i, env, NULL);
	if (env_str)
	{
		tmp = *res;
		*res = ft_strjoin(*res, env_str);
		free(tmp);
		free(env_str);
	}
}

void	expand_env_vars(t_lst *tokenlst, t_env *env, int i)
{
	char	*res;

	while (tokenlst)
	{
		if ((tokenlst->type == TOKEN_CMD || \
			tokenlst->type == TOKEN_DSTRING) && \
			check_the_dollar_and_get_cnt(tokenlst->value))
		{
			i = 0;
			res = ft_strnew(1);
			while (tokenlst->value[i])
			{
				expand_env_vars_helper(&res, tokenlst, &i, env);
			}
			free(tokenlst->value);
			tokenlst->value = res;
		}
		tokenlst = tokenlst->next;
	}
}
