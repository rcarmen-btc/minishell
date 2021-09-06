/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/09/06 15:25:14 by rcarmen          ###   ########.fr       */
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
		if (ptrNew)
		{
			ft_memmove(ptrNew, ptr, newsize);
			// memmove(ptrNew, ptr, newsize);
			// ft_bcopy(ptr, ptrNew, newsize);
			free(ptr);
		}
		return ptrNew;
	}
}

// char	*get_infile_name(t_lst *pipelinelst)
// {
// 	char *save;

// 	save = NULL;
// 	while (pipelinelst)
// 	{	
// 		if (pipelinelst->type == TOKEN_LREDIR)
// 		{
// 			pipelinelst = pipelinelst->next;
// 			if (pipelinelst)	
// 				save = pipelinelst->cmd[0];
// 		}
// 		if (pipelinelst)	
// 			pipelinelst = pipelinelst->next;
// 	}
// 	return (save);
// }

// char	*get_outfile_name(t_lst *pipelinelst)
// {
// 	while (pipelinelst)
// 	{	
// 		if (pipelinelst->type == TOKEN_RREDIR)
// 		{
// 			pipelinelst = pipelinelst->next;
// 			if (pipelinelst)	
// 				return (pipelinelst->cmd[0]);
// 		}
// 		if (pipelinelst)	
// 			pipelinelst = pipelinelst->next;
// 	}
// 	return (NULL);
// }


void	print_pipelinelst(t_lst *pipelinelst)
{
	while (pipelinelst)
	{	
		int	i = 0;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			printf("[%s | %d] ", pipelinelst->cmd[i], i);

			i++;
		}
		// printf("\n");
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			printf("(%s)", pipelinelst->value);
		printf("\n");
		pipelinelst = pipelinelst->next;
	}
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
	prompt_username = ft_strjoin(getenv("USER"), "\e[95m@\033[0m"); // получаем username
	prompt_dir_and_name = ft_strjoin(prompt_username, cwd);// тек. какалог объединяем с username
	prompt_dir_and_name_with_arr = ft_strjoin(prompt_dir_and_name, "\033[0;32m> \033[0m"); // добавляем цветной '>' 
	colored_prompt = ft_strjoin("\033[0;32m", prompt_dir_and_name_with_arr); // красим в зеленый 
	// wait(NULL);
    line = readline(colored_prompt);
	free(prompt_username);
	free(prompt_dir_and_name);
	free(prompt_dir_and_name_with_arr);
	free(colored_prompt);
	if (line == NULL)
		exit(0);
    else if (strlen(line) != 0)
	{
     	add_history(line);
        strcpy(str, line);
		free(line);
    }
	return (0);

}

void	freelst(t_lst *tokenlst, t_lst *pipelinelst)
{
	t_lst *lsttmp;

	while (tokenlst)
	{
		lsttmp = tokenlst->next;
		free(tokenlst->value);
		free(tokenlst);
		tokenlst = lsttmp;;
	}
	while (pipelinelst)
	{	
		int	i = 0;
		lsttmp = pipelinelst->next;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			// printf("%s ", pipelinelst->cmd[i]);
			free(pipelinelst->cmd[i]);
			i++;
		}
		if (pipelinelst)
			free(pipelinelst->cmd);
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			free(pipelinelst->value);
			// printf("\n%s\n", pipelinelst->value);
		free(pipelinelst);
		pipelinelst = lsttmp;
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

int	main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*tokenlst;
	t_lst		*pipelinelst;
	t_lst		*pipelinelst_tmp;
	t_env		*env;

	line = ft_calloc(MAXCOM, sizeof(char));
	if (ac > 1)
	{
		printf("Error message: too many arguments!\n"); // TODO: временно, надо заменить на соотвуствующую ошибку.
		return(1);
	}
	env = NULL;
	init_env(ep, &env);
	init_shell();
	while (1)
	{
		tokenlst = NULL;
		pipelinelst = NULL;
		in_signals();
		get_cmd_line(line, NULL);
		get_tokenlst(line, &tokenlst);
		get_pipelinelst(tokenlst, &pipelinelst);
		// print_pipelinelst(pipelinelst);
		create_outfiles(pipelinelst);
		execute(pipelinelst, &line, env);
		// freelst(tokenlst, pipelinelst);
	}	
}
