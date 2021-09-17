/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 14:56:32 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execute.h"
#include <stddef.h>

void	*ft_realloc(void *ptr, size_t origsize, size_t newsize)
{
	void	*ptrNew;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (ft_calloc(newsize, sizeof(char)));
	else if (newsize <= origsize)
		return (ptr);
	else
	{
		ptrNew = ft_calloc(newsize, sizeof(char));
		if (ptrNew && ptr != NULL)
		{
			ft_strlcpy(ptrNew, ptr, newsize);
			free(ptr);
		}
		return (ptrNew);
	}
}

void	init_shell(void)
{
	int		fd;
	char	*line;

	printf("\033[2J");
	fd = open("greeting_art.txt", O_RDONLY);
	if (fd != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			printf("%s\n", line);
			free(line);
		}
		printf("%s", line);
		free(line);
	}
	printf("\n");
}

int	get_cmd_line_helper(char *line, char *str)
{
	if (line == NULL)
	{
		printf("exit\n");
		rl_clear_history();
		return (1);
	}
	else if (strlen(line) != 0)
	{
		add_history(line);
		strcpy(str, line);
		free(line);
	}
	return (0);
}

int	get_cmd_line(char *str, char *line)
{
	char	*prompt_username;
	char	*prompt_dir_and_name;
	char	*prompt_dir_and_name_with_arr;
	char	*colored_prompt;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	prompt_username = ft_strjoin(getenv("USER"), \
						"\001\e[1;95m\002@\001\033[0m\e[1;94m\002");
	prompt_dir_and_name = ft_strjoin(prompt_username, cwd);
	prompt_dir_and_name_with_arr = ft_strjoin(prompt_dir_and_name, \
									"\001\033[1;32m\002> \001\033[0m\002");
	colored_prompt = ft_strjoin("\001\033[1;32m\002", \
						prompt_dir_and_name_with_arr);
	line = readline(colored_prompt);
	free(prompt_username);
	free(prompt_dir_and_name);
	free(prompt_dir_and_name_with_arr);
	free(colored_prompt);
	return (get_cmd_line_helper(line, str));
}

void	freelst(t_lst *tokenlst, t_lst *pipelinelst)
{
	t_lst	*tmplst;
	int		i;

	while (tokenlst)
	{
		tmplst = tokenlst->next;
		free(tokenlst->value);
		free(tokenlst);
		tokenlst = tmplst;
	}
	while (pipelinelst)
	{	
		i = 0;
		tmplst = pipelinelst;
		pipelinelst = pipelinelst->next;
		while (tmplst->type == TOKEN_CMD_ARGS && tmplst->cmd[i])
			free(tmplst->cmd[i++]);
		if (tmplst->type == TOKEN_CMD_ARGS)
			free(tmplst->cmd);
		if (tmplst->type != TOKEN_CMD_ARGS)
			free(tmplst->value);
		free(tmplst);
	}
}

char	*env_array_find_value(char *ep)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (ep[i] != '=')
		i++;
	j = i;
	while (ep[j])
		j++;
	value = ft_substr(ep, i + 1, j);
	return (value);
}

char	*env_array_find_key(char *ep)
{
	int		i;
	char	*key;

	i = 0;
	while (ep[i] != '=')
		i++;
	key = ft_substr(ep, 0, i);
	return (key);
}

t_env	*find_last_env(t_env *head_env)
{
	while (head_env->next != NULL)
		head_env = head_env->next;
	return (head_env);
}

void	init_env(char **ep, t_env **head_env)
{
	t_env	*env_tmp;
	int		i;

	i = 0;
	while (ep[i])
	{
		env_tmp = ft_calloc(1, sizeof(t_env));
		env_tmp->key = env_array_find_key(ep[i]);
		env_tmp->value = env_array_find_value(ep[i]);
		env_tmp->next = NULL;
		if (*head_env == NULL)
			*head_env = env_tmp;
		else
			find_last_env(*head_env)->next = env_tmp;
		i++;
	}
}

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
	int		doll_cnt;
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

void	add_exit_code(t_env **head_env, int code)
{
	t_env	*env_tmp;
	char	*str_code;

	str_code = ft_itoa(code);
	if (!env_is_exists(*head_env, "?", str_code))
	{
		env_tmp = ft_calloc(1, sizeof(t_env));
		env_tmp->key = ft_strdup("?");
		env_tmp->value = str_code;
		env_tmp->next = NULL;
		find_last_env(*head_env)->next = env_tmp;
	}
}

void	error_message(char *str)
{
	ft_putendl_fd(str, 2);
}

int	check_line_helper(char *line, int *i)
{
	int	dqoute;
	int	sqoute;

	dqoute = 1;
	sqoute = 1;
	if (line[*i] == '\'')
	{
		sqoute = sqoute * -1;
		i++;
		while (line[*i] != '\0' && line[*i] != '\'')
			(*i)++;
		if (line[*i] != '\'')
			return (1);
	}
	if (line[*i] == '"')
	{
		dqoute = dqoute * -1;
		(*i)++;
		while (line[*i] != '\0' && line[*i] != '"')
			(*i)++;
		if (line[*i] != '"')
			return (1);
	}
	return (0);
}

int	check_line(char *line)
{
	int	dind;
	int	sind;
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_line_helper(line, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	freeenv(t_env *env)
{
	t_env	*tmpenv;

	while (env)
	{
		tmpenv = env->next;
		free(env->value);
		free(env->key);
		free(env);
		env = tmpenv;
	}
}

void	print_tokenlst(t_lst *tokenlst)
{
	while (tokenlst)
	{
		printf("%s - %d - %d\n", tokenlst->value, tokenlst->type, \
		tokenlst->str_position);
		tokenlst = tokenlst->next;
	}
}

void	print_pipelinelst(t_lst *pipelinelst)
{
	int	i;

	while (pipelinelst)
	{	
		i = 0;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			printf("[%s | %d] ", pipelinelst->cmd[i], i);
			i++;
		}
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			printf("(%s)", pipelinelst->value);
		printf("\n");
		pipelinelst = pipelinelst->next;
	}
}

int	loop(char *line, t_env *env, char **ep, t_lst *tokenlst)
{
	t_lst	*pipelinelst;

	in_signals();
	pipelinelst = NULL;
	if (get_cmd_line(line, NULL))
	{
		freeenv(env);
		free(line);
		clear_history();
		exit(0);
	}
	if (check_line(line) == 1)
	{
		ft_bzero(line, MAXCOM);
		printf("WARNING: Unclosed quote.\n");
		return (1);
	}
	get_tokenlst(line, &tokenlst);
	expand_env_vars(tokenlst, env, 0);
	get_pipelinelst(tokenlst, &pipelinelst);
	create_outfiles(pipelinelst);
	add_exit_code(&env, execute(pipelinelst, env, ep));
	unlink(".chillytmp");
	freelst(tokenlst, pipelinelst);
	return (0);
}

int	main(int ac, char **av, char **ep)
{
	char	*line;
	t_env	*env;

	line = ft_calloc(MAXCOM, sizeof(char));
	if (ac > 1)
	{
		error_message("Error message: too many arguments!");
		exit(1);
	}
	env = NULL;
	init_env(ep, &env);
	init_shell();
	while (1)
		if (loop(line, env, ep, NULL))
			continue ;
}
