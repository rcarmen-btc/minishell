/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdanyel <hdanyel@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 18:32:08 by hdanyel           #+#    #+#             */
/*   Updated: 2021/08/21 18:32:08 by hdanyel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void re_promp(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0); //замена содержимого line ""
	rl_on_new_line(); //переместились на новую строку
	rl_redisplay(); //замена отображаемого, на текущее содержимое
	// rl_line_buffer(promp)
}

void in_signals(void)
{
	signal(SIGINT, re_promp);
	signal(SIGQUIT, SIG_IGN);
}

static void	quit_process(int signal)
{
	(void)signal;
	printf("Quit\n");
}

static void	interrupt_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
}

void	ex_signals(void) //TODO добавить в execute
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}