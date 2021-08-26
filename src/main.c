/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/24 20:42: by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "builtins.h"
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

char	*get_infile_name(t_lst *pipelinelst)
{
	char *save;

	save = NULL;
	while (pipelinelst)
	{	
		if (pipelinelst->type == TOKEN_LREDIR)
		{
			pipelinelst = pipelinelst->next;
			if (pipelinelst)	
				save = pipelinelst->cmd[0];
		}
		if (pipelinelst)	
			pipelinelst = pipelinelst->next;
	}
	return (save);
}

char	*get_outfile_name(t_lst *pipelinelst)
{
	while (pipelinelst)
	{	
		if (pipelinelst->type == TOKEN_RREDIR)
		{
			pipelinelst = pipelinelst->next;
			if (pipelinelst)	
				return (pipelinelst->cmd[0]);
		}
		if (pipelinelst)	
			pipelinelst = pipelinelst->next;
	}
	return (NULL);
}

void	execute(t_lst *pipelinelst)
{
	builtin_pwd();
}

void	print_pipelinelst(t_lst *pipelinelst)
{
	while (pipelinelst)
	{	
		int	i = 0;
		while (pipelinelst->type == TOKEN_CMD_ARGS && pipelinelst->cmd[i])
		{
			printf("%s ", pipelinelst->cmd[i]);

			i++;
		}
		if (pipelinelst->type != TOKEN_CMD_ARGS)
			printf("\n%s\n", pipelinelst->value);
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
    printf("\n______________________________________________\n");
    sleep(1);
}

char	*create_promp(char **line)
{
	char		*promp_username;
	char		*promp_dir_and_name;
	char		*promp_dir_and_name_with_arr;
	char		*colored_promp;

	promp_username = ft_strjoin(getenv("USER"), "\e[95m@\033[0m"); // получаем username
	promp_dir_and_name = ft_strjoin(promp_username, getenv("HOME")); // получаем тек. каталог и объединяем с username
	promp_dir_and_name_with_arr = ft_strjoin(promp_dir_and_name, "\033[0;32m> \033[0m"); // добавляем цветной '>' 
	colored_promp = ft_strjoin("\033[0;32m", promp_dir_and_name_with_arr); // красим в зеленый 
	*line = readline(colored_promp);
	free(promp_username);
	free(promp_dir_and_name);
	free(promp_dir_and_name_with_arr);
	free(colored_promp);
	if (*line == NULL) // TODO: ctrl-d/free and exit  
	{
		printf(*line);
		exit(0);
	}
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

int	main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*tokenlst;
	t_lst		*pipelinelst;
	t_lst		*pipelinelst_tmp;

	if (ac > 1)
	{
		printf("Error message: too many arguments!\n"); // TODO: временно, надо заменить на соотвуствующую ошибку.
		return(1);
	}
	init_shell();
	// promp = "\033[0;32mchillyshell\033[0;39m$ \033[0m";
	while (1)
	{
		tokenlst = NULL;
		pipelinelst = NULL;
		in_signals();
		create_promp(&line);
		add_history(line);
		get_tokenlst(line, &tokenlst);
		get_pipelinelst(tokenlst, &pipelinelst);
		// print_pipelinelst(pipelinelst);
		execute(pipelinelst);//пока не работает
		free(line);
		freelst(tokenlst, pipelinelst);
	}	
}
