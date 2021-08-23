/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/23 12:23:27 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
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
	int	tmpin = dup(0);
	int	tmpout = dup(1);
	char	*infile;
	char	*outfile;
	int		fdin;

	int pipe_fds[2];	
	
	pipe(pipe_fds);
	
	int children[2];
	
	children[0] = fork();
	if (children[0] == 0)
	{
		dup2(pipe_fds[1], 1);
		close(pipe_fds[0]);
	}
	children[1] = fork();
	if (children[1] == 0)
	{
		dup2(pipe_fds[0], 0);
		close(pipe_fds[1]);
	}
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

int	main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*tokenlst;
	t_lst		*pipelinelst;
	char		*promp;
	t_lst		*pipelinelst_tmp;

	// if (ac > 1 && av)
	if (ac > 1)
	{
		printf("Error message: too many arguments!\n"); // TODO: временно, надо заменить на соотвуствующую ошибку.
		return(1);
	}
	printf("%d\n", ac);
	pipelinelst_tmp = pipelinelst;
	promp = "\033[0;32mchillyshell\033[0;39m$ \033[0m";
	while (1)
	{
		tokenlst = NULL;
		pipelinelst = NULL;
		in_signals();
		line = readline(promp);
		add_history(line);
		get_tokenlst(line, &tokenlst);
		get_pipelinelst(tokenlst, &pipelinelst);
		// print_pipelinelst(pipelinelst);

		// execute(pipelinelst);//пока не работает

	}	
}
