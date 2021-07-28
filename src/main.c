/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 21:26:17 by rcarmen           #+#    #+#             */
/*   Updated: 2021/07/28 21:26:20 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "lexer.h"

// echo "ehh" 'loo'"coo"'dsf' | > < << >> (

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
		return malloc(newsize);
	}
	else if (newsize <= origsize)
	{
		return ptr;
	}
	else
	{
		ptrNew = malloc(newsize);
		if (ptrNew)
		{
			ft_memcpy(ptrNew, ptr, origsize);
			free(ptr);
		}
		return ptrNew;
	}
}

int	main(int ac, char **av, char **ep)
{
	char	*line;
	t_lst	stack_c;
	t_lst	stack_o;
	t_lexer *lexer;
	t_token	*token;

	token = (void *)0;
	while (1)
	{
		line = readline("chillyshell$ ");
		printf("%s\n", line);
		lexer = init_lexer(line);
		while ((token = lexer_get_next_token(lexer)) != (void *)0)
		{
			printf("%d: %s\n", token->type, token->value);
			if (token)
			{
				free(token->value);
				free(token);
			}
		}
		free(lexer);
		add_history(line);
	}

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
