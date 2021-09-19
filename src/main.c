/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/19 14:54:26 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execute.h"
#include <stddef.h>

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

	(void)av;
	line = ft_calloc(MAXCOM, sizeof(char));
	if (ac > 1)
	{
		error_message("Error message: too many arguments!");
		exit(1);
	}
	env = NULL;
	init_env(ep, &env);
	// init_shell();
	while (1)
		if (loop(line, env, ep, NULL))
			continue ;
}
