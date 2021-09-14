/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/14 21:56:40 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execute.h"
#include <stddef.h>

void *ft_realloc(void *ptr, size_t origsize, size_t newsize)
{
	void	*ptrNew; 

	if (newsize == 0)
	{
		free(ptr);
		return NULL;
	}
	else if (!ptr)
	{
		return ft_calloc(newsize, sizeof(char));
	}
	else if (newsize <= origsize)
	{
		return ptr;
	}
	else
	{
		ptrNew = ft_calloc(newsize, sizeof(char));
		if (ptrNew && ptr != NULL)
		{
			// ft_memmove(ptrNew, ptr, newsize);
			// ft_memcpy(ptrNew, ptr, newsize);
			ft_strlcpy(ptrNew, ptr, newsize);
			free(ptr);
		}
		return ptrNew;
	}
}

void	print_pipelinelst(t_lst *pipelinelst)
{
	while (pipelinelst)
	{	
		int	i = 0;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			printf("[%s | %d] ", pipelinelst->cmd[i], i);
			// printf("[%d | %d] ", pipelinelst->type, i);
			i++;
		}
		// printf("\n");
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			printf("(%s)", pipelinelst->value);
		printf("\n");
		pipelinelst = pipelinelst->next;
	}
	printf("HIIIiI\n");
}

void init_shell()
{
	printf("\033[2J");
	int fd;
	char *line;
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
    sleep(1);
}

int get_cmd_line(char *str, char *line)
{ 
	char		*prompt_username;
	char		*prompt_dir_and_name;
	char		*prompt_dir_and_name_with_arr;
	char		*colored_prompt;
	char		cwd[1024];
  	
	getcwd(cwd, sizeof(cwd)); // получаем тек. каталог 
	prompt_username = ft_strjoin(getenv("USER"), "\001\e[1;95m\002@\001\033[0m\e[1;94m\002"); // получаем username
	prompt_dir_and_name = ft_strjoin(prompt_username, cwd);// тек. какалог объединяем с username
	prompt_dir_and_name_with_arr = ft_strjoin(prompt_dir_and_name, "\001\033[1;32m\002> \001\033[0m\002"); // добавляем цветной '>' 
	colored_prompt = ft_strjoin("\001\033[1;32m\002", prompt_dir_and_name_with_arr); // красим в зеленый 
    line = readline(colored_prompt);
	free(prompt_username);
	free(prompt_dir_and_name);
	free(prompt_dir_and_name_with_arr);
	free(colored_prompt);
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

void		freelst(t_lst *tokenlst, t_lst *pipelinelst)
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
	int i;
	int j;
	char *value;

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
	int i;
	char *key;

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
			fd = open(pipelinelst->next->cmd[0], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			close(fd);
		}
		if (pipelinelst->type == TOKEN_APPRDIR)
		{
			fd = open(pipelinelst->next->cmd[0], O_WRONLY | O_CREAT | O_APPEND, 0666);
			close(fd);
		}
		pipelinelst = pipelinelst->next;
	}
	
}

int		check_the_dollar_and_get_cnt(char *str)
{
	int	i;
	int	doll_cnt;
	
	i = 0;
	doll_cnt = 0;
	while (str[i])
	{
		if (str[i] == '$')
			doll_cnt++;
		i++;
	}
	return (doll_cnt);
}

