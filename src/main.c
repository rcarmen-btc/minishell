/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/08/09 00:23:06 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stddef.h>

// void *ft_realloc(void *ptr, size_t origsize, size_t newsize)
// {
// 	void	*ptrNew; 

// 	if (newsize == 0)
// 	{
// 		free(ptr);
// 		return NULL;
// 	}
// 	else if (!ptr)
// 	{
// 		return ft_calloc(newsize, sizeof(char));
// 	}
// 	else if (newsize <= origsize)
// 	{
// 		return ptr;
// 	}
// 	else
// 	{
// 		ptrNew = ft_calloc(newsize, sizeof(char));
// 		if (ptrNew)
// 		{
// 			ft_memmove(ptrNew, ptr, newsize);
// 			// memmove(ptrNew, ptr, newsize);
// 			// ft_bcopy(ptr, ptrNew, newsize);
// 			free(ptr);
// 		}
// 		return ptrNew;
// 	}
// }

void	get_linelst(char *line, t_lst **linelst)
{
	t_lexer *lexer;
	t_token	*token;

	lexer = init_lexer(line);
	while ((token = lexer_get_next_token(lexer)) != (void *)0)
	{
		push_back(linelst, token->value, token->type);
		if (token)
		{
			free(token->value);
			free(token);
		}
	}
	free(lexer);
}

int	main(int ac, char **av, char **ep)
{
	char		*line;
	t_lst		*linelst;
	t_cmdlst	*cmdlst;

	while (1)
	{
		cmdlst = NULL;
		linelst = NULL;
		printf("\033[0;32m"); 
		line = readline("chillyshell$ \033[0m");
		// printf("\033[0m");
		get_linelst(line, &linelst);
		// while (linelst)
		// {
		// 	printf("%d: %s\n", linelst->type, linelst->value);
		// 	linelst = linelst->next;
		// }
		// init_cmdlst(linelst, &cmdlst);
		// while (cmdlst)
		// {
		// 	int i = 0;
		// 	printf("==%d==\n", cmdlst->type);
		// 	if (cmdlst->type == TOKEN_EXEC_ARGS)
		// 		while (cmdlst->cmdline[i])
		// 		{
		// 			printf("- %s\n", cmdlst->cmdline[i]);
		// 			i++;
		// 		}
		// 	else
		// 	{
		// 		printf("%s\n", *(cmdlst->cmdline));
		// 	}
		// 	cmdlst = cmdlst->next;
		// }
		add_history(line);
	}	

		// line = readline("chillyshell$ ");
		// init_cmdlst(line);
		// add_history(line);

	// line = readline("chillyshell$ ");
	// line = "hello";
	// printf("%s\n", line);
	// lexer = init_lexer(line);
	// while ((token = lexer_get_next_token(lexer)) != (void *)0)
	// {
	// 	printf("%d: %s\n", token->type, token->value);
	// 	if ((void *)token != (void *)0)
	// 	{
	// 		if (token->value)
	// 			free(token->value);
	// 		free(token);
	// 	}
	// }
	// free(lexer);
	// add_history(line);
	// free(line);
}
