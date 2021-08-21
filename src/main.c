/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/13 11:44:25 by rcarmen          ###   ########.fr       */
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

	if ((infile = get_infile_name(pipelinelst)) != NULL)
	{
		// printf("%s\n", infile);
		if ((fdin = open(infile, O_RDONLY)) == -1)
		{
			perror(infile);
			return ;
		}
	}
	else
		fdin = dup(tmpin);
		
	int ret;
	int fdout;
	while (pipelinelst != NULL) 
	{
		if (pipelinelst->type == TOKEN_CMD_ARGS)
		{
			dup2(fdin, 0);
			close(fdin);
			if ((outfile = get_outfile_name(pipelinelst)) != NULL)
			{
				if ((fdout = open(outfile, O_WRONLY)) == -1)
				{
					perror(infile);
					return ;
				}
				else
					fdout = dup(tmpout);
			}
			else
			{
				int fdpipe[2];
				pipe(fdpipe);
				fdout = fdpipe[1];
				fdin = fdpipe[0];
			}
			dup2(fdout, 1);
			close(fdout);
			// pipelinelst = pipelinelst->next;
			
			ret = fork();
			printf("s\n");
			printf("-%s\n", pipelinelst->cmd[0]);
			if (ret == 0)
			{
				printf("ss\n");
				printf("-%s\n", pipelinelst->cmd[0]);
				execvp(pipelinelst->cmd[0], pipelinelst->cmd);
				perror(pipelinelst->cmd[0]);
				exit(1);
			}
		}
		if (pipelinelst)
			pipelinelst = pipelinelst->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
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

	if (ac > 1 && av)
	{
		printf("Error message: too many arguments!\n"); // TODO: временно, надо заменить на соотвуствующую ошибку.
		return(1);
	}
	pipelinelst_tmp = pipelinelst;
	promp = "\033[0;32mchillyshell\033[0;39m$ \033[0m";
	while (1)
	{
		tokenlst = NULL;
		pipelinelst = NULL;
		in_signals();
		line = readline(promp);
		get_tokenlst(line, &tokenlst);

		get_pipelinelst(tokenlst, &pipelinelst);
		// // print_pipelinelst(pipelinelst);

		// execute(pipelinelst);//пока не работает

		add_history(line);
	}	
}
