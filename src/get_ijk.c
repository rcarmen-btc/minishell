/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ijk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:46:25 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/17 15:47:03 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