t_env	*get_el_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(key, env->key, ft_strlen(key)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	**replace_doll_to_env(t_lst *tokenlst, t_env *env)
{
	int k;
	int i;
	char **arr_env;	
	t_env	*el_env;

	arr_env = ft_split(tokenlst->value, '$');
	i = 0;
	while (arr_env[i] != NULL)
	{
		el_env = get_el_env(env, arr_env[i]);
		if (el_env != NULL)
		{
			free(arr_env[i]);
			arr_env[i] = el_env->value;
		}
		else
		{
			free(arr_env[i]);
			arr_env[i]  = "";
		}
		i++;
	}
	free(arr_env);
	return (arr_env);
	// i = 0;
	// while (arr_env[i])
	// {
	// 	printf("=%s=\n", arr_env[i]);
	// 	i++;
	// }
	
}

char	*get_start(char *value)
{
	char	*res;
	int		len;

	len = 0;
	while (value[len] != '$')
		len++;
	res = ft_calloc(len + 1, sizeof(char));
	len = 0;
	while (value[len] != '$')
	{
		res[len] = value[len];
		len++;
	}
	return (res);
}

char	*get_doll_cnt(char *value)
{
	int i;
	int	len;
	char	*res;
	
	i = ft_strlen(value) - 1;
	len = 0;
	while (value[i] == '$')
	{
		len++;
		i--;
	}
	res = NULL;
	if (len > 0)
		res = ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
		res[i++] = '$';
	return (res);	
}

char	*join_all_arr(t_lst *tokenlst, char **arr_env)
{
	int i;
	int j;
	int len;
	char *str_env;
	char *start_and_doll;
	
	i = 0;
	len = 0;
	while (arr_env[i])
	{
		len = len + ft_strlen(arr_env[i]);
		i++;
	}
	str_env = ft_calloc(len + 1, sizeof(char));
	len = 0;
	i = 0;
	while (arr_env[i])
	{
		j = 0;
		while (arr_env[i][j])
		{
			str_env[len] = arr_env[i][j];
			len++;
			j++;
		}
		i++;
	}
	i = 0;
	if (tokenlst->value[0] != '$')
	{
		start_and_doll = get_start(tokenlst->value);
		str_env = ft_strjoin(start_and_doll, str_env);
		free(start_and_doll);
	}
	start_and_doll = get_doll_cnt(tokenlst->value);
	if (start_and_doll)
		str_env = ft_strjoin(str_env, start_and_doll);
	return (str_env);
}

void	expand_env_vars(t_lst *tokenlst, t_env *env)
{
	int		doll_cnt;
	char	**arr_env;
	char	*tmp;

	while (tokenlst)
	{
		if (tokenlst->type == TOKEN_CMD || tokenlst->type == TOKEN_DSTRING)
		{
			doll_cnt = check_the_dollar_and_get_cnt(tokenlst->value);
			if (doll_cnt > 0)
			{
				arr_env = replace_doll_to_env(tokenlst, env);
				tmp = tokenlst->value;
				tokenlst->value = join_all_arr(tokenlst, arr_env);
				free(tmp);
			}
		}
		tokenlst = tokenlst->next;
	}
}

void	print_tokenlst(t_lst *tokenlst)
{
	while (tokenlst)
	{
		printf("%s - %d - %d\n", tokenlst->value, tokenlst->type, tokenlst->str_position);
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

void error_message(char *str)
{
	ft_putendl_fd(str, 2);
}
	
int	check_line(char *line)
{
	int dqoute;
	int sqoute;
	int dind;
	int sind;
	int	i;

	dqoute = 1;
	sqoute = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			sqoute = sqoute * -1;
			i++;
			while (line[i] != '\0' && line[i] != '\'')
				i++;
			if (line[i] != '\'')
				exit(1);
			
		}
		if (line[i] == '"')
		{
			dqoute = dqoute * -1;
			i++;
			while (line[i] != '\0' && line[i] != '"')
				i++;
			if (line[i] != '"')
				exit(1);
		}
		i++;
	}
	return (0);
}

void	freeenv(t_env *env)
{
	t_env *tmpenv;

	while (env)
	{
		tmpenv = env->next;		
		free(env->value);
		free(env->key);
		free(env);
		env = tmpenv;
	}
	
}

int		main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*tokenlst;
	t_lst		*pipelinelst;
	t_lst		*pipelinelst_tmp;
	t_env		*env;

	line = ft_calloc(MAXCOM, sizeof(char));
	if (ac > 1)
	{
		error_message("Error message: too many arguments!");
		exit(1);
	}
	env = NULL;
	init_env(ep, &env);
	//init_shell();
	while (1)
	{
		in_signals();
		tokenlst = NULL;
		pipelinelst = NULL;
		if (get_cmd_line(line, NULL))
		{
			freeenv(env);
			free(line);
			clear_history();
			exit(0);
		}
		check_line(line);
		get_tokenlst(line, &tokenlst);
		expand_env_vars(tokenlst, env);
		// print_tokenlst(tokenlst);
		get_pipelinelst(tokenlst, &pipelinelst);
		// print_pipelinelst(pipelinelst);
		create_outfiles(pipelinelst);
		add_exit_code(&env, execute(pipelinelst, env, ep));
		freelst(tokenlst, pipelinelst);
	}	
}
