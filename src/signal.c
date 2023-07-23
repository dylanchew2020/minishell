/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzi-qi <tzi-qi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:25:00 by lchew             #+#    #+#             */
/*   Updated: 2023/07/22 17:50:52 by tzi-qi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(t_root	*sh, int mode)
{
	(void) sh;
	if (mode == 1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
	else if (mode == 0)
	{
		signal(SIGINT, signal_handler2);
		signal(SIGQUIT, signal_handler2);
	}
	else if (mode == 2)
	{
		signal(SIGINT, heredoc_signal);
		signal(SIGQUIT, SIG_IGN);
	}
	return ;
}

//SIGINT - ctrl + c
//SIGQUIT - ctrl + \ //

// Function: int rl_redisplay ()

// Change what's displayed on the screen to reflect the current 
// contents of rl_line_buffer.
void	signal_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void	signal_handler2(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	if (signum == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
	}
}

void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(EXIT_SUCCESS);
	}
}